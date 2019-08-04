
/**@file
 *  AS_TCP_PortHandler header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef AS_TCP_PortHandler_DEFINED
#define AS_TCP_PortHandler_DEFINED

#include <pthread.h>
#include "EGIBase.h"
#include "AS_Network_Types.h"

// Network includes.
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// STL
#include <vector>

// Forward declarations.
class AS_TCP_Server;
class AS_TCP_PortHandlerDelegate;
class ConnectionObject;

/**
 *  AS_TCP_PortHandler Class.
 *  @author Robert Bell.
 *  @remarks
 *  Place notes here.
 *
 *  ------<br>
 *  Update (001): 2009-10-08: As a result of a Mac OS X (10.5.x) bug, the SO_NOSIGPIPE
 *  option has to be set after select returns. Here is the relevent email:<br>
 *  <br>
 *  Robert,<br>
 *  This is indeed a bug of Mac OS X 10.5.x where a number of socket options are not inherited from the listening socket.
 *  The workaround is to call setsockopt(SO_NOSIGPIPE) just after accept() return the socket for the new connection. Because
 *  of the other problem mentioned by Glenn Anderson your code should be ready for setsockopt() to fail with EINVAL
 *  if the peer has already closed the connection.<br>
 *  <br>
 *  Vincent
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2010-04-09: Fixed typo in the __MACH__ conditional compiles.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2010-04-09: Thread safety was off, it is now on.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (004): 2010-04-09: Default constructor not supported.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (005): 2012-05-03: Added ECI port type.<br>
 *  ------<br>
 *
 */
class AS_TCP_PortHandler : virtual public EGIBase::ObserverPattern::Observer{
	
public:
	
	enum PORT_TYPE{
        
		UNKNOWN,
		COMMAND,
		NOTIFICATION,
		STREAM,
		REQUEST,
        ECI
        
	};
	
	/**
	 *  A typed enum representing connection errors encountered by the port handler.
	 */
	typedef enum{
        
		READ_FAILURE = 0,		/**< Read connection failure */
		WRITE_FAILURE = 1,		/**< Write connection failure */
		UNKNOWN_FAILURE  = 2	/**< Unknown failure */
        
	} ConnectionError;
	
	//####################################
	//  Constructor(s).
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
	AS_TCP_PortHandler(AS_TCP_PortHandler::PORT_TYPE portType, unsigned int portNumber, AS_TCP_Server *serverRef, void *userRef);
	//####################################
	// End - Constructor(s).
	//####################################
	
	//####################################
	// Destructor.
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
	virtual ~AS_TCP_PortHandler();
	
	//####################################
	// End - Destructor.
	//####################################
	
	/**                                                                                                                                                                       
	 *  @name Memory Management.                                                                                                                                   
	 *  Memory Management.                                                                                     
	 */
	//@{
	
	/**
	 *  Retains this object.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Throws EGIBase::Retain_EGIException on failure if exceptions are turned on,
	 *  otherwise returns NULL.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; AS_TCP_PortHandler *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_PortHandler *retain();
	
	//@}
	
	/**
	 *  Initializes the port handler.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; userRef: Not supported.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void initPortHandler(void *userRef);
	
	/**
	 *  Wait for connections.
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
	virtual void waitForConnections();
	
	/**
	 *  Handle port connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; userRef: For pthread use.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void *_handlePortConnection(void *userRef);
	
	/**
	 *  Gets the port type for this instance.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_TCP_PortHandler::PORT_TYPE: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_PortHandler::PORT_TYPE getPortType();
	
	/**
	 *  Gets the port number.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; unsigned int: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual unsigned int getPortNumber();
	
	/**
	 *  Gets the thread on which this port resides.
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
	virtual pthread_t *getThread();
	
	/**
	 *  Sets the command delegate.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; delegate: The delegate.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setDelegate(AS_TCP_PortHandlerDelegate *delegate);
	
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
	virtual EGIBase::ClassID getClassID(){return AS_TCP_PortHandler::classID;}
	
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
	virtual std::string toString() const {return Observer::toString() + "::AS_TCP_PortHandler";}
	
	//####################################
	// Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ATPH';
	
	//####################################
	// End - Class variables.
	//####################################
	
	//####################################
	// Class methods.
	//####################################
	
	/**
	 *  Creates a AS_Network_Types::AS_TCP_Port_Connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; delegate: The delegate.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::AS_TCP_Port_ConnectionRef: Caller owned.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::AS_TCP_Port_ConnectionRef createConnection();
	
	//####################################
	// End - Class methods.
	//####################################
	
	
protected:
	
	/**
	 *  Initializes the port handler.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; userRef: Not supported.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void _initPortHandler(void *userRef);
	
	/**
	 *  Wait for connections.
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
	virtual void _waitForConnections();
	
	/**
	 *  Handle port connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; userRef: Not supported.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void handlePortConnection(void *userRef) = 0;
	
	/**
	 *  Adds a connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Adds a connection to the set of connections for this object. The connection is
	 *  not added if it is already present in the set, or the passed in pointer
	 *  is null.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; AS_Network_Types::AS_TCP_Port_ConnectionRef: The connection.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual bool addConnection(ConnectionObject *connection);
	
	/**
	 *  Deletes a connection.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; AS_Network_Types::AS_TCP_Port_ConnectionRef: The connection.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual bool deleteConnection(ConnectionObject *connection);
	
	//####################################
	// Inheritence tree variables.
	//####################################
	
	//##################
	// Copy constructor.
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
	AS_TCP_PortHandler(const AS_TCP_PortHandler& source);
	
	//##################
	// End - Copy constructor.
	//##################
	
	//##################
	// Assignment.
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
	AS_TCP_PortHandler&  operator=(const AS_TCP_PortHandler& source);
	
	//##################
	// End - Assignment.
	//##################
	
	
	AS_TCP_PortHandler::PORT_TYPE mPortType;
	unsigned int *mPortNumber;
	int mSocket;
	pthread_t *mTID;
	bool mPortActive;
	
	// Connection ids.
	uint32_t mNextConnectionID;
	
	// Connection list.
	std::vector<ConnectionObject *> *mConnections;
	
	AS_TCP_Server *mServerRef;
	AS_TCP_PortHandlerDelegate *mPortHandlerDelegate;
	//####################################
	// End - Inheritence tree variables.
	//####################################
	
private:
	
	//####################################
	// Non-Inheritence tree variables.
	//####################################
	//####################################
	// End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_TCP_PortHandler_DEFINED
