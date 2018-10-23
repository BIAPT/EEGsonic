
/**@file
 *  TinyXMLWrappers header.
 *  @author Robert Bell
 *  @date 10/05/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef TinyXMLWrappers_DEFINED
#define TinyXMLWrappers_DEFINED

#include "EGIObject.h"
#include "EGIExceptions.h"

#include "XMLResource.h"

class TiXmlNode;
class TiXmlElement;

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
				 *  util namespace.
				 */
				namespace util{
					
					/**
					 *  TinyXMLWrappers Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-05-10: Class creation.<br>
					 *  ------<br>
                     *
                     *  ------<br>
					 *  Update: 2012-01-28: Added nicer wrappers to shorten calls in the XML layer.<br>
					 *  ------<br>
					 */
					class TinyXMLWrappers : virtual public EGIBase::EGIObject{
						
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
						TinyXMLWrappers();
						
						/**
						 *  Contructor.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; threadSafe: true = thread safe; false = not thread safe<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						TinyXMLWrappers(bool threadSafe);
						
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
						virtual ~TinyXMLWrappers();
						
						//####################################
						//End - Destructor.
						//####################################
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) TinyXMLWrappers *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual TinyXMLWrappers *init(EGIObject *eObject);
						
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
						virtual EGIBase::ClassID getClassID(){return TinyXMLWrappers::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::TinyXMLWrappers";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'XMCE';
						
						//####################################
						//End - Class variables.
						//####################################
						
						//####################################
						//Class methods.
						//####################################
                        
                        static std::string getText(TiXmlElement *element);
                        
                        static std::string getAttribute(TiXmlElement *element, const char *name);
                        
                        static TiXmlElement *getTiXmlElementWithCStringNameAndCStringText(const char *name,
                                                                                          const char *text,
                                                                                          bool alwaysCreate);
                        
                        static TiXmlElement *getTiXmlElementWithXStringNameAndXStringText(EGIBase::EGIXStringWrap name,
                                                                                          EGIBase::EGIXStringWrap text,
                                                                                          bool alwaysCreate);
                        
                        static TiXmlElement *getTiXmlElementWithCStringNameAndText(const char *name,
                                                                                   std::string text,
                                                                                   bool alwaysCreate);
                        
                        static TiXmlElement *getTiXmlElementWithNameAndCStringText(std::string name,
                                                                                   const char *text,
                                                                                   bool alwaysCreate);
                        
                        static TiXmlElement *getTiXmlElementWithNameAndText(std::string name, 
                                                                            std::string text,
                                                                            bool alwaysCreate);
                        
                        static TiXmlElement *setAttributeOnElementWithCStringNameAndCStringName(TiXmlElement *element,
                                                                                                const char *name,
                                                                                                const char *value,
                                                                                                bool alwaysCreate);
                        
                        static TiXmlElement *setAttributeOnElementWithXStringNameAndXStringName(TiXmlElement *element,
                                                                                                EGIBase::EGIXStringWrap name,
                                                                                                EGIBase::EGIXStringWrap value,
                                                                                                bool alwaysCreate);
                        
                        static TiXmlElement *setAttributeOnElementWithCStringNameAndValue(TiXmlElement *element,
                                                                                          const char *name,
                                                                                          std::string value,
                                                                                          bool alwaysCreate);
                        
                        static TiXmlElement *setAttributeOnElementWithNameAndCStringValue(TiXmlElement *element,
                                                                                          std::string name,
                                                                                          const char *value,
                                                                                          bool alwaysCreate);
                        
                        static TiXmlElement *setAttributeOnElementWithNameAndValue(TiXmlElement *element,
                                                                                   std::string name,
                                                                                   std::string value,
                                                                                   bool alwaysCreate);
                        
                        static TiXmlNode *linkChildToParent(TiXmlElement *parent, TiXmlElement *child);
                        
                        static TiXmlNode *linkChildToParentWithChildNameAndText(TiXmlElement *parent,
                                                                                  EGIBase::EGIXStringWrap name,
                                                                                  EGIBase::EGIXStringWrap text,
                                                                                  bool alwaysCreate);
                        
                        static TiXmlNode *linkChildToParentWithChildAndAttribute(TiXmlElement *parent,
                                                                                 EGIBase::EGIXStringWrap childName,
                                                                                 EGIBase::EGIXStringWrap childText,
                                                                                 bool alwaysCreateChild,
                                                                                 EGIBase::EGIXStringWrap attributeName,
                                                                                 EGIBase::EGIXStringWrap attributeValue,
                                                                                 bool alwaysCreateAttribute);
                        
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
						TinyXMLWrappers(const TinyXMLWrappers& source);
						
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
						TinyXMLWrappers&  operator=(const TinyXMLWrappers& source);
						
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

#endif // TinyXMLWrappers_DEFINED
