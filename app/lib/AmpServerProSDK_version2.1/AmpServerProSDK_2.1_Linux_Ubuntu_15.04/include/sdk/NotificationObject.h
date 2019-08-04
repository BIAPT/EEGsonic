
/**@file
 *  NotificationObject Header File
 *  @author Robert Bell
 *  @date 1/1/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  The NotificationObject wraps a Notification.
 */

#ifndef NotificationObject_DEFINED
#define NotificationObject_DEFINED

#include "AS_Network_Types.h"

/**
 *  NotificationObject Class.
 *  @author Robert Bell.
 *  @remarks
 *  The NotificationObject wraps an AS_Network_Types::Notification.
 *
 *  ------<br>
 *  Update (001): 2007-01-01: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Todo: YEAR-MO-DA:<br>
 *  ------<br>
 *
 */
class NotificationObject : virtual public EGIBase::EGIObject{
	
public:
	//####################################
	//Constructor(s).
	//####################################
	
	/**
	 *  Default contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Thread safety is off.<br>
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
	NotificationObject();
	
	/**
	 *  Contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; threadSafe: true = thread safe; false = not thread safe<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	NotificationObject(bool threadSafe);
	
	/**
	 *  Copy constructor.
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
	NotificationObject(const NotificationObject& source);
	
	//####################################
	//End - Constructor(s).
	//####################################
	
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
	virtual ~NotificationObject();
	
	/**
	 *  Assignment.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; NotificationObject& : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	NotificationObject&  operator=(const NotificationObject& source);

	/**
	 *  Sets this object's notification.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Notification will be copied in.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setNotification(AS_Network_Types::Notification notification);
	
	/**
	 *  Gets this object's notification.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Notification will be callee owned.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Notification: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Notification getNotification();
	
	/**
	 *  Sets the source of the notification.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Source will be retained.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; source: The source.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setSource(EGIBase::EGIObject *source);
	
	/**
	 *  Gets the source of the notification.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; EGIObject *: The source.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual EGIBase::EGIObject *getSource();
	
	/**
	 *  Gets the class ID for this class.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); This method should always be overridden
	 *  in derived classes, and instances should return CLASS_NAME::classID. This allows
	 *  for identification of objects in the runtime environment.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; ClassID: The class ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual EGIBase::ClassID getClassID(){return NotificationObject::classID;}
	
	/**
	 *  The toString method.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; std::string: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual std::string toString(){return EGIObject::toString() + "::AmpDataObject";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'NOCT';
	
	//####################################
	//End - Class variables.
	//####################################
	
	//####################################
	//Class methods.
	//####################################
	//####################################
	//End - Class methods.
	//####################################
	
	
protected:
	
	//####################################
	//Inheritence tree variables.
	//####################################
	//####################################
	//End - Inheritence tree variables.
	//####################################
	
private:
	
	//####################################
	//Non-Inheritence tree variables.
	//####################################
	struct NotificationObjectImpl;
	NotificationObjectImpl* mNotificationObjectImplRef;
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // NotificationObject_DEFINED
