
/**@file
 *  ObservableDelegate Header File
 *  @author Robert Bell
 *  @date 01/01/2008
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  In some cases it is nice to delegate the observable/observer
 *  paradigm rather than inherit from it. This is a simple extension
 *  that does just that!
 */

#ifndef ObservableDelegate_DEFINED
#define ObservableDelegate_DEFINED

#include "EGIObject.h"
#include "Observable.h"

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/**
	 *  Observer pattern namespace.
	 */
	namespace ObserverPattern{
	
		/**
		 *  ObservableDelegate Class.
		 *  @author Robert Bell.
		 *  @remarks
		 *  In some cases it is nice to delegate the observable/observer
		 *  paradigm rather than inherit from it. This is a simple extension
		 *  that does just that!
		 *
		 *  ------<br>
		 *  Update (001): 2008-01-01: Class creation.<br>
		 *  ------<br>
		 *
         *  ------<br>
         *  Update (002): 2012-04-20: toString method now const.<br>
         *  ------<br>
		 */
		class ObservableDelegate : public Observable{
			
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
			ObservableDelegate();
			
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
			ObservableDelegate(bool threadSafe);
			
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
			ObservableDelegate(const ObservableDelegate& source);
			
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
			virtual ~ObservableDelegate();
			
			//####################################
			//End - Destructor.
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
			 *  &nbsp; ObservableDelegate& : N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			ObservableDelegate&  operator=(const ObservableDelegate& source);
			
			/**
			 *  Set changed.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) Marks this Observable object as having been changed; the Observable::hasChanged()
			 *  method will now return false.<br>
			 *  &nbsp; 2) The setChanged method is now publically accessable (this accomodates delegation).<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; void: N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			void virtual delegateSetChanged();
			
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
			virtual ClassID getClassID(){return ObservableDelegate::classID;}
			
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
			virtual std::string toString() const {return Observable::toString() + "::ObservableDelegate";}
			
			//####################################
			//Class variables.
			//####################################
			static const ClassID classID = 'OBDE';
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

#endif // ObservableDelegate_DEFINED
