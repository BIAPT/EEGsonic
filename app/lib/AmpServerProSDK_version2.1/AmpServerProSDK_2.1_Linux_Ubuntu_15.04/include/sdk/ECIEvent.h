
/**@file
 *  ECIEvent header.
 *  @author Robert Bell
 *  @date 27/07/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef ECIEvent_DEFINED
#define ECIEvent_DEFINED

#include "EGIObject.h"
#include <vector>
#include <string>

// Forward defines for the MFF.

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
                    
                    class Event;
                    
                }
                
            }
            
        }
        
    }
    
}


/**
 *  ECIEvent Class.
 *  @author Robert Bell.
 *  @remarks
 *  Place notes here.
 *
 *  ------<br>
 *  Update (001): 2012-07-27: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2015-06-10: Updated to include correct type interpretatons from the various ECI
 *  key types.<br>
 *  ------<br>
 */
class ECIEvent : virtual public EGIBase::EGIObject{
    
public:
    
    typedef struct {
        
        uint64_t dataLength;
        char *data;
        
    } EncodedEvent;
    
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
    ECIEvent();
    
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
     *  &nbsp; N/A<br>
     */
    ECIEvent(const ECIEvent& source);
    
    //####################################
    //End - Constructor(s).
    //####################################
    
    //####################################
    //Destructor.
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
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    ECIEvent&  operator=(const ECIEvent& source);
    
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
    virtual ~ECIEvent();
    
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
     *  &nbsp; ECIEvent *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ECIEvent *clone() const;
    
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
     *  &nbsp; ECIEvent *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ECIEvent *create() const;
    
    /**
     *  Init.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; eObject: Initialization object.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; 1) ECIEvent *: This object.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
     *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
     */
    virtual ECIEvent *init(EGIObject *eObject);
    
    /**
     *  Decodes an ECI event.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) encodedEvent: The encoded event.<br>
     *  &nbsp; 2) swapBytes: Whether to swap the bytes for transport.<br>
     *  &nbsp; 3) baseTime: ECI events are typically distributed relative to a recording start time. Recording
     *  start time is referred to as "base time" for this method. If a base time >0 is provided, this will be ADDED
     *  to the event's time for convenience. You should use the same base time during the decode process as the encode
     *  process. Typically, this will require that both systems are aware of the start time (which is provided in the ECI
     *  protocol).<br>
     *  &nbsp; 4) timeZone: The event time will be adjusted for the provided timezone. You should use the same time
     *  zone during the decode process as the encode.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; com::egi::services::mff::api::Event *: An MFF event object.<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    static com::egi::services::mff::api::Event *decodeEvent(const EncodedEvent *encodedEvent,
                                                            bool swapBytes,
                                                            uint64_t baseTime,
                                                            int timeZone = 0);
    
    /**
     *  Encodes an ECI event.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) event: An MFF event object.<br>
     *  &nbsp; 2) swapBytes: Whether to swap the bytes for transport.<br>
     *  &nbsp; 3) baseTime: ECI events are typically distributed relative to a recording start time. Recording
     *  start time is referred to as "base time" for this method. If a base time >0 is provided, this will be ADDED
     *  to the event's time for convenience. You should use the same base time during the encode process as the decode
     *  process. Typically, this will require that both systems are aware of the start time (which is provided in the ECI
     *  protocol).<br>
     *  &nbsp; 4) timeZone: The event time will be adjusted for the provided timezone. You should use the same time
     *  zone during the encode process as the decode.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; com::egi::services::mff::api::Event *: An MFF event object.<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    static EncodedEvent *encodeEvent(com::egi::services::mff::api::Event *event,
                                     bool swapBytes,
                                     uint64_t baseTime,
                                     int &timeZone);
    
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
    virtual EGIBase::ClassID getClassID(){return ECIEvent::classID;}
    
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
    virtual std::string toString() const {return EGIObject::toString() + "::ECIEvent";}
    
    //####################################
    //Class variables.
    //####################################
    
    /**
     *  Class ID
     *  Specifies the class id for instances of this class.
     */
    static const EGIBase::ClassID classID = 'ECNT';
    
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
    
private:
    
};

#endif // ECIEvent_DEFINED

