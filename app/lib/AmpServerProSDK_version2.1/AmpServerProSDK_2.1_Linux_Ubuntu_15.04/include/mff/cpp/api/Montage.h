
/**@file
 *  Montage header.
 *  @author Robert Bell
 *  @date 15/07/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef Montage_DEFINED
#define Montage_DEFINED

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
				 * api namespace.
				 */
				namespace api{
					
					class Sensor;
					
					/**
					 *  Montage Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2012-07-15: Class creation.<br>
					 *  ------<br>
					 */
					class Montage : virtual public com::egi::services::mff::api::MFFResource{
						
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
						Montage();
						
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
						Montage(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType);
						
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
						virtual ~Montage();
						
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
						 *  &nbsp; Montage *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Montage *clone() const;
						
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
						 *  &nbsp; Montage *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Montage *create() const;
						
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
						 *  &nbsp; Montage *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual Montage *create(std::string uri, EGIObject *resourceDelegate, MFFResourceType *resourceType) const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) Montage *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual Montage *init(EGIObject *eObject);
						
						/**
						 *  Sets the name for this sensor layout.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) name: The Montage name.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setName(EGIBase::EGIXStringWrap name);
						
						/**
						 *  Gets the name for this sensor layout.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The sensor layout name.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getName() const;
                        
                        /**
						 *  Sets the parent layout for this montage.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) parentLayout: The parent layout for this montage.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setParentLayout(EGIBase::EGIXStringWrap parentLayout);
						
						/**
						 *  Gets the parent layout for this montage.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) const std::string *: The parent layout for this montage.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual const std::string *getParentLayout() const;
						
						/**
						 *  Sets the montage sensors.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) sensors: The montage sensors.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setSensors(std::vector<Sensor *> *sensors);
						
						/**
						 *  Gets the montage sensors.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) std::vector<Sensor *>: The montage sensors.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual std::vector<Sensor *> *getSensors() const;
						
						/**
						 *  Sets the vertex reference flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) vertexReference: The vertex reference flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setVertexReference(bool vertexReference);
						
						/**
						 *  Gets the vertex reference flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) bool: The vertex reference flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getVertexReference() const;
                        
                        /**
						 *  Sets the average reference flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) averageReference: The average reference flag.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual void setAverageReference(bool averageReference);
						
						/**
						 *  Gets the average reference flag.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp;  1) bool: The average reference flag.<br>
						 *  ------<br>
						 *  <b>Throws</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual bool getAverageReference() const;
						
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
						virtual EGIBase::ClassID getClassID(){return Montage::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::Montage";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'MOGE';
						
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
                         *  The sensor layout name.
                         *  <b>Notes:</b><br>
                         *  &nbsp; N/A<br>
                         **/
                        std::string *name_;
                        
                        /**
                         *  The parent layout name.
                         *  <b>Notes:</b><br>
                         *  &nbsp; N/A<br>
                         **/
                        std::string *parentLayout_;
                        
                        /**
                         *  Vertex reference flag.
                         *  <b>Notes:</b><br>
                         *  &nbsp; N/A<br>
                         **/
                        bool vertexReference_;
                        
                        /**
                         *  Average reference flag.
                         *  <b>Notes:</b><br>
                         *  &nbsp; N/A<br>
                         **/
                        bool averageReference_;
                        
                        /**
                         *  The sensor list for this sensor layout.
                         *  <b>Notes:</b><br>
                         *  &nbsp; N/A<br>
                         **/
						std::vector<Sensor *> *sensors_;
                        
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
						Montage(const Montage& source);
						
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
						Montage&  operator=(const Montage& source);
						
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

#endif // Montage_DEFINED

