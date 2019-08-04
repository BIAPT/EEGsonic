/*
 *  PhysioDetection.cpp
 *  @author Robert Bell
 *  @date 2015/10/27
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

#include "PhysioDetection.h"

// EGIBase's utility functions.
#include "UtilityFunctions.h"

// Other includes.
#include <iostream>
#include <stdexcept>

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

// Some useful defines.
#define MAX_NUMBER_OF_PHYSIO_UNITS_SUPPORTED 2
#define PHYSIO_CHECK_DISABLE_COUNTER 250
#define PHYSIO_CONNECTED_COUNTER 1000

// Note: For some reason, after plugging in a physio unit, it momintarily
// begins to cycle its counter, but then returns to a steady state. This causes
// a false disconnect message, followed a few moments later by another connect. The
// PHYSIO_CONNECTED_COUNTER is set to 1000 to avoid this case. You could also set the
// PHYSIO_CHECK_DISABLE_COUNTER higher to achieve a similar effect.

// A structure for maintaining each physio's state.                                                                                                                     
struct PhysioState {

  bool connected;
  unsigned int connectedCounter;
  uint8_t lastDigitalInputValue;

  bool disableCheck;
  unsigned int disableCheckCounter;

};

//####################################
// Public Section.
//####################################

PhysioDetection::PhysioDetection(unsigned int numberOfPhysioUnits) : EGIObject() {

  this->numberOfPhysioUnits_ = numberOfPhysioUnits;

  // We'll initialize this in this class's init method.
  this->physioStates_ = NULL;
  
}

PhysioDetection::~PhysioDetection() {

  if (this->physioStates_ != NULL) {

    for(std::vector<PhysioState *>::iterator itr = this->physioStates_->begin();
	itr != this->physioStates_->end();
	++itr){
      delete *itr;
    }

  }

}

PhysioDetection *PhysioDetection::clone(unsigned int numberOfPhysioUnits) const{
  
  PhysioDetection *rVal = NULL;
  
  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() + "::clone()");
  
  return rVal;
    
}

PhysioDetection *PhysioDetection::create(unsigned int numberOfPhysioUnits) const{
  
  PhysioDetection *rVal = NULL;
  
  try {
        
    rVal = new PhysioDetection(numberOfPhysioUnits);
        
  } catch(std::bad_alloc){
    
    std::cout << this->toString() << ": fatal error: out of memory" << std::endl;
    rVal = NULL;
        
  }
  
  return rVal;
}

PhysioDetection *PhysioDetection::init(EGIObject *eObject){
  
  // Check to make sure we have a supported number of physio units.
  if ((this->getInitialized() == false) &&
      (this->numberOfPhysioUnits_ > 0) &&
      (this->numberOfPhysioUnits_ <= MAX_NUMBER_OF_PHYSIO_UNITS_SUPPORTED)) {

    this->physioStates_ = new std::vector<PhysioState *>();

    if (this->physioStates_ != NULL) {

      for (unsigned int i=0; i<this->numberOfPhysioUnits_; i++) {

	PhysioState *physioState = new PhysioState();
	physioState->connected = false;
	physioState->connectedCounter = PHYSIO_CONNECTED_COUNTER;
	physioState->lastDigitalInputValue = 0;
	physioState->disableCheck = true;
	physioState->disableCheckCounter = PHYSIO_CHECK_DISABLE_COUNTER;

	this->physioStates_->push_back(physioState);
	
      }

    }
    
    // We are now initialized.
    this->setInitialized(true);

  } else {
    EGI_THROW(EGIBase::Init_EGIException, this->toString() +
	      "::init(EGIObject *eObject))");
  }

  return this;
}

PhysioStatus PhysioDetection::detectPhysioUnitState(unsigned int physioUnitIndex,
						    uint8_t digitalInputValue) {

  PhysioStatus rVal = pys_Unknown;

  if (this->physioStates_ != NULL) {

    try {

      PhysioState *physioState = this->physioStates_->at(physioUnitIndex);
      if (physioState != NULL) {

	// To cut down on rapid changes in detection, after detecting that a
	// pyhsio unit has connected or disconnected, further checks are disabled
	// for a period of time governed by the define "PHYSIO_CHECK_DISABLE_COUNTER".
	if (physioState->disableCheck == true) {
	  
	  if (physioState->disableCheckCounter > 0) {
	    
	    physioState->disableCheckCounter--; 
	    physioState->lastDigitalInputValue = digitalInputValue;
	    
	  } else {
	    
	    physioState->disableCheck = false;
	    physioState->disableCheckCounter = PHYSIO_CHECK_DISABLE_COUNTER;
	    
	  }

	  // We will leave the status in the unknown state since we have disabled
	  // the check whilst we wait for things to settle.
	  
	} else if (physioState->connected == false) {
	  
	  // In this case, we are already in the disconnected state and
	  // must decide if we need to transition to the connected state.

	  if (physioState->lastDigitalInputValue == digitalInputValue) {

	    // Physio remains disconnected.
	    rVal = pys_NotConnected;

	  } else {

	    // A unit physio unit has been detected.
	    physioState->connected = true;
	    physioState->connectedCounter = PHYSIO_CONNECTED_COUNTER;
	    
	    // Output a friendly message.
	    std::cout << "info: physio "  << physioUnitIndex << " detected" << std::endl;
	    
	    // Disable the checks to allow for plugging and unplugging.
	    physioState->disableCheck = true;
	    physioState->disableCheckCounter = PHYSIO_CHECK_DISABLE_COUNTER;
	    
	    rVal = pys_NewlyConnected;

	  }
	  
	} else if (physioState->connected == true) {

	  // In this case, we are already in the connected state and
	  // must decide if we need to transition to the disconnected state.
	  
	  if (physioState->lastDigitalInputValue != digitalInputValue) {
	    
	    // Physio remains connected.
	    physioState->connectedCounter = PHYSIO_CONNECTED_COUNTER;
	    physioState->lastDigitalInputValue = digitalInputValue;

	    rVal = pys_Connected;
	    
	  } else {
	    
	    if (physioState->connectedCounter > 0) {
	      physioState->connectedCounter--;

	      // We don't really know what's going on yet, but in the absence of
	      // more information, we'll assume the physio unit is still connected.
	      rVal = pys_Connected;

	    } else {
	      
	      // Physio unit has been disconnected.
	      physioState->connected = false;
	      
	      // Output a friendly message.
	      std::cout << "info: physio " << physioUnitIndex << " disconnected" << std::endl;
	      
	      // Disable the checks to allow for plugging and unplugging.
	      physioState->disableCheck = true;
	      physioState->disableCheckCounter = PHYSIO_CHECK_DISABLE_COUNTER;

	      rVal = pys_NewlyDisconnected;
	      
	    }
	    
	  }
	  
	}
	
      }
      
    } catch (const std::out_of_range& e) {

      std::cout << "error: physio unit index out of range. Index recieved: " << physioUnitIndex << std::endl;

      // Re-throw the exception.
      throw;

    }

  }

  return rVal;
  
}

bool PhysioDetection::isPhysioUnitConnected(unsigned int physioUnitIndex) {

  bool rVal = false;

    if (this->physioStates_ != NULL) {

    try {

      PhysioState *physioState = this->physioStates_->at(physioUnitIndex);
      if (physioState != NULL) {

	rVal = physioState->connected;
	
      }
	
    } catch (const std::out_of_range& e) {

      std::cout << "error: physio unit index out of range. Index recieved: " << physioUnitIndex << std::endl;

      // Re-throw the exception.
      throw;

    }

  }

  return rVal;

}

//####################################
// End - Public Section.
//####################################

//####################################
// Protected Section.
//####################################

PhysioDetection::PhysioDetection(const PhysioDetection& source) : EGIObject(source){

  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::PhysioDetection(const PhysioDetection& source) : EGIObject(source)");

}

PhysioDetection& PhysioDetection::operator=(const PhysioDetection& source){
  EGIObject::operator=(source);

  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::operator=(const PhysioDetection& source)");

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
