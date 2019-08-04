
/**@file
 *  ConnectionObject header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef ConnectionObject_DEFINED
#define ConnectionObject_DEFINED

#include "Observer.h"

#include <AS_Network_Types.h>

#include <pthread.h>
#include <stdint.h>

/** ConnectionObject class.
 *  @author Robert Bell.
 *  @remarks
 *  This is a full thread safe representation of a connection. Its main purpose
 *  is to augment the more simplistic AS_Network_Types::AS_TCP_Port_ConnectionRef.
 *
 *  ------<br>
 *  Update (001): 0000-00-00: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2009-10-22: Cleaned up mutex resources in the destructor.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2011-03-24: Fixed an error in fgets where only < zero and not <=
 *  was being checked on the return when not using standard io.<br>
 *  ------<br>
 */
class ConnectionObject : public EGIBase::ObserverPattern::Observer{
	
public:
	
	//####################################
	//Constructor(s).
	//####################################
	
	/**
	 *  Default contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Do not use this constructor.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 */
	ConnectionObject();
	
	/**
	 *	Constructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; connection: The connection. Ownership retained.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 */
	ConnectionObject(AS_Network_Types::AS_TCP_Port_ConnectionRef connection);
	
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
 	 *  &nbsp; void: N/A<br>
	 */
	virtual ~ConnectionObject();
	
	//####################################
	//End - Destructor.
	//####################################
	
	/**
	 *  Gets the presentation address.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; uint32_t: The connection ID.<br>
	 */
	virtual const char * getPresentationAddress();
	
	/**
	 *  Gets the connection ID.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; uint32_t: The connection ID.<br>
	 */
	virtual int32_t getConnectionID();
	
	/**
	 *  Sets the read state.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; readState: The desired read state.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 */
	virtual void setReadState(bool readState);
	
	/**
	 *  Gets the read state.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; bool: The read state.<br>
	 */
	virtual bool getReadState();
	
	/**
	 *  Sets the write state.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; writeState: The desired write state.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 */
	virtual void setWriteState(bool writeState);
	
	/**
	 *  Gets the write state.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; bool: The write state.<br>
	 */
	virtual bool getWriteState();
	
	/**
	 *  Read from the connection stream.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This mirrors the standard fread method.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; ptr: Pointer to preallocated data array.<br>
	 *  &nbsp; size: Size of object.<br>
	 *  &nbsp; nobj: Number of objects.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int32_t: N/A<br>
	 */
	virtual int32_t fread(void *ptr, size_t size, size_t nobj);
	
	/**
	 *  Read a line from the connection stream.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This mirrors the standard fgets method.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; s: Pointer to preallocated data array.<br>
	 *  &nbsp; n: Number of character minus one (this will be the max read ... see fgets).<br>
	 *  &nbsp; nobj: Number of objects.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int32_t: N/A<br>
	 */
	virtual char *fgets(char *__restrict__ s, int n);
	
	/**
	 *  Write to the connection stream.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This mirrors the standard fwrite method.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; ptr: Pointer to data to be copied to stream.<br>
	 *  &nbsp; size: Size of object.<br>
	 *  &nbsp; nobj: Number of objects.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int32_t: N/A<br>
	 */
	virtual int32_t fwrite(const void *ptr, size_t size, size_t nobj);
	
	/**
	 *  This object's implementation of update.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) The primary use of this update implementation is to relay connection related
	 *  events to the ConnectionObject.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; observable: N/A<br>
	 *  &nbsp; eObject: N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 */
	virtual void update(EGIBase::ObserverPattern::Observable *observable, EGIBase::EGIObject *eObject);
	
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
	virtual EGIBase::ClassID getClassID(){return ConnectionObject::classID;}
	
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
	virtual std::string toString() const {return Observer::toString() + "::ConnectionObject";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
     */
	static const EGIBase::ClassID classID = 'COOB';
	
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
	 *  &nbsp 1); EGIBase::MethodNotSupported_EGIException.<br>
	 */
	ConnectionObject(const ConnectionObject& source);
	
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
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp 1); EGIBase::MethodNotSupported_EGIException.<br>
	 */
	ConnectionObject&  operator=(const ConnectionObject& source);
	
	//##################
	//End - Assignment.
	//##################
	
	/**
	 *  Internal socket read.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; sockfd: Socket.<br>
	 *  &nbsp; buff: Buffer.<br>
	 *  &nbsp; nbytes: Number of bytes.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; ssize_t: Number of bytes read.<br>
	 */
	virtual ssize_t _read(int sockfd, void *buff, size_t nbytes);
	
	/**
	 *  Internal socket readline.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; sockfd: Socket.<br>
	 *  &nbsp; buff: Buffer.<br>
	 *  &nbsp; maxlen: Number of bytes.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; ssize_t: Number of bytes read.<br>
	 */
	virtual ssize_t _readline(int sockfd, void *buff, size_t maxlen);
	
	/**
	 *  Internal socket readline helper.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; sockfd: Socket.<br>
	 *  &nbsp; ptr: Current character position.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; ssize_t: Number of bytes read.<br>
	 */
	virtual ssize_t _readlineHelper(int sockfd, char *ptr);
	
	/**
	 *  Internal socket write.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
 	 *  &nbsp; sockfd: Socket.<br>
	 *  &nbsp; buff: Buffer.<br>
	 *  &nbsp; nbytes: Number of bytes.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; ssize_t: Number of bytes written.<br>
	 */
	virtual ssize_t _write(int sockfd, const void *buff, size_t nbytes);
	
	//####################################
	//Inheritence tree variables.
	//####################################
	
	AS_Network_Types::AS_TCP_Port_ConnectionRef mConnection;
	
	char * mPresentationAddress;
	
	int mReadCount;
	char *mReadLocation;
	char *mReadBuffer;
		
	pthread_mutex_t *mReadMutex;
	pthread_mutex_t *mWriteMutex;
	
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

#endif // ConnectionObject_DEFINED
