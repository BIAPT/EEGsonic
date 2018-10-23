
/*
 *  MFFFileWriterUtilities.cpp
 *  @author Robert Bell
 *  @date 06/12/2015
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.
 */

#include "MFFFileWriterUtilities.h"

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// General MFF
#include "MFFFactory.h"
#include "LocalAppleMFFFactoryDelegate.h"
#include "MFFFile.h"
#include "MFFUtils.h"

// MFF - Info
#include "Info.h"

// MFF - Epochs
#include "Epochs.h"
#include "Epoch.h"

// MFF - Signal SignalResource
#include "SignalResource.h"
#include "SignalBlock.h"

#include <iostream>
#include <fstream>
#import <Foundation/Foundation.h>

using namespace EGIBase;
using namespace com::egi::services::mff::api;
using namespace com::egi::services::mff::util;

// Some useful defines.
#define SIZE_OF_PACKET1_HEADER 32
#define SIZE_OF_PACKET1_SAMPLE 1152
#define SIZE_OF_PACKET2_SAMPLE 1264
#define CURRENT_MFF_VERSION 3

//####################################
//Public section.
//####################################

//##################
//Constructor(s).
//##################

MFFFileWriterUtilities::MFFFileWriterUtilities() : EGIObject(){}

//##################
//End - Constructor(s).
//##################

//##################
//Destructor.
//##################
MFFFileWriterUtilities::~MFFFileWriterUtilities(){}
//##################
//End - Destructor.
//##################

MFFFileWriterUtilities *MFFFileWriterUtilities::clone() const{
    MFFFileWriterUtilities *rVal = NULL;
    
    try{
        rVal = new MFFFileWriterUtilities(*this);
    }
    catch(EGIBase::MethodNotSupported_EGIException){
        throw;
    }
    
    return rVal;
}

MFFFileWriterUtilities *MFFFileWriterUtilities::create() const{
    MFFFileWriterUtilities *rVal = NULL;
    
    try{
        rVal = new MFFFileWriterUtilities();
    }
    catch(std::bad_alloc){
        std::cout << this->toString() << ": fatal error: out of memory" << std::endl;
    }
    
    return rVal;
}

MFFFileWriterUtilities *MFFFileWriterUtilities::init(EGIObject *eObject){
    return this;
}

bool MFFFileWriterUtilities::createMFFFile(com::egi::services::mff::api::MFFFactory *factory,
                                           std::string mffFileURI,
                                           std::string& message) {
    
    // Check to see if we have a non-empty URI.
    if (mffFileURI == "") {
        message = "error: no URI provided for the MFF file";
        return false;
    }
    
    MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_MFFFile);
    
    if (factory->resourceExistsAtURI(mffFileURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(mffFileURI, resourceType) == false) {
            message = "error: unable to delete existing MFF file resource";
            RELEASE(resourceType);
            return false;
        }
    }
    
    if (factory->createResourceAtURI(mffFileURI, resourceType) == false) {
        message = "error: unable to create MFF file resource";
        RELEASE(resourceType);
        return false;
    }
    
    RELEASE(resourceType);
    return true;
    
}

SignalResource *MFFFileWriterUtilities::createSignalFile(com::egi::services::mff::api::MFFFactory *factory,
                                                         std::string mffFileURI,
                                                         std::string signalFileName,
                                                         std::string& message) {
    
    SignalResource *rVal = NULL;
    
    // Check to see if we have a non-empty URI.
    if ((mffFileURI == "") ||
        (signalFileName == "")) {
        message = "error: invalid signal file URI";
        return NULL;
    }
    
    MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_Signal);
    
    // The info.xml file lives in the root of an MFF file directory structure.
    std::string signalURI = mffFileURI + "/" + signalFileName;
    
    if (factory->resourceExistsAtURI(signalURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(signalURI, resourceType) == false) {
            message = "error: unable to delete existing signal file resource";
            RELEASE(resourceType);
            return NULL;
        }
    }
    
    if (factory->createResourceAtURI(signalURI, resourceType)== true) {
    
        SignalResource *signalResource = dynamic_cast<SignalResource *>(factory->openResourceAtURI(signalURI, resourceType));
        if (signalResource != NULL) {
            rVal = signalResource;
        } else {
            message = "error: could not open " + signalURI + " resource";
        }
        
    } else {
        message = "error: could not open " + signalURI + " resource";
    }
    
    RELEASE(resourceType);
    
    return rVal;
    
}

bool MFFFileWriterUtilities::createInfoFile(MFFFactory *factory,
                                            std::string mffFileURI,
                                            AS_Network_Types::AmpInfo ampInfo,
                                            std::string beginTime,
                                            std::string& message) {
    
    bool rVal = false;
    
    MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_Info);
    
    // The info.xml file lives in the root of an MFF file directory structure.
    std::string infoURI = mffFileURI + "/info.xml";
    
    // Remove any existing info.xml file.
    if (factory->resourceExistsAtURI(infoURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(infoURI, resourceType) == false ) {
            RELEASE(resourceType);
            message = "error: could remove existing info.xml resource";
            return false;
        }
    }
    
    // Now create the resource and populate it accordingly.
    if (factory->createResourceAtURI(infoURI, resourceType) == true) {
        
        Info *info = dynamic_cast<Info *>(factory->openResourceAtURI(infoURI, resourceType));
        
        if (info != NULL) {
            
            info->setMFFVersion(3);
            info->setRecordTime(beginTime);
            info->setMFFVersionPresent(true);
            info->setAmpFirmwareVersion(ampInfo.ampSystemVersion);
            info->setAmpSerialNumber(ampInfo.serialNumber);
            
            info->saveResource();
            
            factory->closeResource(info);
            
            rVal = true;
            
        } else {
            message = "error: could not open info.xml resource";
        }
        
    } else {
        message = "error: could not create info.xml resource";
    }
    
    RELEASE(resourceType);
    
    return rVal;
    
}

bool MFFFileWriterUtilities::createInfoNFile(MFFFactory *factory,
                                             std::string mffFileURI,
                                             InfoN::InfoNFileType infoNFileType,
                                             AS_Network_Types::NetCode netCode,
                                             std::string& message) {
    
    bool rVal = false;
    
    // Determine the infoN.xml filename from it's type.
    // Note: This example only supports creating an EEG version.
    
    std::string infoNFileName = "";
    switch (infoNFileType) {
        case InfoN::kEEG :
            infoNFileName = "info1.xml";
            break;
            
        default:
            message = "error: unsupported InfoN file type.";
            return false;
            break;
    }
    
    MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_InfoN);
    
    // The infoN.xml file lives in the root of an MFF file directory structure.
    std::string infoNURI = mffFileURI + "/" + infoNFileName;
    
    // Remove any existing infoN.xml file of this type.
    if (factory->resourceExistsAtURI(infoNURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(infoNURI, resourceType) == false ) {
            RELEASE(resourceType);
            message = "error: could remove existing " + infoNFileName + " resource";
            return false;
        }
    }
    
    // Now create the resource and populate it accordingly.
    if (factory->createResourceAtURI(infoNURI, resourceType) == true) {
        
        InfoN *infoN = dynamic_cast<InfoN *>(factory->openResourceAtURI(infoNURI, resourceType));
        
        if (infoN != NULL) {
            
            InfoNFileTypeEEG *infoNFileTypeEEG = new InfoNFileTypeEEG();
            
            std::string layoutName = MFFFileWriterUtilities::getLayoutNameForNetType(netCode);
            infoNFileTypeEEG->setMontageName(layoutName);
            infoNFileTypeEEG->setSensorLayoutName(layoutName);
            
            infoN->setInfoNFileType(InfoN::kEEG);
            infoN->setFileTypeInformation(infoNFileTypeEEG);
            
            infoN->saveResource();
            
            factory->closeResource(infoN);
            
            rVal = true;
            
        } else {
            message = "error: could not open " + infoNFileName + " resource";
        }
        
    } else {
        message = "error: could not create " + infoNFileName + " resource";
    }
    
    RELEASE(resourceType);
    
    return rVal;
    
}

bool MFFFileWriterUtilities::createLayoutFile(MFFFactory *factory,
                                              std::string mffFileURI,
                                              AS_Network_Types::NetCode netCode,
                                              MFFResourceType::_MFFResourceType mffType,
                                              std::string& message) {
    
    bool rVal = false;
    
    std::string layoutFileName = "";
    std::string layoutType = "";
    
    // Check to see we have a valid type and assing the file name and type appropriately.
    if (mffType == MFFResourceType::kMFF_RT_Coordinates) {
        layoutFileName = "coordinates.xml";
        layoutType = "CoordinateLayouts";
    } else if (mffType == MFFResourceType::kMFF_RT_SensorLayout) {
        layoutFileName = "sensorLayout.xml";
        layoutType = "SensorLayouts";
    } else {
        message = "error: incorrect resource type provided";
    }
    
    // Now that we have a valid resource type, we can create it.
    MFFResourceType *resourceType = new MFFResourceType(mffType);
    
    // The layout file lives in the root of an MFF file directory structure.
    std::string layoutURI = mffFileURI + "/" + layoutFileName;
    
    // Remove any existing info.xml file.
    if (factory->resourceExistsAtURI(layoutURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(layoutURI, resourceType) == false ) {
            RELEASE(resourceType);
            message = "error: could remove existing " + layoutFileName + " resource";
            return false;
        }
    }
    
    // Copy the correct coordinates file based on net code.
    std::string sourceURI = MFFFileWriterUtilities::getLayoutURIForNetType(netCode, layoutType);
    
    if (factory->copyResourceAtURI(sourceURI, layoutURI, resourceType, NULL) == true) {
        rVal = true;
    } else {
        if (mffType == MFFResourceType::kMFF_RT_Coordinates) {
            message = "error: unable to copy coordinates.xml file";
        } else if (mffType == MFFResourceType::kMFF_RT_SensorLayout) {
            message = "error: unable to copy sensorLayout.xml file";
        }
    }
    
    RELEASE(resourceType);
    return rVal;
    
}

std::string MFFFileWriterUtilities::getLayoutNameForNetType(AS_Network_Types::NetCode netCode) {
    
    std::string rVal = "";
    
    switch (netCode) {
        case AS_Network_Types::GSN64_2_0:
            rVal = "Geodesic Sensor Net 64 2.0";
            break;
        case AS_Network_Types::GSN128_2_0:
            rVal = "Geodesic Sensor Net 128 2.1";
            break;
        case AS_Network_Types::GSN256_2_0:
            rVal = "Geodesic Sensor Net 256 2.1";
            break;
        case AS_Network_Types::HCGSN32_1_0:
            rVal = "HydroCel GSN 32 1.0";
            break;
        case AS_Network_Types::HCGSN64_1_0:
            rVal = "HydroCel GSN 64 1.0";
            break;
        case AS_Network_Types::HCGSN128_1_0:
            rVal = "HydroCel GSN 128 1.0";
            break;
        case AS_Network_Types::HCGSN256_1_0:
            rVal = "HydroCel GSN 256 1.0";
            break;
        case AS_Network_Types::MCGSN32_1_0:
            rVal = "MicroCel GSN 100 32 1.0";
            break;
        case AS_Network_Types::MCGSN64_1_0:
            rVal = "MicroCel GSN 100 64 1.0";
            break;
        case AS_Network_Types::MCGSN128_1_0:
            rVal = "MicroCel GSN 100 128 1.0";
            break;
        case AS_Network_Types::MCGSN256_1_0:
            rVal = "MicroCel GSN 100 256 1.0";
            break;
        case AS_Network_Types::NoNet:
            rVal = "Net Not Connected";
            break;
        default:
            rVal = "Unknown Net Status";
            break;
    }
    
    return rVal;
    
}

std::string MFFFileWriterUtilities::getLayoutURIForNetType(AS_Network_Types::NetCode netCode, std::string layoutType) {
    
    std::string rVal = "";
    
    switch (netCode) {
        case AS_Network_Types::GSN64_2_0:
            rVal = MFFFileWriterUtilities::getURIForResource("Geodesic Sensor Net 64 2.0", "xml", layoutType);
            break;
        case AS_Network_Types::GSN128_2_0:
            rVal = MFFFileWriterUtilities::getURIForResource("Geodesic Sensor Net 128 2.1", "xml", layoutType);
            break;
        case AS_Network_Types::GSN256_2_0:
            rVal = MFFFileWriterUtilities::getURIForResource("Geodesic Sensor Net 256 2.1", "xml", layoutType);
            break;
        case AS_Network_Types::HCGSN32_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("HydroCel GSN 32 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::HCGSN64_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("HydroCel GSN 64 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::HCGSN128_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("HydroCel GSN 128 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::HCGSN256_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("HydroCel GSN 256 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::MCGSN32_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("MicroCel GSN 100 32 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::MCGSN64_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("MicroCel GSN 100 64 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::MCGSN128_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("MicroCel GSN 100 128 1.0", "xml", layoutType);
            break;
        case AS_Network_Types::MCGSN256_1_0:
            rVal = MFFFileWriterUtilities::getURIForResource("MicroCel GSN 100 256 1.0", "xml", layoutType);
            break;
        default:
            break;
    }
    
    return rVal;
    
}

std::string MFFFileWriterUtilities::getURIForResource(std::string name,
                                                      std::string extension,
                                                      std::string type) {
    
    std::string rVal("");
    
    // Obtain a reference to the main bundle.
    CFBundleRef mainbundle = CFBundleGetMainBundle();
    
    // Get the resource URL.
    CFURLRef resourceURLRef = CFBundleCopyResourceURL(mainbundle,
                                                      CFStringCreateWithCString (NULL, name.c_str(), kCFStringEncodingUTF8),
                                                      CFStringCreateWithCString (NULL,extension.c_str(), kCFStringEncodingUTF8),
                                                      CFStringCreateWithCString (NULL,type.c_str(), kCFStringEncodingUTF8));
    
    // Convert to a string reference.
    CFStringRef resourceRef = CFURLCopyFileSystemPath(resourceURLRef,kCFURLPOSIXPathStyle);
    
    // Get the system's encoding.
    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
    
    // Obtain the c-style string so that we can build the return type.
    const char *resource = CFStringGetCStringPtr(resourceRef, encodingMethod);
    
    if (resource != NULL) {
        rVal = resource;
    }
    
    return rVal;
}

bool MFFFileWriterUtilities::createEpochFile(MFFFactory *factory,
                                             std::string mffFileURI,
                                             uint64_t beginTime,
                                             uint64_t endTime,
                                             uint64_t blockCount,
                                             std::string& message) {
    
    bool rVal = false;
    
    MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_Epochs);
    
    // The info.xml file lives in the root of an MFF file directory structure.
    std::string epochsURI = mffFileURI + "/epochs.xml";
    
    // Remove any existing epochs.xml file.
    if (factory->resourceExistsAtURI(epochsURI, resourceType) == true) {
        
        if (factory->deleteResourceAtURI(epochsURI, resourceType) == false ) {
            RELEASE(resourceType);
            message = "error: could remove existing epochs.xml resource";
            return false;
        }
    }
    
    // Now create the resource and populate it accordingly.
    if (factory->createResourceAtURI(epochsURI, resourceType) == true) {
        
        Epochs *epochs = dynamic_cast<Epochs *>(factory->openResourceAtURI(epochsURI, resourceType));
        
        if (epochs != NULL) {
            
            std::vector<Epoch *> *epochsList = new std::vector<Epoch *>();
            
            Epoch *epoch = new Epoch();
            epoch->setBeginTime(beginTime);
            epoch->setEndTime(endTime);
            epoch->setFirstBlock(1);
            epoch->setLastBlock(blockCount);
            
            epochsList->push_back(epoch);
            epochs->setEpochs(epochsList);
            
            epochs->saveResource();
            factory->closeResource(epochs);
            
            rVal = true;
            
        } else {
            message = "error: could not open epochs.xml resource";
        }
        
    } else {
        message = "error: could not create epochs.xml resource";
    }
    
    RELEASE(resourceType);
    
    return rVal;
    
}

bool MFFFileWriterUtilities::writeSignalBlock(com::egi::services::mff::api::SignalResource *resource,
                                              char *data,
                                              int64_t sizeOfData,
                                              AS_Network_Types::AmplifierType amplifierType,
                                              AS_Network_Types::PacketType packetType,
                                              int numberOfChannels,
                                              int frequency,
                                              bool firstBlock,
                                              bool continuationBlock,
                                              AS_Network_Types::NetCode &netCode) {
    
    bool rVal = false;
    
    netCode = AS_Network_Types::Unknown;
    AS_Network_Types::NetCode lastDetectedNetCode = AS_Network_Types::Unknown;
    AS_Network_Types::NetCode detectedNetCode = AS_Network_Types::Unknown;
    int netCodeCount = 1000; // We'll wait for 1000 samples before we believe a net code.
    
    float scalingFactor = 0.0f;
    
    if (amplifierType == AS_Network_Types::naNA300) {
        scalingFactor = 0.0244140625f;
    } else if (amplifierType == AS_Network_Types::naNA400) {
        scalingFactor = 0.00015522042f;
    } else if (amplifierType == AS_Network_Types::naNA410) {
        scalingFactor = 0.00009636188f;
    } else {
        std::cout << "warning: could not determine appropriate amplifer scaling factor, all values will be zero!" << std::endl;
        scalingFactor = 0.0f;
    }
    
    int64_t numberOfSamples = 0;
    float *blockData = NULL;
    int numberOfChannelsWithRef = numberOfChannels + 1;
    
    // Based on the packet and amplifer type, interpret the format and apply the appropriate converstion.
    if (packetType == AS_Network_Types::pkType1) {
        
        numberOfSamples = sizeOfData / SIZE_OF_PACKET1_SAMPLE;
        blockData = new float[numberOfChannelsWithRef * numberOfSamples];
        
        // Convert to packet format 1 type.
        AS_Network_Types::PacketFormat1 *src = reinterpret_cast<AS_Network_Types::PacketFormat1 *>(data);
        
        for (int sample=0; sample<numberOfSamples; sample++) {
            
            // Check the net code.
            uint8_t *headerAsByteArray = reinterpret_cast<uint8_t *>(src[sample].header);
            
            // We have to do a little extra work to extract the net code from the Packet 1 format.
            uint8_t byte = headerAsByteArray[26];
            AS_Network_Types::NetCode netCode = (AS_Network_Types::NetCode)((byte & 0x78) >> 3);
            
            if (netCode != detectedNetCode) {
                
                if (netCodeCount == 1000) {
                    lastDetectedNetCode = netCode;
                    netCodeCount--;
                } else if (netCodeCount > 0) {
                    
                    if (netCode == lastDetectedNetCode) {
                        netCodeCount--;
                    } else {
                        netCodeCount = 1000;
                    }
                    
                } else {
                    detectedNetCode = netCode;
                    netCodeCount = 1000;
                }
            }
            
            for ( int channel = 0; channel < numberOfChannelsWithRef; channel++ ) {
                
                // Packet format 1's EEG data is in float format already, so unlike Packet format 2 below,
                // we do not need to cast.
                float floatValue = 0.0;
                
                // Check for the reference channel.
                if ( channel == (numberOfChannelsWithRef-1)) {
                    floatValue = src[sample].ref;
                } else {
                    floatValue = src[sample].eeg[channel];
                }
                
                // Packet format 1 will always distribute data in network byte order, we'll assume
                // that we want little endian for this example so that you can see the swap.
                UtilityFunctions::swapUINT32_t(reinterpret_cast<uint32_t *>(&(floatValue)));
                
                // Apply the scaling factor.
                // Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
                floatValue = floatValue * scalingFactor;
                
                blockData[(channel * numberOfSamples) + sample] = floatValue;
                
            }
            
        }
        
    }  else if (packetType == AS_Network_Types::pkType2) {
        
        numberOfSamples = sizeOfData / SIZE_OF_PACKET2_SAMPLE;
        blockData = new float[numberOfChannelsWithRef * numberOfSamples];
        
        // Convert to packet format 2 type.
        AS_Network_Types::PacketFormat2 *src = reinterpret_cast<AS_Network_Types::PacketFormat2 *>(data);
        
        // Cycle through the channels to convert to the expected double format.
        for (int sample=0; sample<numberOfSamples; sample++) {
            
            // Check the net code.
            if (src[sample].netCode != detectedNetCode) {
                
                if (netCodeCount == 1000) {
                    lastDetectedNetCode = (AS_Network_Types::NetCode)src[sample].netCode;
                    netCodeCount--;
                } else if (netCodeCount > 0) {
                    
                    if (src[sample].netCode == lastDetectedNetCode) {
                        netCodeCount--;
                    } else {
                        netCodeCount = 1000;
                    }
                    
                } else {
                    detectedNetCode = (AS_Network_Types::NetCode)src[sample].netCode;
                    netCodeCount = 1000;
                }
            }
            
            for ( int channel = 0; channel < numberOfChannelsWithRef; channel++ ) {
                
                // Packet format 2 will always distribute data in little endian byte order, but
                // due to the fact that in the packet 2 format the values are integers, we need to
                // convert to a float.
                float floatValue = 0.0;
                
                // Check for the reference channel.
                if ( channel == (numberOfChannelsWithRef-1)) {
                    floatValue = static_cast<float>(src[sample].refMonitor);
                } else {
                    floatValue = static_cast<float>(src[sample].eegData[channel]);
                }
                
                // Apply the scaling factor.
                // Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
                floatValue = floatValue * scalingFactor;
                
                blockData[(channel * numberOfSamples) + sample] = floatValue;
                
            }
            
        }
        
    } else {
        return rVal;
    }
    
    SignalBlock *block = new SignalBlock();
    
    // Create the header.
    
    
    // This will change in size as we populate the header values.
    //
    // Note: In future versions of the MFF, you will not have to set the
    // header size manually.
    int32_t headerSize = (sizeof(int32_t) * 3);
    
    if (firstBlock == true) {
        block->setVersion(CURRENT_MFF_VERSION);
    } else {
        block->setVersion(0);
    }
    
    block->setDataBlockSize((int32_t)(sizeof(float) * numberOfChannelsWithRef * numberOfSamples));
    block->setNumberOfSignals(numberOfChannelsWithRef);
    
    headerSize += (numberOfChannelsWithRef * sizeof(int32_t));
    int32_t *offsets = new int32_t[numberOfChannelsWithRef];
    int32_t offsetIncrement = ((int32_t)numberOfSamples) * sizeof(float);
    offsets[0] = 0;
    for(int i = 1; i < numberOfChannelsWithRef; i++){
        offsets[i] = ( offsetIncrement + offsets[i - 1] );
    }
    block->setOffsets(offsets);
    
    // Signal depths and frequencies occupy a packed format in the MFF
    // and thus the header size is only increased once for both.
    headerSize += (numberOfChannelsWithRef * sizeof(int32_t));
    int32_t *signalDepths = new int32_t[numberOfChannelsWithRef];
    for(int i = 0; i < numberOfChannelsWithRef; i++){
        signalDepths[i] = sizeof(int32_t) * 8; // In bits.
    }
    block->setSignalDepth(signalDepths);
    
    int32_t * frequencies = new int32_t[numberOfChannelsWithRef];
    for(int i = 0; i < numberOfChannelsWithRef; i++){
        frequencies[i] = frequency;
    }
    block->setSignalFrequency(frequencies);
    
    // We include an optional header in the first block.
    if (firstBlock == true) {
        int32_t optionalHeaderSize = 24;
        char *optHeader = new char[optionalHeaderSize];
        
        *(int32_t*)(optHeader +  0) = 1;
        *(int64_t*)(optHeader +  4) = 0;    // The number of blocks will be filled in when closing the file.
        *(int64_t*)(optHeader +  12) = 0;   // The number of samples will be filled in when closing the file.
        *(int32_t*)(optHeader +  20) = numberOfChannelsWithRef;
        
        headerSize += (sizeof(int32_t));
        block->setOptionalHeaderSize(optionalHeaderSize);
        
        headerSize += optionalHeaderSize;
        block->setOptionalHeader(optHeader);
        
    }
    
    headerSize += (sizeof(int32_t));
    block->setHeaderSize(headerSize);
    
    
    block->setData((char *)blockData);
    
    // Debug.
    //std::cout << "header size: " << block->getHeaderSize() << std::endl;
    //std::cout << "block data size: " << block->getDataBlockSize() << std::endl;
    
    // Now write out the signal block and cleanup.
    if (resource->writeSignalBlock(block) != NULL) {
        
        RELEASE(block);
        
        // Write the net code.
        netCode = detectedNetCode;
        
        rVal = true;
    }
    
    return rVal;
    
}

bool MFFFileWriterUtilities::writeClosingCountsToSignalFile(com::egi::services::mff::api::MFFFactory *factory,
                                                            std::string mffFileURI,
                                                            std::string signalFileName,
                                                            uint64_t blockCount,
                                                            uint64_t sampleCount) {
    
    bool rVal = false;
    
    try {
        
        MFFResourceType *resourceType = new MFFResourceType(MFFResourceType::kMFF_RT_Signal);
        
        // The info.xml file lives in the root of an MFF file directory structure.
        std::string signalURI = mffFileURI + "/" + signalFileName;
        
        SignalResource *signalResource = dynamic_cast<SignalResource *>(factory->openResourceAtURI(signalURI,resourceType));
        
        if (signalResource != NULL) {
            
            if(signalResource->loadResource() == true) {
                
                // We need to determing the header size in order to place the block and sample
                // count in the correct locations. These counts are for the entire file, and
                // Net Station uses these as global information about the file. Typically, this
                // information is not known at the time the first block is written, hence the
                // existance of this function.
                
                int32_t headerSize = 0;
                std::vector<SignalBlock *> *signalBlocks = signalResource->getSignalBlocks();
                if (signalBlocks->size() > 0) {
                    SignalBlock *firstSignalBlock = signalBlocks->at(0);
                    headerSize = firstSignalBlock->getHeaderSize();
                    
                    std::ofstream file;
                    file.open(signalResource->getURI().c_str(), std::ios::in|std::ios::binary|std::ios::out);
                    if (file.good()) {
                        
                        file.seekp(std::ios::beg);
                        file.seekp(headerSize - 20);
                        file.write(reinterpret_cast<const char *>(&blockCount),8);
                        file.write(reinterpret_cast<const char *>(&sampleCount),8);
                        file.close();
                        
                    }
                    
                }
                
                rVal = true;
                
            }
            
            // Close the signal file.
            factory->closeResource(signalResource);
        }
        
    } catch (...) {
        
    }
    
    return rVal;
    
}

//####################################
//Class methods.
//####################################
//####################################
//End - Class methods.
//####################################

//####################################
//End - Public section.
//####################################

//####################################
//Protected section.
//####################################

MFFFileWriterUtilities::MFFFileWriterUtilities(const MFFFileWriterUtilities& source) : EGIObject(source){
    EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() + "::MFFFileWriterUtilities\
              (const MFFFileWriterUtilities& source)");
}

MFFFileWriterUtilities& MFFFileWriterUtilities::operator=(const MFFFileWriterUtilities& source){
    EGIObject::operator=(source);
    
    EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() + "::operator=\
              (const MFFFileWriterUtilities& source)");
    return *this;
}

//####################################
//End - Protected section.
//####################################

//####################################
//Private section.
//####################################
//####################################
//End - Private section.
//####################################
