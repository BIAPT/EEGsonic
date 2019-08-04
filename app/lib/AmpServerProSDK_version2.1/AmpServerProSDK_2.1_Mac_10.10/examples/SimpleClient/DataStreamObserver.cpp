/*
 *  DataStreamObserver.cpp
 *  @author Robert Bell
 *  @date 2015/09/02
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

#include "DataStreamObserver.h"

// This example's includes.
#include "PhysioDetection.h"

// EGIBase's utility functions.
#include "UtilityFunctions.h"

// Other includes.
#include <iostream>
#include <string.h>
#include <sys/time.h>

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

// Some useful defines.
#define SIZE_OF_PACKET1_HEADER 32
#define SIZE_OF_PACKET1_SAMPLE 1152
#define SIZE_OF_PACKET2_SAMPLE 1264
#define NUMBER_OF_SUPPORTED_PHYSIO_UNITS 2

//###
// Non-class function definitions.
//###

// Gets the system time.
static inline uint64_t getSystemTime();

//####################################
// Public Section.
//####################################

DataStreamObserver::DataStreamObserver(AS_Network_Types::AmpInfo ampInfo) : ObserverPattern::Observer() {

  this->ampInfo_ = ampInfo;
  this->lastPacketCounter_ = 0;
  this->sampleCount_ = 1;
  
  // Set the appropriate scaling factor.
  // Note: Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
  if (this->ampInfo_.amplifierType == AS_Network_Types::naNA300) {
    std::cout << "info: setting scaling factor for NA300 amplifier: 0.0244140625f" << std::endl;
    this->scalingFactor_ = 0.0244140625f;
  } else if (this->ampInfo_.amplifierType == AS_Network_Types::naNA400) {
    std::cout<< "info: setting scaling factor for NA400 amplifier: 0.00009313225f" <<std::endl;
    this->scalingFactor_ = 0.00015522042f;
  } else if (this->ampInfo_.amplifierType == AS_Network_Types::naNA410) {
    std::cout<< "info: setting scaling factor for NA400 amplifier: 0.00009313225f" <<std::endl;
    this->scalingFactor_ = 0.00009636188f;
  } else {
    std::cout << "warning: could not determine appropriate amplifer scaling factor, all values will be zero!" << std::endl;
    this->scalingFactor_ = 0.0f;
  }

  // We want to be able to provide information as to when physio units are and are not detected.
  try {
    this->physioDetection_ = (new PhysioDetection(NUMBER_OF_SUPPORTED_PHYSIO_UNITS))->init(NULL);
  } catch (...) {
    std::cout << "error: unable to initialize physio detection" << std::endl;
    this->physioDetection_ = NULL;
  }

  // I have no idea why, it's just what's used.
  this->batteryScaleTemp_ = 1.0 / 28.5;

  // Set the last system time.
  this->lastSystemTime_ = getSystemTime();

  // Setup debug outputs.
  this->outputSampleStatisticsDebug_ = false;
  this->outputPhysioDebug_ = false;

  std::cout << "info: will process data for " << this->ampInfo_.numberOfChannels << " channels" << std::endl;
  
}

DataStreamObserver::~DataStreamObserver() {}

// Note that if you block in update, you will effectively block the data stream
// thread, and thus will cease to receive any more data from the stream.
// Though we are performing some operations here, the better solution is to dump data
// to a thread safe buffer and pull from that buffer in a separate thread. That way, you ensure
// that if your data routines take time, you will not miss samples, or otherwise perturb the system.
void DataStreamObserver::update(Observable *o, EGIObject *eObject){
  
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

    for (int sample=0; sample<numberOfSamples; sample++) {
      
      for ( int channel = 0; channel < this->ampInfo_.numberOfChannels; channel++ ) {
	
	// Packet format 1 will always distribute data in network byte order, we'll assume
	// that we want little endian for this example so that you can see the swap.
	UtilityFunctions::swapUINT32_t(reinterpret_cast<uint32_t *>(&(src[sample].eeg[channel])));
	
	// Packet format 1's EEG data is in float format already, so unlike Packet format 2 below,
	// we do not need to cast.
	float floatValue = src[sample].eeg[channel];

	// Apply the scaling factor.
	// Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
	floatValue = floatValue * this->scalingFactor_;
	
	// For reference in this example, print out channel 0.
	if ( channel==0 ) {
	  std::cout << "Sample count: " << this->sampleCount_ << " channel 0 (1): " << floatValue << std::endl;
	}
	
      }
      
      // Update the sample count.
      this->sampleCount_++;
      
    }
    
  } else if (this->ampInfo_.packetType == AS_Network_Types::pkType2) {
    
    long length = aDO->getSizeOfData();
    unsigned int numberOfSamples = length / SIZE_OF_PACKET2_SAMPLE;

    // Physio status information.
    int32_t status = 0;
    int16_t value = 0;
    int32_t battery_voltageLevel = 0;
    int32_t battery_temperature = 0;
    int32_t battery_status = 0;
    bool battery_ACPower = false;
    bool battery_fault =  false;
    bool battery_charging = false;
    bool battery_discharging = false;
    int16_t heartRate = 0;
    
    // Convert to packet format 2 type.
    AS_Network_Types::PacketFormat2 *src = reinterpret_cast<AS_Network_Types::PacketFormat2 *>(dataPtr);
    
    // Cycle through the channels to convert to the expected double format.
    for (int sample=0; sample<numberOfSamples; sample++) {

      // A diagnostic check for missing packets.
      if ((src[sample].packetCounter != 1) && // Don't check the first packet.
	  src[sample].packetCounter != (this->lastPacketCounter_ + 1)) {
	// This is not good- output an error.
	std::cout << "error: dropped packet- last count: " << this->lastPacketCounter_ << ": new count: " << src[sample].packetCounter << std::endl;
      }
      this->lastPacketCounter_ = src[sample].packetCounter;
      
      // EEG Data.
      
      for ( int channel = 0; channel < this->ampInfo_.numberOfChannels; channel++ ) {
	
	// Packet format 2 will always distribute data in little endian byte order, but
	// due to the fact that in the packet 2 format the values are integers, we need to
	// convert to a float.
	float floatValue = static_cast<float>(src[sample].eegData[channel]);

	// Apply the scaling factor.
	// Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
	floatValue = floatValue * this->scalingFactor_;
	
	// For reference in this example, print out channel 0.
	if ( channel==0 ) {
	  //######
	  // Uncomment the below line to see output.
	  //######
	  //std::cout << "Sample count: " << this->sampleCount_ << " eeg channel 1 (1) value: " << floatValue << " actual sample packet counter: " << src[sample].packetCounter << std::endl;
	}
	
      }

      // Physio Data.
      // There is no direct way to "ask" if a Physio unit is plugged in. The only way to do it is to monitor packets,
      // and this will be demonstrated below. For an NA400, two Physio unites are supported, and the data is placed in the
      // following locations:
      //
      // PacketFormat2_PIB_AUX   pib1_aux;
      // PacketFormat2_PIB_AUX   pib2_aux;
      //
      // And..
      //
      // int32_t pib1_Data[ 16 ];
      // int32_t pib2_Data[ 16 ];
      //
      // Each unit has 16 channels. In this example, like EEG, we will print out a single value (channel 3), but we
      // will also monitor for when the units are connected.
      //
      // All the work for monitoring a physio unit has been placed into PhysioDetection class, the use of which is
      // demonstrated now.
      if (this->physioDetection_ != NULL) {

	for (int physioUnit=0; physioUnit<NUMBER_OF_SUPPORTED_PHYSIO_UNITS; physioUnit++) {

	  // Select the correct physio digital input.
	  AS_Network_Types::PacketFormat2_PIB_AUX *pibAux = NULL;
	  if (physioUnit == 0) {
	    pibAux = &(src[sample].pib1_aux);
	  } else if (physioUnit == 1) {
	    pibAux = &(src[sample].pib2_aux);
	  }

	  // Ask the physio status object for the status of the desired physio unit.
	  PhysioStatus physioStatus = this->physioDetection_->detectPhysioUnitState(physioUnit, pibAux->digitalInputs);
	  if (physioStatus == pys_NewlyDisconnected) {  
	    std::cout << "info: physio detection reports that physio unit " << physioUnit << " has been disconnected" << std::endl;
	  } else if (physioStatus == pys_NewlyConnected) {
	    std::cout << "info: physio detection reports that physio unit " << physioUnit << " has been connected" << std::endl;
	  }

	}

      }
      
      // Note that since you cannot determine the state of the physio unit until you begin to
      // receive packets, it is better to assume it's there first, and do something about it
      // should it not show up. In this example, to cut down on complexity, we'll just report a
      // physio channel value regardless of whether a physio unit is plugged in. We will also only
      // look at physio unit 1. For a real application with all the bells and whistles, it would
      // probably be best to expand on the logic here.
      for ( int pibChannel = 0; pibChannel < 16; pibChannel++ ) {
	
	// Packet format 2 will always distribute data in little endian byte order, but
	// due to the fact that in the packet 2 format the values are integers, we need to
	// convert to a float.
	float floatValue = static_cast<float>(src[sample].pib1_Data[pibChannel]);

	// Apply the scaling factor.
	// Scaling factors can be found in the document "Scaling Factors - AD unit to microvolt".
	floatValue = floatValue * this->scalingFactor_;
	
	// For reference in this example, print out channel 3.
	if ( pibChannel==2 ) {
	  //######
	  // Uncomment the below line to see output.
	  //######
	  //std::cout << "Sample count: " << this->sampleCount_ << " pib channel 3 (1) value: " << floatValue << " actual sample packet counter: " << src[sample].packetCounter << std::endl;
	}
	
      }
      
      // Update the sample count.
      this->sampleCount_++;

      if ((this->sampleCount_ % 1000) == 0) {
	
	if (this->outputSampleStatisticsDebug_ == true) {
	  std::cout << "info: collected: " << this->sampleCount_ << " samples" << std::endl;
	}
	
	// Estimate the sampling rate. Note, this is just an estimate for debugging purposes.
	uint64_t systemTime = getSystemTime();
	int difference = systemTime - this->lastSystemTime_;
	int sampleRatePerSecond = 1000000000 / difference;

	if ((this->outputSampleStatisticsDebug_ == true) &&
	    (difference > 0)) {
	  std::cout << "info: estimated sampling rate: " << sampleRatePerSecond << "/s" << std::endl;
	}
	
	this->lastSystemTime_= getSystemTime();
	
	if (this->physioDetection_ != NULL) {

	  for (int physioUnit=0; physioUnit<NUMBER_OF_SUPPORTED_PHYSIO_UNITS; physioUnit++){
	    
	    // Select the correct physio digital input.
	    AS_Network_Types::PacketFormat2_PIB_AUX *pibAux = NULL;
	    if (physioUnit == 0) {
	      pibAux = &(src[sample].pib1_aux);
	    } else if (physioUnit == 1) {
	      pibAux = &(src[sample].pib2_aux);
	    }

	    if (this->physioDetection_->isPhysioUnitConnected(physioUnit) == true) {
	      
	      // I guess all the below made sense to someone, at some time. It does not really fit
	      // with how the rest of the data is shipped over, but there you go. Just copy the below
	      // into your code and don't think about it too much.
	      value = *(int16_t*)&(pibAux->batteryLevel);
	      status = pibAux->status;
	      battery_voltageLevel = value & 0xFFF; //0xFFF upper 4 bits used for battery status.
	      battery_temperature = (2370 - (*(int16_t*)&(pibAux->temperature))) * this->batteryScaleTemp_;
	      battery_status = (value & 0xF000) >> 12;
	      battery_ACPower = battery_status & 0x2;
	      battery_fault =  (battery_status & 0xE) == 0x2;
	      battery_charging = (battery_status & 0xE) == 0x6;
	      battery_discharging = (battery_status & 0xE) == 0xA;
	      
	      // Heartbeat.
	      value = *(int16_t*)&(pibAux->heartRate);
	      heartRate = ((value & 0x300) >> 1) + (value &0x7F);
	      
	      if (this->outputPhysioDebug_ == true) {
		std::cout << "------" << std::endl;
		std::cout << "info: physio unit " << physioUnit << " information:" << std::endl;
		std::cout << "info: firmware version: " << status << std::endl;
		std::cout << "info: battery temperature: " << battery_temperature << "C (acceptable range 15C - 60C)"<< std::endl;
		std::cout << "info: battery voltage: " << battery_voltageLevel << " (acceptable level range 1168 - 1590)" << std::endl;
		std::cout << "info: battery (ac power): " << battery_ACPower << std::endl;
		std::cout << "info: battery (fault): " << battery_fault << std::endl;
		std::cout << "info: : battery (charging): " << battery_charging << std::endl;
		std::cout << "info: : battery (discharging): " << battery_discharging << std::endl;

		// For completeness, here are some of the other fields.
		std::cout << "info: sp02: " << pibAux->sp02 << "%" << std::endl; // A value from 0-100 in percent.
		std::cout << "info: heart rate: " << heartRate << std::endl;

		std::cout << "------" << std::endl;
	      }

	    }

	  }

	}
	
      }
      
    }
    
  }
  
  // Release the EGI-based object.
  eObject->release();
  
}

void DataStreamObserver::setSampleStatisticsDebuggingOutput(bool sampleStatisticsDebuggingOutput){

  this->outputSampleStatisticsDebug_ = sampleStatisticsDebuggingOutput;

}

void DataStreamObserver::setPhysioDebuggingOutput(bool physioDebuggingOutput) {
  
  this->outputPhysioDebug_ = physioDebuggingOutput;

}

//####################################
// End - Public Section.
//####################################

//####################################
// Protected Section.
//####################################

DataStreamObserver::DataStreamObserver(const DataStreamObserver& source) : EGIObject(source){
  
  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::DataStreamObserver(const DataStreamObserver& source) : EGIObject(source)");
  
}

DataStreamObserver& DataStreamObserver::operator=(const DataStreamObserver& source){
  EGIObject::operator=(source);
  
  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::operator=(const DataStreamObserver& source)");

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

// Gets the system time.
static inline uint64_t getSystemTime(){

  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000LL) + tv.tv_usec;

}
