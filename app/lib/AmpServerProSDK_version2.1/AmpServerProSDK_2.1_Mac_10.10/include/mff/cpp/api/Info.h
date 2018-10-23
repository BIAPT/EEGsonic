
/**@file
 *  Info header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef Info_DEFINED
#define Info_DEFINED

#include "EGIObject.h"

#include "MFFResource.h"

#include <string>
#include <vector>

/**
 *  Forward declarations in the EGIBase namespace.
 */
namespace EGIBase {
    
    class EGIXStringWrap;
    
}

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
					
					class SensorLayout;
					
					/**
					 *  Info Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-02-10: Class creation.<br>
					 *  ------<br>
                     *
                     *  ------<br>
                     *  Update: 2012-01-27: Added comments for all fields.<br>
                     *  ------<br>
                     *
                     *  ------<br>
                     *  Update: 2012-01-27: Added support for MFF version number.<br>
                     *  ------<br>
					 */
					class Info : virtual public com::egi::services::mff::api::MFFResource{
						
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
						Info();
						
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
						Info(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType);
						
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
						virtual ~Info();
						
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
						 *  &nbsp; Info *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Info *clone() const;
						
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
						 *  &nbsp; Info *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Info *create() const;
						
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
						 *  &nbsp; Info *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Info *create(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType) const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) Info *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual Info *init(EGIObject *eObject);
                        
                        /**
						 *  Sets the MFF version flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) mFFVersionPresent: The MFF version flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setMFFVersionPresent(bool mFFVersionPresent);
                        
                        /**
						 *  Gets the MFF version flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: The MFF version flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getMFFVersionPresent();
						
						/**
						 *  Sets the MFF version.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) mFFVersion: The MFF version.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setMFFVersion(uint32_t mFFVersion);
						
						/**
						 *  Gets the MFF version.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint32_t: The MFF version.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual uint32_t getMFFVersion();
						
						/**
						 *  Sets the record time.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) recordTime: The record time.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setRecordTime(EGIBase::EGIXStringWrap recordTime);
						
						/**
						 *  Gets the acquisition time.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The record time.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getRecordTime();
						
						/**
						 *  Sets the amp serial number.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) ampSerialNumber: The amp serial number.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAmpSerialNumber(EGIBase::EGIXStringWrap ampSerialNumber);
						
						/**
						 *  Gets the amp serial number.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The amp serial number.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getAmpSerialNumber();
						
						/**
						 *  Sets the amp firmware version.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) ampFirmwareVersion: The amp firmware version.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAmpFirmwareVersion(EGIBase::EGIXStringWrap ampFirmwareVersion);
						
						/**
						 *  Gets the amp firmware version.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The amp firmware version.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getAmpFirmwareVersion();
                        
                        /**
						 *  Sets the movie delta flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) movieDeltaPresent: The movie delta flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setMovieDeltaPresent(bool movieDeltaPresent);
						
						/**
						 *  Gets the movie delta flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: The movie delta flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getMovieDeltaPresent();
						
						/**
						 *  Sets the movie delta.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) movieDelta: The movie delta.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setMovieDelta(uint64_t movieDelta);
						
						/**
						 *  Gets the movie delta.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: The movie delta.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual uint64_t getMovieDelta();
						
						/**
						 *  Sets the amp type flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) ampType: The amp type flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAmpTypePresent(bool ampType);
                        
                        /**
						 *  Gets the amp Type flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: The amp Type flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getAmpTypePresent();
						
						/**
						 *  Sets the amp type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) ampType: The amp type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAmpType(EGIBase::EGIXStringWrap ampType);
						
						/**
						 *  Gets the amp type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: the amp type.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getAmpType();
						
						/**
						 *  Sets the acquisition version number flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) acqVersion: The acquisition number flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAcquisitionVersionPresent(bool acqVersion);
                        
                        /**
						 *  Gets the acquisition version number flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: The acquisition number flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getAcquisitionVersionPresent();
						
						/**
						 *  Sets the acquisition version number.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) acqVersion: The acquisition version number.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAcquisitionVersionNumber(EGIBase::EGIXStringWrap acqVersion);
						
						/**
						 *  Gets the acquisition version number.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: the acquisition version type.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getAcquisitionVersionNumber();

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
						virtual EGIBase::ClassID getClassID(){return Info::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::Info";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'INFO';
						
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
						
						/**
                         *  Indicates whether the MFF version number is present.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This flag is set automatically when setting the mff version.<br>
                         *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
                         *  set to true if it is to be persisted.<br>
                         **/
                        bool mFFVersionPresent_;
                        
                        /**
                         *  The MFF version number.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This number begins at 0.<br>
                         **/
                        uint32_t mFFVersion_;
                        
                        /**
                         *  The record time.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This is in the MFF date time format,
                         *  for example: "2007-09-05T10:48:42.599000+07:00".<br>
                         **/
                        std::string *recordTime_;
                        
                        /**
                         *  The amplifier serial number.
                         *  <b>Notes:</b><br>
                         *  &nbsp; See the MFF usage notes for explanation.<br>
                         **/
						std::string *ampSerialNumber_;
                        
                        /**
                         *  The amplifier firmware version.
                         *  <b>Notes:</b><br>
                         *  &nbsp; See the MFF usage notes for explanation.<br>
                         **/
						std::string *ampFirmwareVersion_;
						
                        /**
                         *  A flag indicating whether the movie delta is present.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This flag is set automatically when setting the movie delta.<br>
                         *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
                         *  set to true if it is to be persisted.<br>
                         **/
                        bool movieDeltaPresent_;
                        
                        /**
                         *  The movie delta.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) Todo: Add explanation here!<br>
                         **/
                        uint64_t movieDelta_;
											
						/**
                         *  A flag indicating whether the amp type is present.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This flag is set automatically when setting the amp type.<br>
                         *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
                         *  set to true if it is to be persisted.<br>
                         **/
						bool ampTypePresent_;

						/**
                         *  The amplifier type.
                         *  <b>Notes:</b><br>
                         *  &nbsp; See the MFF usage notes for explanation.<br>
                         **/
						std::string *ampType_;

						/**
                         *  A flag indicating whether the acquisition version is present.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This flag is set automatically when setting the acquisition version number.<br>
                         *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
                         *  set to true if it is to be persisted.<br>
                         **/
						bool acquisitionVersionPresent_;
						
						/**
                         *  The acquisition version number.
                         *  <b>Notes:</b><br>
                         *  &nbsp; See the MFF usage notes for explanation.<br>
                         **/
						std::string *acquisitionVersionNumber_;
						
						
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
						Info(const Info& source);
						
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
						Info&  operator=(const Info& source);
						
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

#endif // Info_DEFINED

