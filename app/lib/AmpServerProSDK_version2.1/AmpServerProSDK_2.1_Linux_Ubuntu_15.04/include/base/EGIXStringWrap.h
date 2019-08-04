
/**@file
 *  EGIXStringWrap header.
 *  @author Robert Bell
 *  @date 30/10/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef EGIXStringWrap_DEFINED
#define EGIXStringWrap_DEFINED

#include "EGIObject.h"
#include <string>

#define XSW_NULL static_cast<std::string *>(NULL)

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
    
    /**
     *  EGIXStringWrap Class.
     *  @author Robert Bell.
     *  @remarks
     *  The purpose of this class to to circumvent the inability to have
     *  have std::string * built from a char *. It is nice for classes
     *  that have C++-style string pointers, but want to be able to pass character
     *  strings as arguments. Keeping an interal std::string * means that it is
     *  easy to tell if the string was not set (or to reset it).<br>
     *
     *  ------<br>
     *  Update: 2011-10-30: Class creation.<br>
     *  ------<br>
     *
     *  ------<br>
     *  Update: 2012-12-14: Added getStringObject method.<br>
     *  ------<br>
     */
    class EGIXStringWrap : virtual public EGIBase::EGIObject{
        
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
        EGIXStringWrap();
        
        /**
         *  Contructor.
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
        EGIXStringWrap(const char *inString);
        
        /**
         *  Contructor.
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
        EGIXStringWrap(const std::string *inString);
        
        /**
         *  Contructor.
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
        EGIXStringWrap(std::string inString);
        
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
        EGIXStringWrap(const EGIXStringWrap& source);
                
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
        virtual ~EGIXStringWrap();
        
        //####################################
        //End - Destructor.
        //####################################
        
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
        EGIXStringWrap&  operator=(const EGIXStringWrap& source);
        
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
        EGIXStringWrap&  operator=(const char *inString);
        
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
        EGIXStringWrap&  operator=(const std::string *inString);
        
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
        EGIXStringWrap&  operator=(const std::string inString);
        
        //##################
        //End - Assignment.
        //##################
        
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
         *  &nbsp; EGIXStringWrap *: N/A<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual EGIXStringWrap *clone() const;
        
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
         *  &nbsp; EGIXStringWrap *: N/A<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual EGIXStringWrap *create() const;
        
        /**
         *  Create.
         *  <b>Notes:</b><br>
         *  &nbsp; 1) Implements the virtual constructor idiom.<br>
         *  &nbsp; 2) Use covariant return types in descended classes.<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; inString: The string.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; EGIXStringWrap *: N/A<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual EGIXStringWrap *create(const char *inString) const;
        
        /**
         *  Create.
         *  <b>Notes:</b><br>
         *  &nbsp; 1) Implements the virtual constructor idiom.<br>
         *  &nbsp; 2) Use covariant return types in descended classes.<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; inString: The string.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; EGIXStringWrap *: N/A<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual EGIXStringWrap *create(const std::string *inString) const;
        
        /**
         *  Create.
         *  <b>Notes:</b><br>
         *  &nbsp; 1) Implements the virtual constructor idiom.<br>
         *  &nbsp; 2) Use covariant return types in descended classes.<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; inString: The string.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; EGIXStringWrap *: N/A<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual EGIXStringWrap *create(std::string inString) const;
        
        /**
         *  Init.
         *  <b>Notes:</b><br>
         *  &nbsp; 1) Use covariant return types in descended classes.<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; eObject: Initialization object.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; 1) EGIXStringWrap *: This object.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
         *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
         */
        virtual EGIXStringWrap *init(EGIObject *eObject);
        
        /**
         *  Gets the string.
         *  <b>Notes:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; 1) inString: The string.<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; std::string *: The string.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual void setString(const std::string *inString);
        
        /**
         *  Gets the string as a pointer to an std::string.
         *  <b>Notes:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; const std::string *: The string.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual const std::string *getString();
        
        /**
         *  Gets a copy of the string.
         *  <b>Notes:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; std::string *: The string. Callee owned.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual std::string *getStringCopy();
        
        /**
         *  Gets the string as an object.
         *  <b>Notes:</b><br>
         *  &nbsp; 1) If there is no internal string, an expection is thrown.<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; std::string: The string.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
         */
        virtual std::string getStringObject();
        
        /**
         *  Gets the string as a pointer to an c-style string.
         *  <b>Notes:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Arguments:</b><br>
         *  &nbsp; N/A<br>
         *  ------<br>
         *  <b>Return:</b><br>
         *  &nbsp; const char *: The string.<br>
         *  ------<br>
         *  <b>Throws:</b><br>
         *  &nbsp; N/A<br>
         */
        virtual const char *getCString();
        
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
        virtual EGIBase::ClassID getClassID(){return EGIXStringWrap::classID;}
        
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
        virtual std::string toString() const {return EGIObject::toString() + "::EGIXStringWrap";}
        
        //####################################
        //Class variables.
        //####################################
        
        /**
         *  Class ID
         *  Specifies the class id for instances of this class.
         */
        static const EGIBase::ClassID classID = 'XSAP';
        
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
        
        std::string *theString_;
        
    private:
        
    };
}

#endif // EGIXStringWrap_DEFINED

