
/*
 *  DataStreamObserver.cpp
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

#include "DataStreamObserver.h"

// Other EGI Base includes.
#include "EGIBase.h"
#include "EGIBuffer.h"
#include "EGICircularBuffer.h"

#include "EGICircularBuffer.h"
#include "EGIExceptions.h"
#include "EGIRunLoop.h"

#include "UtilityFunctions.h"

// Other includes.
#include <iostream>
#include <string.h>

class MFFWriter;

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

struct SDKImpl{
    
    AS_Network_Client *client;
    AS_Network_Types::AmpInfo ampInfo;
    DataStreamObserver *dataStreamObserver;
    EGIRunLoop *egiRunLoop;
    MFFWriter *mffWriter;
    EGICircularBuffer *ampBuffer = NULL;
    EGIBuffer::Opts *ampBufferOpts = NULL;
    
};

//####################################
// Public Section.
//####################################

DataStreamObserver::DataStreamObserver(const SDKImpl* sdkWrapper) : Observer() {
    
    this->sdkWrapper_ = new SDKImpl();
    
    ASSIGN(sdkWrapper->client, this->sdkWrapper_->client);
    ASSIGN(sdkWrapper->ampBuffer, this->sdkWrapper_->ampBuffer);
    ASSIGN(sdkWrapper->ampBufferOpts, this->sdkWrapper_->ampBufferOpts);
    
    // Don't need references below.
    this->sdkWrapper_->dataStreamObserver = NULL;
    this->sdkWrapper_->egiRunLoop = NULL;
    this->sdkWrapper_->mffWriter = NULL;
    
    
    this->record_ = false;
    
}

DataStreamObserver::~DataStreamObserver() {

    // Release the client layer.
    RELEASE(this->sdkWrapper_->client);
    
    // Cleanup the buffer.
    RELEASE(this->sdkWrapper_->ampBuffer);
    RELEASE(this->sdkWrapper_->ampBufferOpts);

}

// Note that if you block in update, you will effectively block the data stream
// thread, and thus will cease to receive any more data from the stream.
// Though we are performing some operations here, the better solution is to dump data
// to a thread safe buffer and pull from that buffer in a separate thread. That way, you ensure
// that if your data routines take time, you will not miss samples, or otherwise perturb the system.
void DataStreamObserver::update(Observable *o, EGIObject *eObject) {
    
    if ( this->lock() == 0 ) {
        
        if ( this->record_ ) {
            
            // Retain the EGI-based object.
            eObject->retain();
            
            // Should be of type AmpDataObject. The default copy status of this object is true ... and it is reversed for convenience below.
            AmpDataObject *aDO = dynamic_cast<AmpDataObject *>(eObject);
            
            // Get the actual sample data.
            // Note that by default the update function receives a data object with its copy state as true. That is, when the getData(...)
            // method is called, a copy of the data will be made. By passing the true argument below, this behaviour is reversed.
            char *dataPtr = aDO->getData(true);
            
            // Place the data obtained into the amplifier buffer. This will be processed on a different thread and
            // written to disk.
            if ((dataPtr != NULL) &&
                (this->sdkWrapper_->ampBuffer != NULL)) {
                this->sdkWrapper_->ampBuffer->writeToBuffer(dataPtr, aDO->getSizeOfData(), NULL);
            }
            
            // Release the EGI-based object.
            eObject->release();
            
        }
        
        this->unlock();
        
    }
    
}

void DataStreamObserver::setRecordingState(bool record) {
    
    if ( this->lock() == 0 ) {
        this->record_ = record;
        
        if ((this->sdkWrapper_ != NULL) &&
            (this->sdkWrapper_->ampBuffer != NULL) &&
            (record == true)) {
            this->sdkWrapper_->ampBuffer->resetBuffer();
        }
        
        this->unlock();
    }
    
}

bool DataStreamObserver::getRecordingState() {
    
    bool rVal = false;
    
    if ( this->lock() == 0 ) {
        rVal = this->record_;
        this->unlock();
    }
    
    return rVal;
    
}

//####################################
// End - Public Section.
//####################################

//####################################
// Protected Section.
//####################################

DataStreamObserver::DataStreamObserver(const DataStreamObserver& source) : EGIObject(source){
#ifdef __USE_EXCEPTIONS__
    throw EGIBase::MethodNotSupported_EGIException("DataStreamObserver::DataStreamObserver\
                                                   (const DataStreamObserver& source)");
#endif //__USE_EXCEPTIONS__
}

DataStreamObserver& DataStreamObserver::operator=(const DataStreamObserver& source){
    EGIObject::operator=(source);
#ifdef __USE_EXCEPTIONS__
    throw EGIBase::MethodNotSupported_EGIException("DataStreamObserver& DataStreamObserver::operator=\
                                                   (const DataStreamObserver& source)");
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
