
/**@file
 *  MFFResourceType header.
 *  @author Robert Bell
 *  @date 15/08/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef MFFResourceType_DEFINED
#define MFFResourceType_DEFINED

#include "EGIObject.h"
#include "EGIException.h"

#include <string>

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
					
					/**
					 *  MFFResourceType Class.
					 *  @author Robert Bell.
					 *  @remarks
					 *  Place notes here.
					 *
					 *  ------<br>
					 *  Update: 2011-08-15: Class creation.<br>
					 *  ------<br>
					 */
					class MFFResourceType : virtual public EGIBase::EGIObject{
						
					public:
                        
                        /**
                         *
                         * Resource types for files in MFF.
                         *
                         */
                        typedef enum{
                            
                            //######
                            // Resource types for files in MFF.
                            //######
                            
                            // We don't understand the resource.
                            kMFF_RT_Unknown         = -1,
                            
                            kMFF_RT_Any             = 0,
                            kMFF_RT_MFFFile         = 1,
                            kMFF_RT_Signal          = 2,
                            kMFF_RT_EventTrack      = 3,
                            kMFF_RT_Epochs          = 4,
                            kMFF_RT_Subject         = 5,
                            kMFF_RT_History         = 6,
                            kMFF_RT_Info            = 7,
                            kMFF_RT_InfoN           = 8,
                            kMFF_RT_Categories      = 9,
                            kMFF_RT_JTFCategories   = 10,
                            kMFF_RT_SensorLayout    = 11,
                            kMFF_RT_Coordinates     = 12,
                            kMFF_RT_Photogrammetry  = 13,
                            kMFF_RT_PNSSet          = 14,
                            kMFF_RT_MovieSyncs      = 15,
                            kMFF_RT_Fields          = 16,
                            kMFF_RT_Notes           = 17,
                            kMFF_RT_Montage         = 18,
							kMFF_RT_DipoleSet		= 19,
							kMFF_RT_PhoticStim
                            
                        } _MFFResourceType;
                        
                        class MFFResourceTypeInitInfo : public EGIObject{
                        public:
                            MFFResourceTypeInitInfo(_MFFResourceType resourceType) : EGIObject(false){
                                this->resourceType_ = resourceType;
                            }
                            
                            void setResourceType(_MFFResourceType resourceType){this->resourceType_ = resourceType;}
                            _MFFResourceType getResourceType(){return this->resourceType_;}
                            
                        private:
                            _MFFResourceType resourceType_;
                        };
						
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
						MFFResourceType();
                        
                        /**
						 *  Contructor.
						 *  <b>Notes:</b><br>
						 *  &nbsp; Thread safety is off.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) resourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						MFFResourceType(_MFFResourceType resourceType);
						
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
						virtual ~MFFResourceType();
						
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
						 *  &nbsp; MFFResourceType *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFResourceType *clone() const;
						
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
						 *  &nbsp; MFFResourceType *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFResourceType *create() const;
						
						/**
						 *  Create.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Implements the virtual constructor idiom.<br>
						 *  &nbsp; 2) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) resourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; MFFResourceType *: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; N/A<br>
						 */
						virtual MFFResourceType *create(_MFFResourceType resourceType) const;
						
						/**
						 *  Init.
						 *  <b>Notes:</b><br>
						 *  &nbsp; 1) Use covariant return types in descended classes.<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; eObject: Initialization object.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) MFFResourceType *: This object.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
						 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
						 */
						virtual MFFResourceType *init(EGIObject *eObject);
                        
                        /**
						 *  Sets the MFF resource type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; 1) resourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; void: N/A<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: Indicates that the file could not be
						 *  loaded for some reason.<br>
						 */
						virtual void setResourceType(_MFFResourceType resourceType);
                        
                        /**
						 *  Gets the MFF resource type.
						 *  <b>Notes:</b><br>
						 *  &nbsp; N/A<br>
						 *  ------<br>
						 *  <b>Arguments:</b><br>
						 *  &nbsp; N/A.<br>
						 *  ------<br>
						 *  <b>Return:</b><br>
						 *  &nbsp; 1) _MFFResourceType: The resource type.<br>
						 *  ------<br>
						 *  <b>Throws:</b><br>
						 *  &nbsp; 1) MFF::File_MFFException: Indicates that the file could not be
						 *  loaded for some reason.<br>
						 */
						virtual _MFFResourceType getResourceType();
						
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
						virtual EGIBase::ClassID getClassID(){return MFFResourceType::classID;}
						
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
						virtual std::string toString() const {return EGIObject::toString() + "::MFFResourceType";}
						
						//####################################
						//Class variables.
						//####################################
						
						/**
						 *  Class ID
						 *  Specifies the class id for instances of this class.
						 */
						static const EGIBase::ClassID classID = 'MFPE';
						
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
						
						_MFFResourceType resourceType_;
						
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
						MFFResourceType(const MFFResourceType& source);
						
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
						MFFResourceType&  operator=(const MFFResourceType& source);
						
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

#endif // MFFResourceType_DEFINED

