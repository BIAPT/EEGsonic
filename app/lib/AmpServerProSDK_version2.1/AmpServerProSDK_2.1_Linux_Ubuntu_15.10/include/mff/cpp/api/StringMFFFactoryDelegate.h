
/**@file
 *  StringMFFFactoryDelegate header.
 *  @author Robert Bell
 *  @date 11/04/2014
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef StringMFFFactoryDelegate_DEFINED
#define StringMFFFactoryDelegate_DEFINED

#include "EGIObject.h"
#include "EGIException.h"

#include "MFFFactoryDelegate.h"

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
				 *  api namespace.
				 */
				namespace api{
                    
                    class MFFResource;
                    class MFFResourceType;
					
					/**
					 *  StringMFFFactoryDelegate Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2014-04-11: Class creation.<br>
					 *  ------<br>
					 */
					class StringMFFFactoryDelegate : virtual public protocols::MFFFactoryDelegate{
						
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
						StringMFFFactoryDelegate();
						
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
						virtual ~StringMFFFactoryDelegate();
						
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
						 *  &nbsp; StringMFFFactoryDelegate *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual StringMFFFactoryDelegate *clone() const;
						
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
						 *  &nbsp; StringMFFFactoryDelegate *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual StringMFFFactoryDelegate *create() const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) StringMFFFactoryDelegate *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual StringMFFFactoryDelegate *init(EGIObject *eObject);
                        
                        /**
						 *  Tests whether a resource exists at the specified URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI to test.<br>
                         *  &nbsp; 2) resourceType: The type of resource (pass kAny to simply test for any resource
                         * at that URI).<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = resource exists; false = resource does not exist.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool resourceExistsAtURI(std::string uri, MFFResourceType *resourceType);
                        
                        /**
						 *  Creates a resource of the specified type at the specified URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Fails if the caller does not have permissions to create
                         *  a resource of the given type at URI.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI at which to create the resource.<br>
                         *  &nbsp; 2) resourceType: The type of resource to create.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool createResourceAtURI(std::string uri, MFFResourceType *resourceType);
                        
                        /**
						 *  Deletes a resource of the specified type at the specified URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
                         *  or the caller does not have permissions to delete the resource.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI of the resource to be deleted.<br>
                         *  &nbsp; 2) resourceType: The type of resource being moved.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool deleteResourceAtURI(std::string uri, MFFResourceType *resourceType);
                        
                        /**
						 *  Moves a resource of the specified type at the specified source URI to the
                         *  the specified destination URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
                         *  or the caller does not have permissions to move the resource.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) sourceURI: The source URI to be moved.<br>
                         *  &nbsp; 2) destinationURI: The destination URI to which to move the resource.<br>
                         *  &nbsp; 3) resourceType: The type of resource being moved.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool moveResourceAtURI(std::string sourceURI, std::string destinationURI, MFFResourceType *resourceType);
                        
                        /**
						 *  Copies a resource of the specified type at the specified source URI to the
                         *  the specified destination URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
                         *  or the caller does not have permissions to copy the resource.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) sourceURI: The source URI to be copied.<br>
                         *  &nbsp; 2) destinationURI: The destination URI to which to copy the resource.<br>
                         *  &nbsp; 3) resourceType: The type of resource being copied.<br>
                         *  &nbsp; 4) excludeResources: Any resource contained as a sub-resource of the source resource,
                         *  the identifier of which matches (or contains) an element inexcludeResources will not be copied.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool copyResourceAtURI(std::string sourceURI, std::string destinationURI,
                                                       MFFResourceType *resourceType, const std::vector<std::string> *excludeResources);
                        
                        /**
						 *  Copies a resource of the specified type at the specified source URI to the
                         *  the specified destination URI.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
                         *  or the caller does not have permissions to copy the resource.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI at which the resource is located.<br>
                         *  &nbsp; 2) resourceType: The type of resource.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) MFFResource *: The newly opened resource, or NULL if the resource failed to open.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual MFFResource *openResourceAtURI(std::string uri, MFFResourceType *resourceType);
                        
                        /**
						 *  Closes specified resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) resource: The resource to close.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: true = sucess; false = failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) ...mff::api::Resource_MFFException: Indicates that the desired operation could not be completed.<br>
						 */
						virtual bool closeResource(MFFResource *resource);
						
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
						virtual EGIBase::ClassID getClassID(){return StringMFFFactoryDelegate::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::StringMFFFactoryDelegate";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'STTE';
						
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
                        
                        void *encoding_;
						
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
						StringMFFFactoryDelegate(const StringMFFFactoryDelegate& source);
						
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
						StringMFFFactoryDelegate&  operator=(const StringMFFFactoryDelegate& source);
						
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

#endif // StringMFFFactoryDelegate_DEFINED

