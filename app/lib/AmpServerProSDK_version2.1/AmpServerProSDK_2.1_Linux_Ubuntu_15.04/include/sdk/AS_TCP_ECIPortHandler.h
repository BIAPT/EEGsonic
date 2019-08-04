
/**@file
 *  AS_TCP_NotificationHandler header.
 *  @author Robert Bell
 *  @date 03/05/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef AS_TCP_ECIPortHandler_DEFINED
#define AS_TCP_ECIPortHandler_DEFINED

#include "AS_TCP_PortHandler.h"

#include <pthread.h>

/** AS_TCP_ECIPortHandler class.
 *  @author Robert Bell.
 *  @remarks
 *  This class implements AS_TCP_Porthandler to hand off data interactions to its
 *  ECI handler delegate.
 *
 *  ------<br>
 *  Update (001): 2012-05-03: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-08-02: Updated to support new and old queries.<br>
 *  ------<br>
 */
class AS_TCP_ECIPortHandler : virtual public AS_TCP_PortHandler{
	
public:
	
	//####################################
	//Constructor(s).
	//####################################
	
	/**
	 *  Constructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); Thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; portType : The port type.<br>
	 *  &nbsp; portNumber : The port number.<br>
	 *  &nbsp; serverRef : Reference to the server.<br>
	 *  &nbsp; userRef : User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_TCP_ECIPortHandler(AS_TCP_ECIPortHandler::PORT_TYPE portType, unsigned int portNumber, AS_TCP_Server *serverRef, void *userRef);
	
	//####################################
	//End - Constructor(s).
	//####################################
	
	//####################################
	//Destructor.
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
	virtual ~AS_TCP_ECIPortHandler();
	
	//####################################
	//End - Destructor.
	//####################################
	
	/**                                                                                                                                                                       
	 *  @name Memory Management.                                                                                                                                   
	 *  Memory Management.                                                                                     
	 */
	//@{
	
	/**
	 *  Retains this object.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); Throws EGIBase::Retain_EGIException on failure if exceptions are turned on,
	 *  otherwise returns NULL.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; AS_TCP_ECIPortHandler *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_ECIPortHandler *retain();
	
	//@}
	
	/**
	 *  This object's implementation of update.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; observable: The observable object calling this method.<br>
	 *  &nbsp; eObject: The optional user reference passed to the observable object.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void update(EGIBase::ObserverPattern::Observable *, EGIBase::EGIObject *eObject);
	
	/**
	 *  Gets the class ID for this class.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This method should always be overridden
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
	virtual EGIBase::ClassID getClassID(){return AS_TCP_ECIPortHandler::classID;}
	
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
	virtual std::string toString() const {return AS_TCP_PortHandler::toString() + "::AS_TCP_ECIPortHandler";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ATEH';
	
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
	
	//##################
	//Copy constructor.
	//##################
	
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
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_TCP_ECIPortHandler(const AS_TCP_ECIPortHandler& source);
	
	//##################
	//End - Copy constructor.
	//##################
	
	//##################
	//Assignment.
	//##################
	
	/**
	 *  Assignment.
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
	AS_TCP_ECIPortHandler&  operator=(const AS_TCP_ECIPortHandler& source);
	
	//##################
	//End - Assignment.
	//##################
	
	/**
	 *  Handles port connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void handlePortConnection(void *userRef);
	
	//####################################
	//Inheritence tree variables.
	//####################################
    
    AS_Network_Types::ArchType architectureType_;
    bool swapBytes_;
    
	//####################################
	//End - Inheritence tree variables.
	//####################################
	
private:
	
	//####################################
	//Non-Inheritence tree variables.
	//####################################
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_TCP_ECIPortHandler_DEFINED


