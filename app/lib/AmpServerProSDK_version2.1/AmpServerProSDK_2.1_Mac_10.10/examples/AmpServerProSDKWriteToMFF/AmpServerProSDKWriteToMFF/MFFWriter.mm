
/*
 *  MFFWriter.cpp
 *  @author Robert Bell
 *  @date 2015/12/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

#include "MFFWriter.h"

// Other EGI Base includes.
#include "EGIBase.h"
#include "EGIBuffer.h"
#include "EGICircularBuffer.h"
#include "EGIExceptions.h"
#include "EGIRunLoop.h"
#include "UtilityFunctions.h"


// Poco Libs
#include "Poco/Timestamp.h"
#include "Poco/Timezone.h"

// General MFF
#include "MFFFactory.h"
#include "LocalAppleMFFFactoryDelegate.h"
#include "MFFUtils.h"

// MFF - Signal SignalResource
#include "SignalResource.h"

// Local MFF Utilities.
#include "MFFFileWriterUtilities.h"

// Other includes.
#include <iostream>
#include <string.h>

// Objective-C.
#import "AppController.h"

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;
using namespace com::egi::services::mff::api;
using namespace com::egi::services::mff::util;

using Poco::Timestamp;
using Poco::Timezone;

// Local functions.
static std::string getCurrentMFFTimeStamp();
static NSString *cppStringToNSString(std::string theString);

// Useful define(s).
#define PACKET1_SAMPLE_SIZE 1152
#define PACKET2_SAMPLE_SIZE 1264
#define BLOCK_SIZE_IN_SAMPLES 4096

//####################################
// Public Section.
//####################################

MFFWriter::MFFWriter(AS_Network_Types::AmpInfo ampInfo,
                     EGIBase::EGICircularBuffer *ampBuffer,
                     std::string mffFileURI,
                     int samplingRate,
                     AppController *appController) : EGITask() {
    
    this->stopRecording_ = false;
    
    // Based on the number of samples per block and the packet format,
    // allocate the memory for the source data.
    this->ampInfo_ = ampInfo;
    if (this->ampInfo_.packetType == AS_Network_Types::pkType1) {
        
        this->srcDataSize_ = BLOCK_SIZE_IN_SAMPLES * PACKET1_SAMPLE_SIZE;
        this->srcData_ = new char[this->srcDataSize_];
        
    } else if (this->ampInfo_.packetType == AS_Network_Types::pkType2) {
        
        this->srcDataSize_ = BLOCK_SIZE_IN_SAMPLES * PACKET2_SAMPLE_SIZE;
        this->srcData_ = new char[this->srcDataSize_];
        
    }
    
    this->samplingRate_ = samplingRate;
    
    // Debug:
    std::cout << "info: source data buffer size: " << this->srcDataSize_ << std::endl;
    
    // Setup the buffer.
    this->ampBuffer_ = ampBuffer;
    RETAIN(this->ampBuffer_);
    this->ampBufferOpts_ = new EGIBuffer::Opts();
    this->ampBufferOpts_->uByCopy = false;
    this->ampBufferOpts_->numberOfBytes = this->srcDataSize_; // We only read this number of bytes!
    
    // Sample and block counters.
    this->sampleCounter_ = 0;
    this->dataBlockCounter_ = 0;
    
    // Set the net code to an unknown code. We will not know which net is attached
    // until we begin to receive samples.
    this->netCode_ = AS_Network_Types::Unknown;
    
    this->mffFileURI_ = mffFileURI;
    this->appController_ = [appController retain];
    
}

MFFWriter::~MFFWriter() {
    
    RELEASE(this->ampBuffer_);
    [this->appController_ release];

}


void MFFWriter::performTask(EGIObject *taskScheduler, EGIObject *eObject) {
    
    // Setup everything we need to starting writing signal data to an MFF
    // file. There will be a lot of error checking during this process to make sure
    // each of the steps functions correctly.
    
    //######
    // Step 1.
    // Create the MFF file.
    //######
    
    MFFFactory *factory = new MFFFactory(new LocalAppleMFFFactoryDelegate());
    std::string message = "unknown";
    
    if ( MFFFileWriterUtilities::createMFFFile(factory, this->mffFileURI_, message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    //######
    // Step 2.
    // Create the various files that we'll need during the acquisition. These include:
    //
    // 1) signal1.bin ... and streaming will begin.
    //
    // The below will be created after streaming has finish to ensure
    // that we have the correct net code and the total number of blocks and
    // samples. If we never obtain one, we will
    // place a default net in.
    //
    // 2) info.xml
    // 3) info1.xml
    // 4) coordinates.xml
    // 5) sensorLayout.xml
    // 6) epochs.xml
    //######
    
    message = "unknown";
    SignalResource *signalResource = MFFFileWriterUtilities::createSignalFile(factory, this->mffFileURI_, "signal1.bin", message);
    if (signalResource != NULL) {
        
        // We have a valid signal resource file, start the loop to pull data and process to file until we receive an
        // indication to stop.
        bool firstBlock = true;
        bool continuationBlock = false;
        
        while (true) {
            
            // Exit this while loop if a stop recording request is received.
            if ( this->lock() == 0 ) {
                if ( this->stopRecording_ == true ) {
                    this->unlock();
                    break;
                }
                this->unlock();
            }
            
            if ((this->ampBuffer_ != NULL) &&
                (this->ampBufferOpts_ != NULL)) {
                
                uint64_t numberOfAvailableBytes = this->ampBuffer_->getAvailableReadSize(this->ampBufferOpts_);
                if (numberOfAvailableBytes >= this->srcDataSize_) {
                    
                    uint64_t numberOfBytesRead = 0;
                    this->ampBuffer_->readFromBuffer(this->srcData_, numberOfBytesRead, this->ampBufferOpts_);
                    
                    // Important note: The buffer options ensures we only read "this->srcDataSize_" from the buffer.
                    
                    if (numberOfBytesRead == this->srcDataSize_) {
                        
                        std::ostringstream blockNumber;
                        blockNumber << this->dataBlockCounter_;
                        
                        [this->appController_ logToInterface:cppStringToNSString("info: writing data block " + blockNumber.str() + "\n")];
                        
                        // Process the data block.
                        AS_Network_Types::NetCode detectedNetCode = AS_Network_Types::Unknown;
                        MFFFileWriterUtilities::writeSignalBlock(signalResource, this->srcData_, this->srcDataSize_, this->ampInfo_.amplifierType,
                                                                 this->ampInfo_.packetType, this->ampInfo_.numberOfChannels, this->samplingRate_,
                                                                 firstBlock, continuationBlock, detectedNetCode);
                        
                        if (this->netCode_ != detectedNetCode) {
                            
                            // A net change was detected.
                            std::string connectedNet = MFFFileWriterUtilities::getLayoutNameForNetType(detectedNetCode);
                            [this->appController_ logToInterface:cppStringToNSString("info: net connected: " + connectedNet + "\n")];
                            
                            this->netCode_ = detectedNetCode;
                        }
                        
                        firstBlock = false;
                        continuationBlock = true;
                        
                        this->sampleCounter_ += BLOCK_SIZE_IN_SAMPLES;
                        this->dataBlockCounter_++;
                        
                    } else {
                        
                        // This is not good.
                        
                    }
                    
                }
                
            }
            
            // Don't run the loop too fast...
            usleep(10000);
        }
        
        // Close the signal file.
        factory->closeResource(signalResource);
        
        // Write count information to the file.
        MFFFileWriterUtilities::writeClosingCountsToSignalFile(factory,
                                                               this->mffFileURI_,
                                                               "signal1.bin",
                                                               this->dataBlockCounter_, this->sampleCounter_);
        
        
    } else {
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    // If no net was detected, use a default net.
    if (this->netCode_ == AS_Network_Types::Unknown ||
        (this->netCode_ == AS_Network_Types::NoNet)) {
        this->netCode_ = AS_Network_Types::MCGSN256_1_0;
        
        [this->appController_ logToInterface:cppStringToNSString("info: no net was connected, using: MicroCel GSN 100 256 1.0\n")];
    }

    
    message = "unknown";
    if ( MFFFileWriterUtilities::createInfoFile(factory, this->mffFileURI_,
                                                this->ampInfo_, getCurrentMFFTimeStamp(),
                                                message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    message = "unknown";
    if ( MFFFileWriterUtilities::createInfoNFile(factory, this->mffFileURI_, InfoN::kEEG,
                                                 this->netCode_, message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    message = "unknown";
    if ( MFFFileWriterUtilities::createLayoutFile(factory, this->mffFileURI_,
                                                  this->netCode_, MFFResourceType::kMFF_RT_Coordinates,
                                                  message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    message = "unknown";
    if ( MFFFileWriterUtilities::createLayoutFile(factory, this->mffFileURI_,
                                                  this->netCode_, MFFResourceType::kMFF_RT_SensorLayout,
                                                  message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
    message = "unknown";
    uint64_t microsecondsPerSample = 0;
    if (this->samplingRate_ != 0) {
        microsecondsPerSample = 1000000 / this->samplingRate_;
    } else {
        microsecondsPerSample = 0;
    }
    if ( MFFFileWriterUtilities::createEpochFile(factory, this->mffFileURI_,
                                                 0, this->sampleCounter_ * microsecondsPerSample, this->dataBlockCounter_,
                                                 message) == false ) {
        
        [this->appController_ errorToInterface:cppStringToNSString(message)];
        return;
    }
    
}

void MFFWriter::stopRecording() {
    
    if ( this->lock() == 0 ) {
        this->stopRecording_ = true;
        this->unlock();
    }
    
}

//####################################
// End - Public Section.
//####################################

//####################################
// Protected Section.
//####################################

// Gets the current time stamp in MFF time format.
// Note 1: The time zone is also provided.
// Note 2: This functionality will be moved to the MFF in a later release.
static std::string getCurrentMFFTimeStamp() {
    
    Poco::Timezone *tzone = new Poco::Timezone();
    Poco::Timestamp *timeStamp = new Poco::Timestamp();
    
    int timeZone = tzone->tzd();
    uint64_t microsecondsTimeStamp = timeStamp->epochMicroseconds();
    
    delete tzone;
    delete timeStamp;
    
    return MFFUtils::microsecondsToMFFDateTime(microsecondsTimeStamp, timeZone);
    
}

// Simple convenience function to convert a cpp string to an NSString.
// Note: The returned string is NOT auto-released.
static NSString *cppStringToNSString(std::string theString) {
    
    return [[NSString alloc] initWithCString:theString.c_str() encoding:NSUTF8StringEncoding];
    
}

MFFWriter::MFFWriter(const MFFWriter& source) : EGIObject(source){
#ifdef __USE_EXCEPTIONS__
    throw EGIBase::MethodNotSupported_EGIException("MFFWriter::MFFWriter\
                                                   (const MFFWriter& source)");
#endif //__USE_EXCEPTIONS__
}

MFFWriter& MFFWriter::operator=(const MFFWriter& source){
    EGIObject::operator=(source);
#ifdef __USE_EXCEPTIONS__
    throw EGIBase::MethodNotSupported_EGIException("MFFWriter& MFFWriter::operator=\
                                                   (const MFFWriter& source)");
#endif //__USE_EXCEPTIONS__
    return *this;
}

//####################################
// End - Protected Section.
//####################################

//####################################
// Private Section.
//####################################
//####################################
// End - Private Section.
//####################################
