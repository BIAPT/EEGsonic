/*
 *  AmpServerInterface.cpp
 *  @author Robert Bell
 *  @date 2011/09/14
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

// The header.
#include "AmpServerInterface.h"

// Helper Classes.
#include "NotificationObserver.h"
#include "DataStreamObserver.h"

// Other Includes.
#include <iostream>
#include <ios>
#include <fstream>

// Server Ports.
#define SERVER_COMMAND_PORT 9877
#define SERVER_NOTIFICATION_PORT 9878
#define SERVER_STREAM_PORT 9879

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

// Static Member Initialization.
AmpServerInterface* AmpServerInterface::theAmpServer = NULL;

AmpServerInterface* AmpServerInterface::GetAmpServer() {

   if (AmpServerInterface::theAmpServer) {
      return AmpServerInterface::theAmpServer;
   } else {
      return (AmpServerInterface::theAmpServer = new AmpServerInterface);
   }

}

AmpServerInterface::AmpServerInterface() {

  this->ampID_ = 0; // Note: In this example, we will always assume the amplifier ID is zero.
  this->client_ = NULL;
  this->connected_ = false;
  this->notificationObserver_ = NULL;
  this->dataStreamObserver_ = NULL;

}

AmpServerInterface::~AmpServerInterface() {

  RELEASE(this->notificationObserver_);
  RELEASE(this->dataStreamObserver_);
  this->client_->disconnect();

}

int AmpServerInterface::connect( char* ipAddress ) {

  int rVal = 1; // A value of one is used for failure (to match that of the SDK client's connect function.

  if ( this->connected_ == false ) {

    // Create a client object.
    this->client_ = new AS_Network_Client();
    
    // Add an observer to grab notifications.
    this->notificationObserver_ = new NotificationObserver();
    this->client_->addNotificationObserver(this->notificationObserver_, NULL);
    
    // Create a connection prefs instance. The defaults are fine except for the server address, which for
    // this example, we'd like the option to change.
    AS_Network_Types::ConnPrefsRef connPrefsRef = AS_Network_Types::createConnPrefs();
    delete connPrefsRef->serverAddress; // Remove the default.
    connPrefsRef->serverAddress = ipAddress;
    
    if ( this->client_->connect( connPrefsRef ) == 0 ) {
      
      if ( this->client_->getNumberOfAmps() > 0 ) {
	
	// Determine the packet format so that we can pass it to the data observer.
	AS_Network_Types::AmpInfo ampInfo = this->client_->getAmpInfo(this->ampID_);
	
	// Now that we have some information from the Amp Server (possibly), attempt
	// to setup the data observer.
	this->dataStreamObserver_ = new DataStreamObserver(ampInfo);
	this->client_->addDataStreamObserver(this->dataStreamObserver_, this->ampID_, NULL);
	
	// Todo:
	// Put a method in the data stream observer to indicate that it got what it needed before
	// adding it to the observer list. This example might leave it out; it's just an example.
	
	// Set the connected flag.
	this->connected_ = true;
	
	rVal = 0;
	
      }
      
    }
    
    // Cleanup.
    delete connPrefsRef; // This is only needed for the initial connect.
    
  }

  return rVal;

}

int AmpServerInterface::disconnect() {

  int rVal = 1; // A value of one is used for failure (to match that of the SDK client's connect function.
  
  if ((this->connected_ == true) &&
      (this->client_ != NULL)) {
    
    // Disconnect from the Amp Server.
    if ( this->client_->disconnect() == 0 ) {
      rVal = 0;
    }

  }

  return rVal;
  
}

void AmpServerInterface::acquire(double* data, long numberOfSamples) {

  // Make sure we are connected then collect data.
  if ((this->connected_ == true) &&
      (this->dataStreamObserver_ != NULL)) {

    // This call will block until the data is collected.
    this->dataStreamObserver_->collectData(data, numberOfSamples);

  }

}

int AmpServerInterface::turnOnAmp() {

  return this->sendCommand("cmd_SetPower", -1, 1);

}

int AmpServerInterface::startAmp() {

  // Set to the default acquisiton state by default.
  this->sendCommand("cmd_DefaultAcquisitionState", -1, -1);

  return this->sendCommand("cmd_Start", -1, -1);

}

int AmpServerInterface::stopAmp() {

  return this->sendCommand("cmd_Stop", -1, -1);

}

int AmpServerInterface::turnOffAmp() {

  return this->sendCommand("cmd_SetPower", -1, 0);

}

int AmpServerInterface::sendCommand(const char *command, int16_t channel, int64_t value){

  int rVal = 1; // Failure is 1.

  if ((this->connected_ == true) &&
      (this->client_ != NULL)) {
    
    // Issue command.
    AS_ReturnValue *aS_ReturnValue = this->client_->sendCommand(this->ampID_, command, channel, value);

    // Note: In a future version of this example, we'll check the actual return, for now
    // we'll assume it's good if it's not NULL (in other words, something was sent).

    if (aS_ReturnValue != NULL) {

      // Success.
      rVal = 0;

      // We won't use the return value from this point, so release it.
      RELEASE(aS_ReturnValue);
    }
    
  }

  return rVal;

}

void AmpServerInterface::setAmpID(long ampID) {
  this->ampID_ = ampID;
}

long AmpServerInterface::getAmpID() {
  return this->ampID_;
}

void AmpServerInterface::setApplyScalingFactor(bool applyScalingFactor) {
  
  this->applyScalingFactor_ = applyScalingFactor;

  // Check to see if we have a data stream observer available and update it accordingly.
  if (this->dataStreamObserver_ != NULL) {
    this->dataStreamObserver_->setApplyScalingFactor(applyScalingFactor);
  }
  
}

bool AmpServerInterface::getApplyScalingFactor() {
  return this->applyScalingFactor_;
}
