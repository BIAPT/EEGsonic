
/**@file
 *  AS_TCP_Server header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef AS_TCP_Server_DEFINED
#define AS_TCP_Server_DEFINED

#include "AS_TCP_PortHandler.h"

#include <pthread.h>

/** AS_TCP_Server class.
 *  @author Robert Bell.
 *  @remarks
 *  Currently, this class' primary purpose is to serve as a factory / monitoring of various port handlers.
 *  At present, it just creates.
 *
 *  ------<br>
 *  Update (001): 2007-01-01: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-05-03: Added ECI support.<br>
 *  ------<br>
 */
class AS_TCP_Server : virtual public EGIBase::EGIObject{
	
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
	AS_TCP_Server();
	
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
	virtual ~AS_TCP_Server();
	
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
	 *  &nbsp; AS_TCP_Server *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_Server *retain();
    
    //@}
	
	/**
	 *  Initializes a port handler.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; portType : The port type.<br>
	 *  &nbsp; portNumber : The port number.<br>
	 *  &nbsp; userRef : User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; AS_TCP_PortHandler *: The initalized port handler, or NULL on failure.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_PortHandler *initPortHandler(AS_TCP_PortHandler::PORT_TYPE portType, unsigned int portNumber, void *userRef);
	
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
	virtual EGIBase::ClassID getClassID(){return AS_TCP_Server::classID;}
	
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
	virtual std::string toString() const {return EGIBase::EGIObject::toString() + "::AS_TCP_Server";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ATSE';
	
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
	AS_TCP_Server(const AS_TCP_Server& source);
	
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
	AS_TCP_Server&  operator=(const AS_TCP_Server& source);
	
	//##################
	//End - Assignment.
	//##################
	
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
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_TCP_Server_DEFINED


