
/**@file
 *  MFFFile header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef MFFFile_DEFINED
#define MFFFile_DEFINED

#include "EGIObject.h"
#include "MFFResource.h"
#include "EGIException.h"

// Here because we require InfoN::InfoNFileType.
#include "InfoN.h"

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
				/**
				 *  api namespace.
				 */
				namespace api{
					
					class File_MFFException : public EGIBase::EGIException{
                        
					public:
                        
						File_MFFException(std::string message) : EGIException(message){}
						File_MFFException(std::string message, bool exitApplication, bool threadsafe) : EGIBase::EGIException(message, exitApplication, threadsafe){}
                        
					};
					
					/**
					 *  MFFFile Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-02-10: Class creation.<br>
					 *  ------<br>
                     *
                     *  ------<br>
					 *  Update: 2012-04-05: Added convenience method for obtaining signal files
                     *  of a desired type.<br>
					 *  ------<br>
					 */
					class MFFFile : virtual public com::egi::services::mff::api::MFFResource{
						
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
						MFFFile();
                        
                        /**
						 *  Contructor.
						 *  <b>Notes:</b><br>
						 *  &nbsp; Thread safety is off.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI for this resource.<br>
                         *  &nbsp; 2) resourceDelegate: The resource delegate.<br>
                         *  &nbsp; 3) resourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						MFFFile(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType);
						
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
						virtual ~MFFFile();
						
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
						 *  &nbsp; MFFFile *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFFile *clone() const;
						
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
						 *  &nbsp; MFFFile *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFFile *create() const;
                        
                        /**
						 *  Create.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Implements the virtual constructor idiom.<br>
						 *  &nbsp; 2) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) uri: The URI for this resource.<br>
                         *  &nbsp; 2) resourceDelegate: The resource delegate.<br>
                         *  &nbsp; 3) resourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; MFFFile *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFFile *create(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType) const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) MFFFile *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual MFFFile *init(EGIObject *eObject);
                        
                        /**
						 *  Get the MFF version.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) MFF versions start at 1. Thus, a value of zero indicates that no version
                         *  is present.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint32_t: The MFF version number.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual uint32_t getMFFVersion();
                        
                        /**
						 *  Get the resource size in bytes.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: Resource size in bytes.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual uint64_t getResourceSizeInBytes();
						
						/**
						 *  Gets a list of the resources associated with this MFF resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
                         *  &nbsp; 2) excludeResources: Any resource contained as a sub-resource of the source resource,
                         *  the identifier of which matches (or contains) an element inexcludeResources will not be listed.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<std::string>: The resource listing.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual std::vector<std::string> *getResourceList(bool fullURI,
                                                                          const std::vector<std::string> *excludeResources = NULL);
                        
                        /**
						 *  Gets a list of the signal resources associated with this MFF resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<std::string>: The signal resource listing. An empty list is
                         *  if no signal resources are found.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual std::vector<std::string> *getSignalResourceList(bool fullURI);
                        
                        /**
						 *  Gets the InfoN resource corresponding to the given signal resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<std::string>: The InfoN resource corresponding to the given signal resource.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual std::string getCorrespondingInfoNResource(std::string signalURI);
                        
                        /**
						 *  Gets a list of the signal resources associated with this MFF resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
                         *  &nbsp; 1) type: The type of signal resources to be returned.<br>
						 *  &nbsp; 2) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<std::string>: The signal resource listing of the desired type. An empty list is
                         *  if no signal resources of the desired type are found.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: An error ocurred.<br>
						 */
						virtual std::vector<std::string> *getSignalResourceListOfType(InfoN::InfoNFileType type, bool fullURI);
                        
                        /**
						 *  Gets the record time (most often equal to the acquisition time).
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::string: The record time.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual std::string getRecordTime();
						
						/**
						 *  Gets the number of event tracks.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) int: The number of event tracks. On failure, -1 is returned.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: The most likely cause of failure is that
						 *  an MFF file has not been loaded yet by this instance.<br>
						 */
						virtual int getNumberOfEventTracks();
						
						/**
						 *  Gets the list of event tracks.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) fullURI: If this is true, the full URI is returned, otherwise
                         *  a URI that is relative to the URI of the MFF resource is returned.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<std::string>: The event track list for this file; empty list on failure.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: The most likely cause of failure is that
						 *  an MFF file has not been loaded yet by this instance.<br>
						 */
						virtual std::vector<std::string> *getEventTrackList(bool fullURI);
						
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
						virtual EGIBase::ClassID getClassID(){return MFFFile::classID;}
						
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
						virtual std::string toString() const {return com::egi::services::mff::api::MFFResource::toString() + "::MFFFile";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'MFLE';
						
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
						MFFFile(const MFFFile& source);
						
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
						MFFFile&  operator=(const MFFFile& source);
						
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

#endif // MFFFile_DEFINED

