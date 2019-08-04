
/**@file
 *  EGICircularBuffer.h.
 *  @author Robert Bell
 *  @date 01/01/2008
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 */

#ifndef EGICircularBuffer_DEFINED
#define EGICircularBuffer_DEFINED

#include "EGIBuffer.h"

#include <iostream>
#include <string.h>

/**
 *  EGIBase namespace.
 */
namespace EGIBase{

	/**
	 *  EGICircularBuffer Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  EGI circular buffer.
	 *
	 *  ------<br>
	 *  Update (001): 2008-09-23: Updated comments for Doxygen.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (002): 2010-05-07: Updated comments.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (003): 2010-05-07: Fixed copy, assignment, clone and create.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (004): 2010-05-15: Updated comments.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (005): 2012-04-20: toString method now const.<br>
	 *  ------<br>
	 */
	class EGICircularBuffer : virtual public EGIBuffer{
		
	public:
		
		//####################################
		// Constructor(s).
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
		EGICircularBuffer();
		
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
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		EGICircularBuffer(bool threadsafe);
		
		//####################################
		// End - Constructor(s).
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
		virtual ~EGICircularBuffer();
		
		//####################################
		//End - Destructor.
		//####################################
		
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
		 *  &nbsp; EGICircularBuffer *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGICircularBuffer *clone() const;
		
		/**
		 *  Create.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Implements the virtual constructor idiom.<br>
		 *  &nbsp; 2) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGICircularBuffer *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGICircularBuffer *create() const;
		
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
		 *  &nbsp; EGICircularBuffer *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGICircularBuffer *create(bool threadSafe) const;
		
		/**
		 *  Init.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) eObject: Initialization object.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGICircularBuffer *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGICircularBuffer *init(EGIObject *eObject);
		
		/**
		 *  Is buffer active.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; userRef: Not supported.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true: not active, false: not active.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual bool isBufferActive();
		
		/**
		 *  Creates buffer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; size: Size of buffer.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIBuffer::Code: See EGIBuffer.h.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual EGIBuffer::Code createBuffer(uint64_t size);
		
		/**
		 *  Deletes buffer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIBuffer::Code: See EGIBuffer.h.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual EGIBuffer::Code destroyBuffer();
		
		/**
		 *  Writes to the buffer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; data: Data to write.<br>
		 *  &nbsp; size: Size of data.<br>
		 *  &nbsp; opts: Options.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIBuffer::Code: See EGIBuffer.h.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual EGIBuffer::Code writeToBuffer(char *data, uint64_t size, EGIBuffer::Opts *opts);
		
		/**
		 *  Reads from the buffer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; output: Output data.<br>
		 *  &nbsp; size: Size of output data.<br>
		 *  &nbsp; opts: Options.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIBuffer::Code: See EGIBuffer.h.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual EGIBuffer::Code readFromBuffer(char * &output, uint64_t &size, EGIBuffer::Opts *opts);
		
		/**
		 *  Resets the buffer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; This does not delete the buffer.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIBuffer::Code: See EGIBuffer.h.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual EGIBuffer::Code resetBuffer();
		
		/**
		 *  Gets the buffer's internal store.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void *: The internal store.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual void *getBuffer();
		
		/**
		 *  Gets the buffer's size.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; uint64_t: Buffer size.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual uint64_t getSizeOfBuffer();	
		
		/**
		 *  Gets the available read size.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; uint64_t: Available read size.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 */
		virtual uint64_t getAvailableReadSize(EGIBuffer::Opts *opts);
		
		/**
		 *  Gets the available write size.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; uint64_t: Available write size.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		virtual uint64_t getAvailableWriteSize();
		
		/**
		 *  Gets the class ID for this class.
		 *  <b>Notes:</b><br>
		 *  &nbsp; This method should always be overridden
		 *  in derived classes, and instances should return CLASS_NAME::classID. This allows
		 *  for identification of objects in the runtime environment.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; ClassID: The class ID.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual ClassID getClassID(){return EGICircularBuffer::classID;}
		
		/**
		 *  The toString method.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; std::string: String representation of this instance.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual std::string toString() const {return EGIBuffer::toString() + "::EGICircularBuffer";}
		
		//####################################
		//Class variables.
		//####################################
		
		/**
		 *  Class ID<br>
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'CIER';
		
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
		// Constructor(s).
		//####################################
		
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
		EGICircularBuffer(const EGICircularBuffer& source);
		
		//####################################
		// End - Constructor(s).
		//####################################
		
		
		//####################################
		// Assignment.
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
		 *  &nbsp; EGICircularBuffer& : N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		EGICircularBuffer& operator=(const EGICircularBuffer& source);
		
		//####################################
		// End - Assignment.
		//####################################
		
		
		//####################################
		// Inheritence tree variables.
		//####################################
		
		/**
		 *  Gets the available read size.
		 *  <b>Notes:</b><br>
		 *  &nbsp; Non-locking version.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; uint64_t: Available read size.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual uint64_t _getAvailableReadSize(EGIBuffer::Opts *opts);
		
		char *mBuffer;
		uint64_t mBufferSize;
		uint64_t mBufferLocation;
		
		//####################################
		// End - Inheritence tree variables.
		//####################################
		
	private:
		
		//####################################
		// Non-Inheritence tree variables.
		//####################################
		//************************************
		// End - Non-Inheritence tree variables.
		//####################################
		
	};
}

#endif // Buffer_DEFINED
