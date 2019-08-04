
/**@file
 *  Observer header.
 *  @author Robert Bell
 *  @date 01/01/2008
 *  @remarks
 *  Copyright 2008 EGI. All rights reserved.<br>
 *  This class is part of the observable/observer paradigm.
 */


#ifndef Observer_DEFINED
#define Observer_DEFINED

#include "EGIObject.h"

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/**
	 *  Observer pattern namespace.
	 */
	namespace ObserverPattern{
	
		//Some forward declarations.
		class Observable;
		
		/**
		 *  Observer Class.
		 *  @author Robert Bell.
		 *  @remarks
		 *  This class is part of the observable/observer paradigm.
		 *
		 *  ------<br>
		 *  Update (001): 2008-01-01: Class creation.<br>
		 *  ------<br>
		 *
         *  ------<br>
         *  Update (002): 2012-04-20: toString method now const.<br>
         *  ------<br>
		 */
		class Observer : virtual public EGIObject{
			
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
			Observer();
			
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
			Observer(bool threadSafe);
			
			/**
			 *  Copy Constructor.
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
			Observer(const Observer& source);
			
			//####################################
			//End - Constructor(s).
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
			virtual ~Observer();
			
			//##################
			//End - Copy constructor.
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
			 *  &nbsp; Observer& : N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			Observer&  operator=(const Observer& source);
			
			/**
			 *  The update method.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) This method is called when the object being observed calls its notify method.<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; observable: The observable object calling this method.<br>
			 *  &nbsp; eObject: The optional user reference passed to the observable object.<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; void: N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual void update(Observable *observable, EGIObject *eObject) = 0;
			
			/**
			 *  Gets the class ID for this class.
			 *  <b>Notes:</b><br>
			 *  &nbsp; This method should always be overridden
			 *  in derived classes, and instances should return CLASS_NAME::classID. This allows
			 *  for identification of objects in the runtime environment.<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; ClassID: The class ID.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual ClassID getClassID(){return Observer::classID;}
			
			/**
			 *  The toString method.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; std::string: String representation of this instance.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual std::string toString() const {return EGIObject::toString() + "::Observer";}
			
			//####################################
			//Class variables.
			//####################################
			static const ClassID classID = 'OBER';
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
			
			//####################################
			//Inheritence tree variables.
			//####################################
			//####################################
			//End - Inheritence tree variables.
			//####################################
			
		private:
			
			//####################################
			//Non-Inheritence tree variables.
			//####################################
			//####################################
			//End - Non-Inheritence tree variables.
			//####################################
			
		};
	}
}

#endif // Observer_DEFINED
