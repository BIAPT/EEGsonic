
/**@file
 *  ByteBuffer header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef ByteBuffer_DEFINED
#define ByteBuffer_DEFINED

#include "EGIObject.h"
#include "EGIException.h"

#include <iostream>

/**
 *  com namespace.
 */
namespace com{
	/**
	 *  egi namespace.
	 */
	namespace egi{
		/**
		 *  services namespace.
		 */
		namespace services{
			/**
			 *  mff namespace.
			 */
			namespace mff{
				/**
				 *  util namespace.
				 */
				namespace util{
					
					/**
					 *  ByteBuffer Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update (001): 2011-02-10: Class creation.<br>
					 *  ------<br>
                     *
                     *  ------<br>
					 *  Update (002): 2012-07-30: Added one of the get methods and a generic get.<br>
					 *  ------<br>
                     *
                     *  ------<br>
                     *  Update (003): 2015-10-14: Updated to throw the correct exceptions.<br>
                     *  ------<br>
                     *
                     *  ------<br>
                     *  Update (004): 2015-10-14: Comments improved.<br>
                     *  ------<br>
					 */
					class ByteBuffer : virtual public EGIBase::EGIObject{
						
					public:
                        
                        class InsufficentDataAvailable_EGIException : public EGIBase::EGIException {
                            
                        public:
                            
                            InsufficentDataAvailable_EGIException(std::string message) : EGIException(message){}
                            InsufficentDataAvailable_EGIException(std::string message, bool exitApplication,
                                                                  bool threadsafe) : EGIException(message, exitApplication,
                                                                                                  threadsafe){}
                            
                        };
						
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
						ByteBuffer();
                        
                        /**
						 *  Contructor.
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
						ByteBuffer(uint64_t withCapacity, bool expandable = true, int64_t withExpandIncrement = -1);
						
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
						virtual ~ByteBuffer();
						
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
						 *  &nbsp; ByteBuffer *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual ByteBuffer *clone() const;
						
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
						 *  &nbsp; ByteBuffer *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual ByteBuffer *create() const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual ByteBuffer *init(EGIObject *eObject);
                        
                        /**
						 *  Allocates a new byte buffer of given capacity.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) capacity: The byte buffer's capacity.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: The allocated byte buffer (retained).<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						static ByteBuffer *allocate(uint64_t withCapacity, bool expandable = true, int64_t withExpandIncrement = -1);
                        
                        /**
						 *  Returns the byte array for this buffer.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) char *: The byte array.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual char *array();
                        
                        /**
						 *  Gets the buffer position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: The buffer position.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual uint64_t position();
                        
                        /**
						 *  Sets the buffer position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) If the new poition is outside the buffer's bounds, and the buffer
                         *  is not set to be expandable, then an invalid argument exception is thrown.<br>
                         *  &nbsp; 2) If the new poition is outside the buffer's bounds, and the buffer
                         *  IS set to be expandable, then the buffer size is expanded accordingly, and the new
                         *  position is set.<br>
                         *  &nbsp; 3) Zero is the beginning position of the buffer.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) position: The new buffer position.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::InvalidArgument_EGIException: If the conditions for the
                         *  new position are not met, this exception is thrown.<br>
                         *  &nbsp; 2) EGIBase::Error_EGIException: If the an unknown error state is encounted. This is bad,
                         *  and probably means you should bail and look at the code.<br>
						 */
						virtual ByteBuffer *position(uint64_t newPosition);
                        
                        /**
						 *  Gets the buffer capacity.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: The buffer capacity.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual uint64_t capacity();
                        
                        /**
						 *  Puts data from "data" into the buffer at its current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer.<br>
                         *  &nbsp; 2) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
                         *  &nbsp; 1) EGIBase::InvalidArgument_EGIException: If the conditions for the
                         *  new position are not met, this exception is thrown.<br>
                         *  &nbsp; 2) EGIBase::Error_EGIException: If the an unknown error state is encounted. This is bad,
                         *  and probably means you should bail and look at the code.<br>
						 */
						virtual ByteBuffer *put(const char *data, uint64_t size);
                        
                        /**
						 *  Puts data from "data" into the buffer at the location specified by
                         *  "index".
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Not implemented yet- will immediately throw the exception.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer.<br>
                         *  &nbsp; 2) index: The index of where to place the data in the buffer.<br>
                         *  &nbsp; 3) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						virtual ByteBuffer *put(const char *data, uint64_t index, uint64_t size);
                        
                        /**
						 *  Puts data from "data" beginning at "offset" into the buffer at its
                         *  current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer (using the offset below).<br>
                         *  &nbsp; 2) offset: The offset in data where the data begins.<br>
                         *  &nbsp; 3) size: The size of the data from the offset.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
                         *  &nbsp; 1) EGIBase::InvalidArgument_EGIException: If the conditions for the
                         *  new position are not met, this exception is thrown.<br>
                         *  &nbsp; 2) EGIBase::Error_EGIException: If the an unknown error state is encounted. This is bad,
                         *  and probably means you should bail and look at the code.<br>
						 */
						virtual ByteBuffer *putWithOffset(const char *data, uint64_t offset, uint64_t size);
                        
                        /**
						 *  Puts data from "data" beginning at "offset" into the buffer at the location specified by
                         *  "index".
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Not implemented yet- will immediately throw the exception.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer (using the offset below).<br>
                         *  &nbsp; 2) offset: The offset in data where the data begins.<br>
                         *  &nbsp; 3) index: The index of where to place the data in the buffer.<br>
                         *  &nbsp; 4) size: The size of the data from the offset.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						virtual ByteBuffer *putWithOffsetAndIndex(const char *data, uint64_t offset, uint64_t index, uint64_t size);
                        
                        /**
						 *  Puts the value into the buffer at its current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) value: The value to put into the buffer.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
                         *  &nbsp; 1) EGIBase::InvalidArgument_EGIException: If the conditions for the
                         *  new position are not met, this exception is thrown.<br>
                         *  &nbsp; 2) EGIBase::Error_EGIException: If the an unknown error state is encounted. This is bad,
                         *  and probably means you should bail and look at the code.<br>
						 */
                        template <class T> ByteBuffer *put_T(T value);
                        
                        /**
                         *  Puts the value into the buffer at the location specified by
                         *  "index".
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) Not implemented yet- will immediately throw the exception.<br>
                         *  ------<br>
                         *  <b>Arguments:</b><br>
                         *  &nbsp; 1) value: The value to put into the buffer.<br>
                         *  &nbsp; 2) index: The index of where to place the data in the buffer.<br>
                         *  ------<br>
                         *  <b>Return:</b><br>
                         *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
                         *  ------<br>
                         *  <b>Throws:</b><br>
                         *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
                         */
                        template <class T> ByteBuffer *put_T(T value, uint64_t index);
                        
                        /**
						 *  Gets data from the buffer at its current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: A preallocted region into which to place the data.<br>
                         *  &nbsp; 2) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) InsufficentDataAvailable_EGIException.<br>
						 */
						virtual ByteBuffer *get(char *data, uint64_t size);
                        
                        /**
						 *  Gets data from the buffer at the given index.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: A preallocted region into which to place the data.<br>
                         *  &nbsp; 2) index: The index from which to get the data.<br>
                         *  &nbsp; 3) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) InsufficentDataAvailable_EGIException.<br>
						 */
						virtual ByteBuffer *get(char *data, uint64_t index, uint64_t size);
                        
                        template <class T>  T get_T();
                        
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
						virtual EGIBase::ClassID getClassID(){return ByteBuffer::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::ByteBuffer";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'BYER';
						
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
                        
                        char *data_;
                        uint64_t capacity_;
                        uint64_t position_;
                        bool expandable_;
                        int64_t expandIncrement_;
						
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
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						ByteBuffer(const ByteBuffer& source);
						
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
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						ByteBuffer&  operator=(const ByteBuffer& source);
						
						//##################
						//End - Assignment.
						//##################
                        
                        /**
						 *  Puts data from "data" into the buffer at its current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer.<br>
                         *  &nbsp; 2) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
                         *  &nbsp; 1) EGIBase::InvalidArgument_EGIException: If the conditions for the
                         *  new position are not met, this exception is thrown.<br>
                         *  &nbsp; 2) EGIBase::Error_EGIException: If the an unknown error state is encounted. This is bad,
                         *  and probably means you should bail and look at the code.<br>
						 */
						virtual ByteBuffer *put_(const char *data, uint64_t size);
                        
                        /**
						 *  Puts data from "data" into the buffer at the location specified by
                         *  "index".
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Not implemented yet- will immediately throw the exception.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: The data to put into the buffer.<br>
                         *  &nbsp; 2) index: The index of where to place the data in the buffer.<br>
                         *  &nbsp; 3) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						virtual ByteBuffer *put_(const char *data, uint64_t index, uint64_t size);
                        
                        /**
						 *  Gets data from the buffer at its current position.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: A preallocted region into which to place the data.<br>
                         *  &nbsp; 2) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) InsufficentDataAvailable_EGIException.<br>
						 */
						virtual ByteBuffer *get_(char *data, uint64_t size);
                        
                        /**
						 *  Gets data from the buffer at the given index.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) data: A preallocted region into which to place the data.<br>
                         *  &nbsp; 2) index: The index from which to get the data.<br>
                         *  &nbsp; 3) size: The size of the data.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) ByteBuffer *: This byte buffer.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) InsufficentDataAvailable_EGIException.<br>
						 */
						virtual ByteBuffer *get_(char *data, uint64_t index, uint64_t size);
						
					private:
						
					};
                    
                    template <class T> ByteBuffer *ByteBuffer::put_T(T value){
                        
                        ByteBuffer *rVal = this;
                        
                        // Debug.
                        //std::cout << this->toString() << ": value: " << value << std::endl;
                        
                        this->put_(reinterpret_cast<char *>(&value), sizeof(T));
                        
                        return rVal;
                        
                    }
                    
                    template <class T> ByteBuffer *ByteBuffer::put_T(T value, uint64_t index){
                        
                        ByteBuffer *rVal = this;
                        
                        this->put_(reinterpret_cast<char *>(&value), index, sizeof(T));
                        
                        return rVal;
                        
                    }
                    
                    template <class T>  T ByteBuffer::get_T(){
                        
                        T rVal = 0;
                        
                        this->get_(reinterpret_cast<char *>(&rVal), sizeof(T));
                        
                        // Debug.
                        //std::cout << this->toString() << ": rVal: " << rVal << std::endl;
                        
                        return rVal;
                      
                        
                    }
                    
				}
                
			}
            
		}
        
	}
    
}

#endif // ByteBuffer_DEFINED

