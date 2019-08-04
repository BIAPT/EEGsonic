
/**@file
 *  XMLResource header.
 *  @author Robert Bell
 *  @date 02/03/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef XMLResource_DEFINED
#define XMLResource_DEFINED

#include "EGIObject.h"
#include "EGIException.h"

#include "MarshallingProtocol.h"

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
					 *  XMLResource Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-03-02: Class creation.<br>
					 *  ------<br>
					 */
					class XMLResource : virtual public protocols::MarshallingProtocol{
						
					public:
                        
                        /**
						 *  XMLException_EGIException.
						 */
                        class XMLException_EGIException : EGIBase::EGIException{
                        public:
                            XMLException_EGIException(std::string message) : EGIBase::EGIException(message){}
                            XMLException_EGIException(std::string message, bool exitApplication, bool threadsafe) : EGIBase::EGIException(message, exitApplication, threadsafe){}
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
						XMLResource();
						
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
						virtual ~XMLResource();
						
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
						 *  &nbsp; XMLResource *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual XMLResource *clone() const;
						
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
						 *  &nbsp; XMLResource *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual XMLResource *create() const;
                        
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) XMLResource *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual XMLResource *init(EGIObject *eObject);
                        
                        /**
						 *  Marshalls object to the specified URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The object must be one of the known MFF resource types.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) fromObject: The object to marshal.<br>
                         *  &nbsp; 2) uri: The URI to which to marshal the specified object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = resource exists; false = resource does not exist.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
                        virtual EGIObject *marshal(EGIObject * fromObject, std::string uri) = 0;
                        
                        /**
						 *  Unmarshalls URI to the specified object.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The object must be one of the known MFF resource types.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) toObject: The object to which to marshal.<br>
                         *  &nbsp; 2) uri: The URI from which to marshal.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = resource exists; false = resource does not exist.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
                        virtual EGIObject *unmarshal(EGIObject * toObject, std::string uri) = 0;
						
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
						virtual EGIBase::ClassID getClassID(){return XMLResource::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::XMLResource";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'XMCE';
						
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
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
						XMLResource(const XMLResource& source);
						
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
						XMLResource&  operator=(const XMLResource& source);
						
						//##################
						//End - Assignment.
						//##################
						
					private:
						
					};
				}
			}
		}
	}
}

#endif // XMLResource_DEFINED
