
/**@file
 *  MFFFileWriterUtilities header.
 *  @author Robert Bell
 *  @date 06/12/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef MFFFileWriterUtilities_DEFINED
#define MFFFileWriterUtilities_DEFINED

#include "EGIObject.h"
#include "AS_Network_Types.h"

// MFF - Needed for some of the enum types in the signatures.
#include "MFFResourceType.h"
#include "InfoN.h"
#include "InfoNFileTypeEEG.h"

// Forward declarations.
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
                    class MFFFactory;
                    class SignalResource;
                    
                }
            }
        }
    }
}

/**
 *  MFFFileWriterUtilities Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class is encapsulates most of the writing to EGI's MFF format. It is not
 *  inclusive, meaning that the MFF is a rich format and can include many data elements not
 *  represented here, but the files created using this class will open in Net Station Review.
 *
 *  ------<br>
 *  Update: 2015-12-06: Class creation.<br>
 *  ------<br>
 */
class MFFFileWriterUtilities : virtual public EGIBase::EGIObject{
    
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
    MFFFileWriterUtilities();
    
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
    virtual ~MFFFileWriterUtilities();
    
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
     *  &nbsp; MFFFileWriterUtilities *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual MFFFileWriterUtilities *clone() const;
    
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
     *  &nbsp; MFFFileWriterUtilities *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual MFFFileWriterUtilities *create() const;
    
    /**
     *  Init.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; eObject: Initialization object.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; 1) MFFFileWriterUtilities *: This object.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
     *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
     */
    virtual MFFFileWriterUtilities *init(EGIObject *eObject);
    
    /**
     *  Creates the base MFF "file (which is actually a folder)" with the passed values.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example is tailored to this application and does not provide an illustration
     *  of all the different ways an MFF file could be created.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use to create this xml resource.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 5) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool createMFFFile(com::egi::services::mff::api::MFFFactory *factory,
                              std::string mffFileURI,
                              std::string& message);
    
    /**
     *  Creates a signal resource at the appropriate URI, and opens it.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example behaves slightly differently from the other creation ones as it
     *  merely creates an empty signal file resource that the user can use.<br>
     *  &nbsp; 2) Since the signal resource returned is open, the user must remember to close the resource
     *  using the same factory as that with which is was opened.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) signalFileName: The name for the signal resource, for example "signal1.bin".<br>
     *  &nbsp; 4) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; com::egi::services::mff::api::SignalResource *: An opened signal resource, or NULL if a failure occurred.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static com::egi::services::mff::api::SignalResource *createSignalFile(com::egi::services::mff::api::MFFFactory *factory,
                                                                          std::string mffFileURI,
                                                                          std::string signalFileName,
                                                                          std::string& message);
    
    /**
     *  Creates an info.xml file with the passed values.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example is tailored to this application and does not provide an illustration
     *  of all the different ways an xml file of this resource type could be created.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use to create this xml resource.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) ampInfo: The various items of amplifier information used in info.xml resources.<br>
     *  &nbsp; 4) beginTime: The record begin time (usually the start of recording).<br>
     *  &nbsp; 5) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool createInfoFile(com::egi::services::mff::api::MFFFactory *factory,
                               std::string mffFileURI,
                               AS_Network_Types::AmpInfo ampInfo,
                               std::string beginTime,
                               std::string& message);
    
    /**
     *  Creates an infoN.xml file of the appropriate type.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example only supports creating an EEG version.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use to create this xml resource.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) infoNFileType: The type of infoN file to create.<br>
     *  &nbsp; 4) netCode: The net code corresponding to the desired EGI net type.<br>
     *  &nbsp; 5) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool createInfoNFile(com::egi::services::mff::api::MFFFactory *factory,
                                std::string mffFileURI,
                                com::egi::services::mff::api::InfoN::InfoNFileType infoNFileType,
                                AS_Network_Types::NetCode netCode,
                                std::string& message);
    
    /**
     *  Creates either a coordinates.xml or a sensorLayout.xml file for the appropriate net code (EGI net).
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example is tailored to this application and does not provide an illustration
     *  of all the different ways an xml file of this resource type could be created.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use to create this xml resource.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) netCode: The net code corresponding to the desired EGI net type.<br>
     *  &nbsp; 4) mffType: The resource type. This should be either "MFFResourceType::kMFF_RT_Coordinates" or
     *  "MFFResourceType::kMFF_RT_SensorLayout"<br>
     *  &nbsp; 5) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool createLayoutFile(com::egi::services::mff::api::MFFFactory *factory,
                                 std::string mffFileURI,
                                 AS_Network_Types::NetCode netCode,
                                 com::egi::services::mff::api::MFFResourceType::_MFFResourceType mffType,
                                 std::string& message);
    
    /**
     *  Returns the appropriate layout name for the net code.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This method is used to obtain the sensorLayout and coordinates names.<br>
     *  &nbsp; 2) This method differs from MFFFileWriterUtilities::getLayoutNameForNetType(...) as
     *  it just provides the names, not the full URI.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) netCode: The net code.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; std::string: The layout name. The empty string is returned if
     *  an error occured.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static std::string getLayoutNameForNetType(AS_Network_Types::NetCode netCode);
    
    /**
     *  Returns the appropriate layout file for the net code.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This method is used to obtain the sensorLayout and coordinates xml files.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) netCode: The net code.<br>
     *  &nbsp; 2) layoutType: The layout type. This should be either "CoordinateLayouts" or "SensorLayouts".<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; std::string: The full system path to the file layout file requested. The empty string is returned if
     *  an error occured.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static std::string getLayoutURIForNetType(AS_Network_Types::NetCode netCode, std::string layoutType);
    
    /**
     *  Returns a URI to an application resource (referenced by this application).
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This method is used to obtain the sensorLayout and coordinates xml files.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) name: The name of the resource minus the dot and extension.<br>
     *  &nbsp; 2) extension: The extension for the type of resource requested.<br>
     *  &nbsp; 3) type: Subdirectory in the application resource folder for the file.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; std::string: The full system path to the file requested. The empty string is returned if
     *  an error occured.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static std::string getURIForResource(std::string name,
                                         std::string extension,
                                         std::string type);
    
    /**
     *  Creates an epochs.xml file with the passed values.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This example is tailored to this application and does not provide an illustration
     *  of all the different ways an xml file of this resource type could be created.<br>
     *  &nbsp; 2) This example creates a single epoch for the entire duration of the recording.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use to create this xml resource.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) beginTime: The relative record begin time from the start of recording (usually zero).<br>
     *  &nbsp; 4) endTime: The relative record end time from the start of recording.<br>
     *  &nbsp; 6) blockCount: The number of blocks for this single epoch recording.<br>
     *  &nbsp; 7) message: Anything of interest that needs to be propagated to the caller is placed here. For
     *  example, should an error occur, the error message will be in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool createEpochFile(com::egi::services::mff::api::MFFFactory *factory,
                                std::string mffFileURI,
                                uint64_t beginTime,
                                uint64_t endTime,
                                uint64_t blockCount,
                                std::string& message);
    
    /**
     *  Writes a signal block to the signal resource.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) resource: An open signal resource. The resource MUST be open.<br>
     *  &nbsp; 2) data: The data to write. This data is assumed to be in the one of the sample
     *  formats used by EGI amplifiers.<br>
     *  &nbsp; 3) sizeOfData: The size of the data, in bytes.<br>
     *  &nbsp; 4) amplifierType: The amplifer type.<br>
     *  &nbsp; 5) packetType: The packet type.<br>
     *  &nbsp; 6) numberOfChannels: The number of channels.<br>
     *  &nbsp; 7) frequency: The sampling rate of the file (the MFF calls this the frequency).<br>
     *  &nbsp; 8) firstBlock: Whether this is the first block in the file.<br>
     *  &nbsp; 9) continuationBlock: Whether this is continuation block, that is, whether the block layout
     *  is identical to the previous block except for the actual signal data in each location.<br>
     *  &nbsp; 10) netCode: The detected net code is filled in here.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool writeSignalBlock(com::egi::services::mff::api::SignalResource *resource,
                                 char *data,
                                 int64_t sizeOfData,
                                 AS_Network_Types::AmplifierType amplifierType,
                                 AS_Network_Types::PacketType packetType,
                                 int numberOfChannels,
                                 int frequency,
                                 bool firstBlock,
                                 bool continuationBlock,
                                 AS_Network_Types::NetCode &netCode);
    
    /**
     *  Writes the closing counts to the signal resource.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Currently the closing counts are the number of blocks in the signal file and
     *  the number of samples.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) factory: The MFF factory to use.<br>
     *  &nbsp; 2) mffFileURI: The base URI for the MFF resource.<br>
     *  &nbsp; 3) signalFileName: The name for the signal resource, for example "signal1.bin".<br>
     *  &nbsp; 4) blockCount: The block count.<br>
     *  &nbsp; 5) sampleCount: The sample count.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- success, false- failure.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    static bool writeClosingCountsToSignalFile(com::egi::services::mff::api::MFFFactory *factory,
                                               std::string mffFileURI,
                                               std::string signalFileName,
                                               uint64_t blockCount,
                                               uint64_t sampleCount);
    
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
    virtual EGIBase::ClassID getClassID(){return MFFFileWriterUtilities::classID;}
    
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
    virtual std::string toString() const {return EGIObject::toString() + "::MFFFileWriterUtilities";}
    
    //####################################
    //Class variables.
    //####################################
    
    /**
     *  Class ID
     *  Specifies the class id for instances of this class.
     */
    static const EGIBase::ClassID classID = 'MFES';
    
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
    MFFFileWriterUtilities(const MFFFileWriterUtilities& source);
    
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
    MFFFileWriterUtilities&  operator=(const MFFFileWriterUtilities& source);
    
    //##################
    //End - Assignment.
    //##################
    
private:
    
};

#endif // MFFFileWriterUtilities_DEFINED

