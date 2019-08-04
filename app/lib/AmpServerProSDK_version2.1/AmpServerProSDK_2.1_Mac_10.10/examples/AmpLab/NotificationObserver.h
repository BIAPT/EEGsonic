
/**@file
 *  NotificationObserver Header File
 *  @author Robert Bell
 *  @date 2015/09/07
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// Other includes.
#include <iostream>

/**
 *  NotificationObserver Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class demonstrates how to receive notifications that are distributed
 *  by the SDK when using the high-level C++ API.<br>
 *
 *  <b> Important Notes:</b><br>
 *  
 *  1) The class implements the update method, the method called to pass (in this case) instances of the class a NotificationObject.
 *  NotificationObserver:update(...) is called from a separate thread, and as such, you should take appropriate precautions. Similar
 *  to the update method of DataStreamObserver, in addition to normal thread precautions (locks etc.), you should avoid blocking in the
 *  update thread. This is because the update thread is the same thread that services the notificatoin port and
 *  thus if you block, you will block this action.<br>
 *
 *  ------<br>
 *  Update (001): 2015-09-07: Class creation.<br>
 *  ------<br>
 */
class NotificationObserver : public EGIBase::ObserverPattern::Observer{
  
 public:
  
  /**
   *  Contructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  NotificationObserver();

  /**
   *  Destructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws</b><br>
   *  &nbsp; N/A<br>
   */
  virtual ~NotificationObserver();
  
  /**
   *  This class's implementation of update.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This method is called when the object being observed calls its notify method.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; observable: The observable object calling this method.<br>
   *  &nbsp; eObject: The optional user reference passed to the observable object.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; void: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  virtual void update(EGIBase::ObserverPattern::Observable *o, EGIObject *eObject);
  
 protected:

  /**
   *  Copy Constructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  NotificationObserver(const NotificationObserver& source);
  
  /**
   *  Assignment.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; NotificationObserver& : N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  NotificationObserver& operator=(const NotificationObserver& source);

 private:

};
