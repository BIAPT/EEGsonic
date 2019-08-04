
/**@file
 *  MFFUtils header.
 *  @author Robert Bell
 *  @date 15/12/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef MFFUtils_DEFINED
#define MFFUtils_DEFINED

#include "EGIObject.h"
#include "EGIException.h"

#include <vector>
#include "InfoN.h"

// "Restricted" using declarations. Restricted so as not to expose
// the entire namespace, but needed to make the code readable.
using namespace com::egi::services;

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
				namespace api{
                    
                    class MFFResourceType;
                    class SignalResource;
                    class SignalBlock;
                    class Epoch;
                    class Event;
                    class Category;
                    class Segment;
                    
                }
                
				/**
				 *  util namespace.
				 */
				namespace util{
					
					/**
					 *  MFFUtils Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-10-10: Class creation.<br>
					 *  ------<br>
                     *
                     *  ------<br>
					 *  Update: 2012-05-18: Added method to convert microsecond MFF datetime format back
                     *  into the nanosecond ( old format ). This is useful for supporting older files.<br>
					 *  ------<br>
					 */
					class MFFUtils : virtual public EGIBase::EGIObject{
						
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
						MFFUtils();
						
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
						virtual ~MFFUtils();
						
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
						 *  &nbsp; MFFUtils *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFUtils *clone() const;
						
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
						 *  &nbsp; MFFUtils *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFUtils *create() const;
                        
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) MFFUtils *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual MFFUtils *init(EGIObject *eObject);
						
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
						virtual EGIBase::ClassID getClassID(){return MFFUtils::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::MFFUtils";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'MFIL';
						
						//####################################
						//End - Class variables.
						//####################################
						
						//####################################
						//Class methods.
						//####################################
                        
                        /**
						 *  Attempts to detect when non-valid characters are present in the text uri given.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) MFF supports UTF-8. This method tries to detect when invalid character sequences
                         *  are present in at the given uri.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
                         *  &nbsp; 1) uri: The uri to test.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) true: uri passes the verify test; false: uri fails the verify test.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static bool isValidUTF8Resource(const char *uri);
                        
                        static bool fixUTF8Resource(const char *resourceURI, mff::api::MFFResourceType *resourceType,
                                                    bool saveOldFile, char replaceWith = '?');
                        
                        /**
						 *  Gets all events in the MFF resource.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
                         *  &nbsp; 1) mffResourceURI: The MFF resource.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<mff::api::Event *> *: A list of all the events in the MFF resource.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::vector<mff::api::Event *> *getAllEvents(std::string mffResourceURI);
                        
                        /**
						 *  Gets the segment's corresponding epoch.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) segment: The segment.<br>
                         *  &nbsp; 2) mffResourceURI: The MFF resource.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) mff::api::Epoch *: The epoch that corresponds to the segment.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static mff::api::Epoch *getEpochForSegment(mff::api::Segment *segment,
                                                                   std::string mffResourceURI);
                        
                        /**
						 *  Gets the epochs for the segments in the category.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The epochs vector returned is in the same order as the segments in
                         *  the category.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) category: The category.<br>
                         *  &nbsp; 2) mffResourceURI: The MFF resource.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<mff::api::Epoch *> *: The list of epochs
                         *  for the segments in the category.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::vector<mff::api::Epoch *> *getEpochsForSegmentsInCategory(mff::api::Category *category,
                                                                                              std::string mffResourceURI);
                        
                        /**
						 *  Gets the signal blocks for the given epoch.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Only EEG signal data is supported.<br>
                         *  &nbsp; 2) All EEG signal data is contained in the first EEG signal file. A later
                         *  version might support for multiple signal files.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) epoch: The epoch.<br>
                         *  &nbsp; 2) mffResourceURI: The MFF resource.<br>
                         *  &nbsp; 3) signalResource: The signal resource used to load the signal resource. This
                         *  is useful (if not required) for loading the block data into the returned signal blocks.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<mff::api::SignalBlock *> *: The list of signal blocks. This
                         *  is a vector of signal blocks that have all be loaded with the signal block data and retained. No copy is made. Use
                         *  the EGIBase macro: RELEASE_VECTOR to clean up, or manually release every signal block object before deleting
                         *  the vector.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::vector<mff::api::SignalBlock *> *getSignalBlocksForEpoch(mff::api::Epoch *epoch,
                                                                                             std::string mffResourceURI,
                                                                                             mff::api::SignalResource **signalResource,
                                                                                             api::InfoN::InfoNFileType dataType =  api::InfoN::kEEG);
                        
                        /**
						 *  Gets data for an epoch as one signal block. NOT IMPLEMENTED YET!
                         
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Only EEG signal data is supported.<br>
                         *  &nbsp; 2) All EEG signal data is contained in the first EEG signal file. A later
                         *  version might support for multiple signal files.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) epoch: The desired signal blocks' epoch.<br>
                         *  &nbsp; 2) mffResourceURI: The MFF resource.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) mff::api::SignalBlock *: The signal block containing all the data for that epoch. Note
                         *  that if this is a new signal block an is owned by the caller.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
						 */
                        static mff::api::SignalBlock *getDataForEpoch(mff::api::Epoch *epoch,
                                                                      std::string mffResourceURI);
                        
                        /**
						 *  Gets data for a particular signal in the signal block.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) signalBlock: The desired signal's signal block.<br>
                         *  &nbsp; 2) signalNumber: The signal number (zero-based).<br>
                         *  &nbsp; 3) sizeOfDataInBytes: The size of data in bytes returned. If NULL is passed in, then not filled in.<br>
                         *  &nbsp; 4) signalDepthInBits: The signal depth in bits. If NULL is passed in, then not filled in.<br>
                         *  &nbsp; 5) numberOfSamples: The number of samples returned (which will be the number of
                         *  of samples present for this signal in the signal block). If NULL is passed in, then not filled in.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) char *: Signal data for the desired signal.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static char *getDataForSignalInSignalBlock(mff::api::SignalBlock *signalBlock,
                                                                   uint32_t signalNumber,
                                                                   uint32_t *sizeOfDataInBytes,
                                                                   uint32_t *signalDepthInBits,
                                                                   uint32_t *numberOfSamples);
                        
                        /**
						 *  Gets the current timezone.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) int: The time zone.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static int getTimezone();
                        
                        /**
						 *  Converts an MFF date time string to microseconds since epoch.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Examples of an MFF date time string are:<br>
                         *  &nbsp; &nbsp; i) 2011-09-12T10:53:36.140373-07:00<br>
                         *  &nbsp; &nbsp; ii) 2012-01-10T14:23:45.140373+01:00<br>
                         *  &nbsp; 2) The time zone will be extracted during the parsing of the
                         *  string, and return in the reference argument "timeZone". This will be the time zone offset
                         *  in seconds. Thus, in (i) above, the value would be: (-7 * 3600) = -25200.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) dateTime: An MFF date time string.<br>
                         *  &nbsp; 2) timeZone: An int expressing the timezone (will be filled in by
                         *  this function whilst parsing of the data time string given in argument 1 (dateTime).<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) uint64_t: Microseconds since epoch. This is the Unix epoch
                         *  of midnight, January 1st, 1970.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static uint64_t mffDateTimeToMicroseconds(std::string dateTime, int &timeZone);
                        
                        /**
						 *  Converts microseconds since epoch to an MFF date time string.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Examples of an MFF date time string are:<br>
                         *  &nbsp; &nbsp; i) 2011-09-12T10:53:36.140373-07:00<br>
                         *  &nbsp; &nbsp; ii) 2012-01-10T14:23:45.140373+01:00<br>
                         *  &nbsp; 2) A time zone of "-07:00" desired in the string should for example be passed in as
                         *  timezone = (-7 * (the number of seconds in an hour)) = (-7 * 3600).<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) microseconds: Microseconds since epoch. This is the Unix epoch
                         *  of midnight, January 1st, 1970.<br>
                         *  &nbsp; 2) timeZone: An int expressing the timezone.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::string: The resulting MFF data time string.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::string microsecondsToMFFDateTime(uint64_t microseconds, int timeZone = 0);
                        
                        /**
						 *  Calculates the difference between two MFF date time strings in microseconds.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The difference is dateTime1 - dateTime2. Thus, if dateTime1 represents a time
                         *  before dateTime2, the value will be negative.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1): dateTime1: Date time string 1.<br>
                         *  &nbsp; 2): dateTime2: Date time string 2, which is subtracted from date time string 1.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1); uint64_t: The difference i microseconds.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static uint64_t mffDateTimeDifferenceInMicroseconds(std::string dateTime1, std::string dateTime2);
                        
                        /**
						 *  Converts an MFF string in nanosecond data time format to one in microseconds.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The old MFF format used nanoseconds as a resolution, thus there existed strings
                         *  in the following format:<br>
                         *  &nbsp; &nbsp; "2011-09-12T10:53:36.140373000-07:00"<br>
                         *  This method will remove the sub-microsecond portion of the string, thus using the example
                         *  above, the following string will be returned:
                         *  &nbsp; &nbsp; "2011-09-12T10:53:36.140373-07:00"<br>
                         *  Please note that the string will remain unchanged if for some reason the string is not in
                         *  the expected nanosecond format (for example, the nanoseconds have already been removed).
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) dateTime: Date time destined for nanosecond removal.<br>
                         *  &nbsp; 2) error: Used to indicate that the string could not be converted and thus remains the same.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::string: The date time string with the nanoseconds removed, or the original
                         *  string if the error flag is set.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::string nanosecondToMicrosecondDateTime(std::string dateTime, bool &error);
                        
                        /**
						 *  Converts an MFF string in microsecond data time format to one in nanoseconds ( the old MFF format ).
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) The old MFF format used nanoseconds as a resolution, thus there existed strings
                         *  in the following format:<br>
                         *  &nbsp; &nbsp; "2011-09-12T10:53:36.140373000-07:00"<br>
                         *  This method will add 000 to the microsecond portion of the string.<br>
                         *  Please note that the string will remain unchanged if for some reason the string is not in
                         *  the expected microsecond format (for example, the nanoseconds have already been added).<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) dateTime: Date time destined for nanosecond removal.<br>
                         *  &nbsp; 2) error: Used to indicate that the string could not be converted and thus remains the same.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::string: The date time string with the nanoseconds removed, or the original
                         *  string if the error flag is set.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
                        static std::string microsecondToNanosecondDateTime(std::string dateTime, bool &error);
                        
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
						MFFUtils(const MFFUtils& source);
						
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
						MFFUtils&  operator=(const MFFUtils& source);
						
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

#endif // MFFUtils_DEFINED
