
/**@file
 *  InfoN header.
 *  @author Robert Bell
 *  @date 25/10/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef InfoN_DEFINED
#define InfoN_DEFINED

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
					
                    class Filter;
                    class Calibration;
                    
					/**
					 *  InfoN Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-10-25: Class creation.<br>
					 *  ------<br>
					 */
					class InfoN : virtual public com::egi::services::mff::api::MFFResource{
						
					public:
                        
                        /**
                         *
                         *  The different types of InfoN files.
                         *
                         */
                        typedef enum{
                            kUnknownInfoNFileType   = -1,
                            kEEG                    = 0,
                            kSpectral               = 1,
                            kSourceData             = 2,
                            kPNSData                = 3,
                            kJTF                    = 4,
                            kTValues                = 5
                        } InfoNFileType;
						
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
						InfoN();
						
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
						InfoN(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType);
						
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
						virtual ~InfoN();
						
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
						 *  &nbsp; InfoN *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual InfoN *clone() const;
						
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
						 *  &nbsp; InfoN *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual InfoN *create() const;
						
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
						 *  &nbsp; InfoN *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual InfoN *create(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType) const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) InfoN *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual InfoN *init(EGIObject *eObject);
						
						/**
						 *  Sets the InfoN file type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp;  1) infoNFileType: The InfoN file type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setInfoNFileType(InfoN::InfoNFileType infoNFileType);
						
						/**
						 *  Gets the InfoN file type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) InfoN::InfoNFileType: The InfoN file type.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual InfoN::InfoNFileType getInfoNFileType();
						
                        /**
						 *  Sets the file type information.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Replaces this object's file type information.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp;  1) fileTypeInformation: The file type information. Retained.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setFileTypeInformation(EGIObject *fileTypeInformation);
						
						/**
						 *  Gets the file type information.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) EGIObject *: The file type information.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual EGIObject *getFileTypeInformation();
                        
                        /**
						 *  Sets the continuation from.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp;  1) continuationFrom: The continuation from.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setContinuationFrom(EGIBase::EGIXStringWrap continuationFrom);
						
						/**
						 *  Gets the continuation from.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) const std::string *: The continuation from.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getContinuationFrom();
                        
                        /**
						 *  Sets the continuation to.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp;  1) continuationFrom: The continuation to.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setContinuationTo(EGIBase::EGIXStringWrap continuationTo);
						
						/**
						 *  Gets the continuation to.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) const std::string *: The continuation to.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getContinuationTo();
                        
                        /**
						 *  Sets the channels.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) channels: The channels.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setChannels(std::vector<uint64_t> *channels);
						
						/**
						 *  Gets the channels.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<uint64_t> *: The channels.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual std::vector<uint64_t> *getChannels();
                        
                        /**
						 *  Sets the exclusion string.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) exclusion: The exclusion string.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setExclusion(EGIBase::EGIXStringWrap exclusion);
						
						/**
						 *  Gets the exclusion string.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The exclusion string.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getExclusion();
                        
                        /**
						 *  Sets the filters.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) filters: The filters.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setFilters(std::vector<Filter *> *filters);
						
						/**
						 *  Gets the filters.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<Filter *> *: The filters.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual std::vector<Filter *> *getFilters();
                        
                        /**
						 *  Sets the calibrations.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) calibrations: The calibrations.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setCalibrations(std::vector<Calibration *> *calibrations);
						
						/**
						 *  Gets the calibrations.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<Calibration *> *: The calibrations.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual std::vector<Calibration *> *getCalibrations();
						
						/**
						 *  Sets the filter adjusted flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) filterAdjusted: the flag whether we've been filter adjusted.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setFilterAdjusted(bool filterAdjusted);
						
						/**
						 *  Gets the filter adjusted
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) bool: whether the file has been filter adjusted.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getFilterAdjusted();
						
						/**
						 *  Sets the filter adjusted shift value.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) shiftValue: How many microseconds the data was adjusted<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setShiftValue(uint64_t shiftValue);
						
						/**
						 *  Gets the shift value
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: the number of microseconds the data was adjusted.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual uint64_t getShiftValue();
						
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
						virtual EGIBase::ClassID getClassID(){return InfoN::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::InfoN";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'EPHS';
						
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
                         *  The InfoN file type.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) Each InfoN describes a signal resource, or more than one signal resource.
                         *  Each of those signal resources is of a particular data type, for example,
                         *  InfoN::kEEG.<br>
                         **/
                        InfoN::InfoNFileType infoNFileType_;
                        
                        /**
                         *  The file type information for this InfoN instance.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) For each file type, there is a corresponding class that contains
                         *  file type specific information. Currently, the actual type of this class can
                         *  be the following:<br>
                         *  &nbsp; i)   com::egi::services::mff::api::InfoNFileTypeEEG<br>
                         *  &nbsp; ii)  com::egi::services::mff::api::InfoNFileTypeSpectral<br>
                         *  &nbsp; iii) com::egi::services::mff::api::InfoNFileTypeSourceData<br>
                         *  &nbsp; iv)  com::egi::services::mff::api::InfoNFileTypePNSData<br>
                         *  &nbsp; v)   com::egi::services::mff::api::InfoNFileTypeJTF<br>
                         *  &nbsp; vi)  com::egi::services::mff::api::InfoNFileTypeTValues<br>
                         *  .<br>
                         **/
                        EGIObject *fileTypeInformation_;
                        
                        /**
                         *  Continuation from.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) This is now not currently used, but it still being picked
                         *  up in the resource if it is available. It indicated the continuation
                         *  "from" resource, ie, the signal resource preceeding this one. This
                         *  occurs when a signal resource is split over multiple resources.<br>
                         **/
                        std::string *continuationFrom_;
                        
                        /**
                         *  Continuation to.
                         *  <b>Notes:</b><br>
                         *  &nbsp; This is now not currently used, but it still being picked
                         *  up in the resource if it is available. It indicated the continuation
                         *  "to" resource, ie, the signal resource succeeding this one. This
                         *  occurs when a signal resource is split over multiple resources.<br>
                         **/
                        std::string *continuationTo_;
                        
                        /**
                         *  A list of channels for this InfoN that have some attribute to take into
                         *  account.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) The exclusion string for this segment (property exclusion) indicates what the
                         *  attribute is. For example, "badChannels".<br>
                         **/
                        std::vector<uint64_t> *channels_;
                        
                        /**
                         *  The exclusion attribute for this InfoN's channel list.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) The channels property (property channels) gives a list of channels for
                         *  which some attribute is taken into account. This exclusion string indicates what
                         *  that attribute is. For example, "badChannels" or "goodChannels".<br>
                         **/
                        std::string *exclusion_;
                        
                        /**
                         *  The list of filters.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) See the com::egi::services::mff::api::Filter class for more information.<br>
                         **/
                        std::vector<Filter *> *filters_;
                        
                        /**
                         *  The list of calibrations.
                         *  <b>Notes:</b><br>
                         *  &nbsp; 1) See the com::egi::services::mff::api::Calibration class for more information.<br>
                         **/
						std::vector<Calibration *> *calibrations_;
                        
						/**
						 *	Whether the file has been adjusted for the hardware filter offset
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) YES means that the data has already been adjusted for the hardware filter offset, NO or absent means that it still needs updated
						 **/
						bool filterAdjusted_;
						
						/**
						 *	The amount the data has been shifted to adjust for the anti alaising filter offset
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) the number of microseconds the data has been adjusted/
						 **/
						uint64_t shiftValue_;
						
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
						InfoN(const InfoN& source);
						
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
						InfoN&  operator=(const InfoN& source);
						
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

#endif // InfoN_DEFINED
