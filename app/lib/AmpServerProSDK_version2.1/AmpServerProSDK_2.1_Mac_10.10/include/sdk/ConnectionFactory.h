
/**@file
 *  ConnectionFactory header.
 *  @author Robert Bell
 *  @date 10/08/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef ConnectionFactory_DEFINED
#define ConnectionFactory_DEFINED

// EGI Base.
#include "EGIObject.h"

// Amp Server Pro SDK.
#include "AS_Network_Types.h"

class ConnectionObject;

/**
 *  ConnectionFactory Class.
 *  @author Robert Bell.
 *  @remarks
 *  Place notes here.
 *
 *  ------<br>
 *  Update (001): 2012-08-10: Class creation.<br>
 *  ------<br>
 */
class ConnectionFactory : virtual public EGIBase::EGIObject{
    
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
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    ConnectionFactory();
    
    /**
     *  Copy constructor.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    ConnectionFactory(const ConnectionFactory& source);
    
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
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ~ConnectionFactory();
    
    //####################################
    //End - Destructor.
    //####################################
    
    /**
     *  Assignment.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    ConnectionFactory&  operator=(const ConnectionFactory& source);
    
    /**
     *  Clone.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Implements the virtual constructor idiom.<br>
     *  &nbsp; 2) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; ConnectionFactory *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ConnectionFactory *clone() const;
    
    /**
     *  Create (default constructor).
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Implements the virtual constructor idiom.<br>
     *  &nbsp; 2) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; ConnectionFactory *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ConnectionFactory *create() const;
    
    /**
     *  Init.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; eObject: Initialization object.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; 1) ConnectionFactory *: This object.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
     *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
     */
    virtual ConnectionFactory *init(EGIObject *eObject);
    
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
    virtual EGIBase::ClassID getClassID(){return ConnectionFactory::classID;}
    
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
    virtual std::string toString() const {return EGIObject::toString() + "::ConnectionFactory";}
    
    //####################################
    //Class variables.
    //####################################
    
    /**
     *  Class ID
     *  Specifies the class id for instances of this class.
     */
    static const EGIBase::ClassID classID = 'CORY';
    
    //####################################
    //End - Class variables.
    //####################################
    
    //####################################
    //Class methods.
    //####################################
    
    /**
     *  Gets a generic client connection to the given server address and port.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This is generic in the sense that all the default options for setting up the
     *  client connection are used.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) serverAddress: The server address.<br>
     *  &nbsp; 2) serverAddress: The server port number.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; ConnectionObject *: The resulting connection object.<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    static ConnectionObject *getGenericClientConnectionObject(const char *serverAddress, in_port_t serverPort);
    
    /**
     *  Creates an unconnected port connection but initialized.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This has all fields initialized to default values.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; AS_Network_Types::AS_TCP_Port_ConnectionRef: A reference to an unconnected
     *  port connection.<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    static AS_Network_Types::AS_TCP_Port_ConnectionRef createPortConnection();
    
    //####################################
    //End - Class methods.
    //####################################
    
    
protected:
    
private:
    
};

#endif // ConnectionFactory_DEFINED

