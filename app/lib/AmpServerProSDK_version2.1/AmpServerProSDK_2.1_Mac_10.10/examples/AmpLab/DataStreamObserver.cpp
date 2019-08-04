
/*
 *  DataStreamObserver.cpp
 *  @author Robert Bell
 *  @date 2015/09/02
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

#include "DataStreamObserver.h"

// EGIBase's utility functions.
#include "UtilityFunctions.h"

// Other includes.
#include <iostream>
#include <string.h>

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

// Some useful defines.
#define SIZE_OF_PACKET1_HEADER 32
#define SIZE_OF_PACKET1_SAMPLE 1152
#define SIZE_OF_PACKET2_SAMPLE 1264

//####################################
// Public Section.
//####################################

DataStreamObserver::DataStreamObserver(AS_Network_Types::AmpInfo ampInfo) : EGIObject() {

  // Initialize everything.
  this->ampInfo_ = ampInfo;
  this->totalSamplesConnected_ = 1;
  this->scalingFactor_ = 0;
  this->applyScalingFactor_ = true;
  this->collectData_ = false;
  this->finishedCollectingData_ = true;
  this->numberOfSamplesToCollect_ = 0;
  this->numberOfSamplesCollected_ = 0;
  this->data_ = NULL;

  // Set the appropriate scaling factor.
  // Note: Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
  if (this->ampInfo_.amplifierType == AS_Network_Types::naNA300) {
    std::cout << "info: setting scaling factor for NA300 amplifier: 0.0244140625L" << std::endl;
    this->scalingFactor_ = 0.0244140625L;
  } else if (this->ampInfo_.amplifierType == AS_Network_Types::naNA400) {
    std::cout<< "info: setting scaling factor for NA400 amplifier: 0.00009313225L" <<std::endl;
    this->scalingFactor_ = 0.00009313225L;
  } else if (this->ampInfo_.amplifierType == AS_Network_Types::naNA410) {
    std::cout<< "info: setting scaling factor for NA410 amplifier: 0.00009636188L" <<std::endl;
    this->scalingFactor_ = 0.00009636188L;
  } else {
    std::cout << "warning: could not determine appropriate amplifer scaling factor, all values will be zero!" << std::endl;
    this->scalingFactor_ = 0.0L;
  }

  std::cout << "info: will process data for " << this->ampInfo_.numberOfChannels << " channels" << std::endl;
  
}

DataStreamObserver::~DataStreamObserver() {}

// Note that if you block in update, you will effectively block the data stream
// thread, and thus will cease to receive any more data from the stream.
// Though we are performing some operations here, the better solution is to dump data
// to a thread safe buffer and pull from that buffer in a separate thread. That way, you ensure
// that if your data routines take time, you will not miss samples, or otherwise perturb the system.
void DataStreamObserver::update(Observable *o, EGIObject *eObject){
  
  // Don't do anything if we are not collecting data.
  if(this->lock() == 0) {
    if (this->collectData_ == true ) {
      
      // Retain the EGI-based object.
      eObject->retain();
      
      // Should be of type AmpDataObject. The default copy status of this object is true ... and it is reversed for convenience below.
      AmpDataObject *aDO = dynamic_cast<AmpDataObject *>(eObject);
      
      // Get the actual sample data.
      // Note that by default the update function receives a data object with its copy state as true. That is, when the getData(...)
      // method is called, a copy of the data will be made. By passing the true argument below, this behaviour is reversed. This is
      // done in the example and the result is that if it were intended that the memory pointed to by "dataPtr" below were to be
      // persisted outside of the update method (this method), you would have to copy it manually. For this example however, it is
      // nice to not have to worry about the extra memory allocation as we will never save the data.
      char *dataPtr = aDO->getData(true);
      
      // Based on the packet and amplifer type, interpret the format and apply the appropriate converstion.
      if (this->ampInfo_.packetType == AS_Network_Types::pkType1) {
	
	long length = aDO->getSizeOfData();
	unsigned int numberOfSamples = length / SIZE_OF_PACKET1_SAMPLE;
	
	// Convert to packet format 1 type.
	AS_Network_Types::PacketFormat1 *src = reinterpret_cast<AS_Network_Types::PacketFormat1 *>(dataPtr);
	
	for (int i=0; i<numberOfSamples; i++) {
	  
	  if (this->numberOfSamplesCollected_ < this->numberOfSamplesToCollect_) {
	    
	    for ( int channel = 0; channel < this->ampInfo_.numberOfChannels; channel++ ) {
	      
	      // Packet format 1 will always distribute data in network byte order, we'll assume
	      // that we want little endian for this example so that you can see the swap.
	      UtilityFunctions::swapUINT32_t(reinterpret_cast<uint32_t *>(&(src[i].eeg[channel])));
	      
	      // Convert to a double from the float in the packet 1 format.
	      double doubleValue = static_cast<double>(src[i].eeg[channel]);
	      
	      // Apply the scaling factor if desired.
	      // Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
	      if (this->applyScalingFactor_ == true) {
		doubleValue = doubleValue * this->scalingFactor_;
	      }
	      
	      // Set the output data. This is what MATLAB will see!
	      (this->data_)[this->numberOfSamplesCollected_ + this->numberOfSamplesToCollect_ * channel] = doubleValue;
	      
	    }
	    
	    // Update the sample counts.
	    this->numberOfSamplesCollected_++;
	    this->totalSamplesConnected_++;
	    
	  } else {
	    // We have finished collecting, break out of this for-loop, and update the collecting state.
	    this->finishedCollectingData_ = true;
	    break;
	  }
	  
	}
	
      } else if (this->ampInfo_.packetType == AS_Network_Types::pkType2) {
	
	long length = aDO->getSizeOfData();
	unsigned int numberOfSamples = length / SIZE_OF_PACKET2_SAMPLE;
	
	// Convert to packet format 2 type.
	AS_Network_Types::PacketFormat2 *src = reinterpret_cast<AS_Network_Types::PacketFormat2 *>(dataPtr);
	
	// Cycle through the channels to convert to the expected double format.
	for (int i=0; i<numberOfSamples; i++) {
	  
	  if (this->numberOfSamplesCollected_ < this->numberOfSamplesToCollect_) {
	    
	    for ( int channel = 0; channel < this->ampInfo_.numberOfChannels; channel++ ) {
	      
	      // Packet format 2 will always distribute data in little endian byte order, but
	      // due to the fact that in the packet 2 format the values are integers, we need to
	      // convert to a double.
	      double doubleValue = static_cast<double>(src[i].eegData[channel]);
	      
	      // Apply the scaling factor if desired.
	      // Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
	      if (this->applyScalingFactor_ == true) {
		doubleValue = doubleValue * this->scalingFactor_;
	      }
	      
	      // Set the output data. This is what MATLAB will see!
	      (this->data_)[this->numberOfSamplesCollected_ + this->numberOfSamplesToCollect_ * channel] = doubleValue;
	      
	    }
	    
	    // Update the sample count.
	    this->numberOfSamplesCollected_++;
	    this->totalSamplesConnected_++;
	    
	  } else {
	    // We have finished collecting, break out of this for-loop, and update the collecting state.
	    this->finishedCollectingData_ = true;
	    break;
	  }
	  
	}
	
      }
      
      // Release the EGI-based object.
      eObject->release();
      
    }
    
    this->unlock();

  }

}

bool DataStreamObserver::collectData(double *data, uint64_t numberOfSamplesToCollect) {

  bool rVal = false;

  if(this->lock() == 0){

    // Check to see if we are not already collecting.
    if (this->collectData_ == false) {

      // Setup the object to be in collection mode.
      this->collectData_ = true;
      this->finishedCollectingData_ = false;
      this->numberOfSamplesToCollect_ = numberOfSamplesToCollect;
      this->numberOfSamplesCollected_ = 0;
      this->data_ = data;

      // Now we want to wait to see when collecting has finished. We need to
      // make sure to unblock or we will block the update function (which is
      // also monitoring this object's lock.
      this->unlock();
      while (true) {
	usleep(5000);

	// Check to see if we are done.
	this->lock();
	if (this->finishedCollectingData_ == true) {
	  this->collectData_ = false;
	  break;
	}
	this->unlock();

      }

    }

    this->unlock();

  }

  return rVal;

}

void DataStreamObserver::setApplyScalingFactor(bool applyScalingFactor) {

  if(this->lock() == 0){    
    this->applyScalingFactor_ = applyScalingFactor;
    this->unlock();
    
    if (applyScalingFactor == true) { 
      std::cout << "DataStreamObserver: info: apply scaling factor is now on." << std::endl;
    } else {
      std::cout << "DataStreamObserver: info: apply scaling factor is now off." << std::endl;
    }

  }

}

bool DataStreamObserver::getApplyScalingFactor() {
  return this->applyScalingFactor_;
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
