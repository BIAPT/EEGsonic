
/**@file
 *  ECICommandDelegate header.
 *  @author Robert Bell
 *  @date 31/07/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef ECICommandDelegate_DEFINED
#define ECICommandDelegate_DEFINED

#include "EGIObject.h"
#include "AS_TCP_PortHandlerDelegate.h"

// Forward defines for the MFF.

@class ECIServerController;

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
 *  ECICommandDelegate Class.
 *  @author Robert Bell.
 *  @remarks
 *  Place notes here.
 *
 *  ------<br>
 *  Update (001): 2012-07-31: Class creation.<br>
 *  ------<br>
 */
class ECICommandDelegate : virtual public AS_TCP_PortHandlerDelegate{
    
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
    ECICommandDelegate();
    
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
    ECICommandDelegate(const ECICommandDelegate& source);
    
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
    ECICommandDelegate&  operator=(const ECICommandDelegate& source);
    
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
    virtual ~ECICommandDelegate();
    
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
     *  &nbsp; ECICommandDelegate *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ECICommandDelegate *clone() const;
    
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
     *  &nbsp; ECICommandDelegate *: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual ECICommandDelegate *create() const;
    
    /**
     *  Init.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Use covariant return types in descended classes.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; eObject: Initialization object.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; 1) ECICommandDelegate *: This object.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
     *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
     */
    virtual ECICommandDelegate *init(EGIObject *eObject);
    
    /**
     *  Data received. This is called when the port handler receives data.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; trans: the transaction packet.<br>
     *  &nbsp; userRef: user ref.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void *: N/A.<br>
     */
    virtual void *receive(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef);
    
    /**
     *  Data send. This is called when the port handler sends data.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; trans: the transaction packet.<br>
     *  &nbsp; userRef: user ref.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void *: N/A.<br>
     */	
    virtual void *send(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef);
    
    /**
     *  Connection error. Called when the port handler encounters a connection error.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; trans: the transaction packet.<br>
     *  &nbsp; userRef: user ref.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A.<br>
     */
    virtual void connnectionError(AS_TCP_PortHandler::ConnectionError error, void *userRef);
    
    /**
     *  Log a message on the main thread.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; message: Message to be logged.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A.<br>
     */
    void setController(ECIServerController *controller) { controller_ = controller;};
    
    /**
     *  Log a message on the main thread.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; message: Message to be logged.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A.<br>
     */
    void log(std::string message) const ;
    
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
    virtual EGIBase::ClassID getClassID(){return ECICommandDelegate::classID;}
    
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
    virtual std::string toString() const {return AS_TCP_PortHandlerDelegate::toString() + "::ECICommandDelegate";}
    
    //####################################
    //Class variables.
    //####################################
    
    /**
     *  Class ID
     *  Specifies the class id for instances of this class.
     */
    static const EGIBase::ClassID classID = 'ECTE';
    
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
    
    /**
     *  Controller
     *  Provides access to the controller class to log messages.
     */
    ECIServerController *controller_;
    
};

#endif // ECICommandDelegate_DEFINED

