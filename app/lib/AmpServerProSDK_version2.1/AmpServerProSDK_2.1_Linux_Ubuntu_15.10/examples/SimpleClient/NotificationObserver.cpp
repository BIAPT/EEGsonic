/*
 *  NotificationObserver.cpp
 *  @author Robert Bell
 *  @date 2015/09/02
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br> 
 */

#include "NotificationObserver.h"

// EGIBase's utility functions.
#include "UtilityFunctions.h"

// Other includes.
#include <iostream>
#include <string.h>

// Namespaces.
using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

//####################################
// Public Section.
//####################################

NotificationObserver::NotificationObserver() : EGIObject() {}

NotificationObserver::~NotificationObserver() {}

// Note that if you block in update, you will effectively block the data stream
// thread, and thus will cease to receive any more notifications from the notification port.
void NotificationObserver::update(Observable *o, EGIObject *eObject){
  
  eObject->retain();
  
  // Should be of type NotificationObject.
  NotificationObject *notificationObject = dynamic_cast<NotificationObject *>(eObject);
  AS_Network_Client *client = dynamic_cast<AS_Network_Client *>(notificationObject->getSource());
  
  if (notificationObject != 0) {
    
    // Get the notification itself.
    AS_Network_Types::Notification notification = notificationObject->getNotification();
    
    int64_t notificationID = AS_Network_Types::getNotificationID(notification);
    int64_t ampID = AS_Network_Types::getNotificationAmpID(notification);
    int64_t type = AS_Network_Types::getNotificationType(notification);
    
    switch(type){
      
    case AS_Network_Types::ntn_None:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_None" << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpInstalled:
      
      std::cout << "info: client received notification: notificationID: " << notificationID 
		<< " type: ntn_AmpInstalled ampID: " << ampID << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpRemoved:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_AmpRemoved" << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpPowerOn:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_AmpPowerOn" << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpPowerOff:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_AmpPowerOff" << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpStarted:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_AmpStarted" << std::endl;
      break;
      
    case AS_Network_Types::ntn_AmpStopped:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: ntn_AmpStopped" << std::endl;
      break;
      
    default:
      
      std::cout << "info: client received notification: notificationID: " << notificationID << " type: unknown" << std::endl;
      break;
      
    }
    
  } else {
    std::cerr << "error: unable to recognize type" << std::endl;
  }
  
  eObject->release();
  
}

//####################################
// End - Public Section.
//####################################

//####################################
// Protected Section.
//####################################

NotificationObserver::NotificationObserver(const NotificationObserver& source) : EGIObject(source){
  
  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::NotificationObserver(const NotificationObserver& source) : EGIObject(source)");
  
}

NotificationObserver& NotificationObserver::operator=(const NotificationObserver& source){
  EGIObject::operator=(source);
  
  EGI_THROW(EGIBase::MethodNotSupported_EGIException, this->toString() +
	    "::operator=(const NotificationObserver& source)");

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
