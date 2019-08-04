
/**@file
 *  Buffer.h.
 *  @author Robert Bell
 *  @date 01/01/2008.
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 */

#ifndef EGIBuffer_DEFINED
#define EGIBuffer_DEFINED

#include "EGIObject.h"

#include <iostream>

/**
 *  EGIBase namespace.
 */
namespace EGIBase{

	/**
	 *  EGIBuffer Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  Base class for EGI buffers.
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
	 *  Update (003): 2010-05-07: Fixed copy and assignment.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (004): 2012-04-20: toString method now const.<br>
	 *  ------<br>
	 */
	class EGIBuffer : virtual public EGIObject{

	public:
		
		typedef unsigned short Type;
		typedef short Code;
		
		class Opts : virtual public EGIObject{
		public:
			
			Opts() : EGIObject(){
				this->uByCopy = false;
				this->uSpecific = false;
				this->numberOfBytes = 0;
				this->uFrom = 0;
				this->uTo = 0;
				this->uNextReadLocation = 0;
			}
			
			bool uByCopy;
			bool uSpecific;
			uint64_t numberOfBytes;
			uint64_t uFrom;
			uint64_t uTo;
			uint64_t uNextReadLocation;
		};
		
		class MethodNotSupported : std::exception{
			virtual const char *what() const throw(){
				return "error: method not supported";
			}
		};
		
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
		EGIBuffer();
		
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
		EGIBuffer(bool threadsafe);
		
		//####################################
		// End - Constructor(s).
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
		virtual ~EGIBuffer();
		
		/**
		 *  Is buffer active.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; userRef: Not supported.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true: active, false: not active<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual bool isBufferActive() = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual EGIBuffer::Code createBuffer(uint64_t size) = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual EGIBuffer::Code destroyBuffer() = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual EGIBuffer::Code writeToBuffer(char *data, uint64_t size, EGIBuffer::Opts *opts) = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual EGIBuffer::Code readFromBuffer(char * &output, uint64_t &size, EGIBuffer::Opts *opts) = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual EGIBuffer::Code resetBuffer() = 0;
		
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
		virtual void *getBuffer() = 0;
			
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
		 *  &nbsp; N/A<br>
		 */
		virtual uint64_t getSizeOfBuffer() = 0;	
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual uint64_t getAvailableReadSize(EGIBuffer::Opts *opts) = 0;
		
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
		 *  &nbsp; N/A<br>
		 */
		virtual uint64_t getAvailableWriteSize() = 0;
		
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
		virtual ClassID getClassID(){return EGIBuffer::classID;}
		
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
		virtual std::string toString() const {return EGIObject::toString() + "::EGIBuffer";}
		
		//####################################
		//Class variables.
		//####################################
		
		static EGIBuffer::Type const RAW_BUFFER = 0;
		static EGIBuffer::Type const TRADITIONAL_EGI_BUFFER = 1;
		
		static EGIBuffer::Code const SUCCESS = 1;
		static EGIBuffer::Code const NEUTRAL = 0; // Neutral status.
		static EGIBuffer::Code const FAIL = -1; // General Fail.
		static EGIBuffer::Code const ERROR_UNABLE_TO_ALLOCATE_MEMORY = -2;	// Caused when no more memory is available.
		static EGIBuffer::Code const ERROR_NULL_BUFFER = -3; // Caused by trying to reference a null buffer.
		
		// BufferContainer additions.
		static EGIBuffer::Code const ERROR_BAD_BUFFER_LOCATION = -4; // Caused when trying to access a location in a (the) buffer that is too high.
		static EGIBuffer::Code const ERROR_BAD_BUFFER_ID_LOCATION = -5; // Caused by trying to create or use a buffer id that does not exist.
		static EGIBuffer::Code const ERROR_UNSUPPORTED_BUFFER_TYPE = -6; // Buffer type not supported.
		
		/**
		 *  Class ID<br>
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'BUER';
		
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
		EGIBuffer(const EGIBuffer& source);
		
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
		 *  &nbsp; EGIObject& : N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		EGIBuffer& operator=(const EGIBuffer& source);
		
		//####################################
		// End - Assignment.
		//####################################
			
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
}

#endif // Buffer_DEFINED
