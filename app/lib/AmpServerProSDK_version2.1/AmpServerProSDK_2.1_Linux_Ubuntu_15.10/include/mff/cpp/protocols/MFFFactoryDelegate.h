
/**@file
 *  MFFFactoryDelegateDelegate header.
 *  @author Robert Bell
 *  @date 15/08/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef MFFFactoryDelegate_DEFINED
#define MFFFactoryDelegate_DEFINED

#include "EGIObject.h"
#include "EGIException.h"
#include <vector>

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
                
                // Forward declarations in the api namespace.
                namespace api{
                    
                    class MFFResource;
                    class MFFResourceType;
                    
                }
                
				/**
				 *  protocols namespace.
				 */
                namespace protocols{
                    
					/**
					 *  MFFFactoryDelegate Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-08-15: Class creation.<br>
					 *  ------<br>
					 */
					class MFFFactoryDelegate : virtual public EGIBase::EGIObject{
						
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
						MFFFactoryDelegate();
						
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
						virtual ~MFFFactoryDelegate();
						
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
						 *  &nbsp; MFFFactoryDelegate *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFFactoryDelegate *clone() const;
						
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
						 *  &nbsp; MFFFactoryDelegate *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFFactoryDelegate *create() const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) MFFFactoryDelegate *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual MFFFactoryDelegate *init(EGIObject *eObject);
                        
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
						virtual bool resourceExistsAtURI(std::string uri, api::MFFResourceType *resourceType) = 0;
                        
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
						virtual bool createResourceAtURI(std::string uri, api::MFFResourceType *resourceType) = 0;
                        
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
						virtual bool deleteResourceAtURI(std::string uri, api::MFFResourceType *resourceType) = 0;
                        
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
						virtual bool moveResourceAtURI(std::string sourceURI, std::string destinationURI, api::MFFResourceType *resourceType) = 0;
                        
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
                                                       api::MFFResourceType *resourceType, const std::vector<std::string> *excludeResources) = 0;
                        
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
						virtual api::MFFResource *openResourceAtURI(std::string uri, api::MFFResourceType *resourceType) = 0;
                        
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
						virtual bool closeResource(api::MFFResource *resource) = 0;
						
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
						virtual EGIBase::ClassID getClassID(){return MFFFactoryDelegate::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::MFFFactoryDelegate";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'MFTE';
						
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
						MFFFactoryDelegate(const MFFFactoryDelegate& source);
						
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
						MFFFactoryDelegate&  operator=(const MFFFactoryDelegate& source);
						
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

#endif // MFFFactoryDelegate_DEFINED

