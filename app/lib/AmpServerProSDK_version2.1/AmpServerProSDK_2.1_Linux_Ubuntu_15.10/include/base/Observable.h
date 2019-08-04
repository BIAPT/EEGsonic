
/**@file
 *  Observable header.
 *  @author Robert Bell
 *  @date 01/01/2008
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  This class is part of the observable/observer paradigm.
 */

#ifndef Observable_DEFINED
#define Observable_DEFINED

#include "EGIObject.h"
#include "Observer.h"

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/**
	 *  Observer pattern namespace.
	 */
	namespace ObserverPattern{
	
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
		class Observable : virtual public EGIObject{
			
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
			Observable();
			
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
			Observable(bool threadSafe);
			
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
			Observable(const Observable& source);
			
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
			virtual ~Observable();
			
			/**
			 *  Assignment.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; Observable& : N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			Observable&  operator=(const Observable& source);
			
			/**
			 *  Adds an observer to the list of observers for this object.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) The observer is not added if it is already present in the set,
			 *  or the passed in pointer is null.<br>
			 *  ------<br>
			 *  <b>Arguments: o: The oberver.</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; bool: true = success; false = failure.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual bool addObserver(Observer *o);
			
			/**
			 *  Get the number of observers in this Observable object's list of observers.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; int: The number of observers.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual int countObservers();
			
			/**
			 *  Deletes an observer from the set of observers of this object.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; bool:  true = observer found and deleted, false = not found.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual bool deleteObserver(Observer *o);
			
			/**
			 *  Clears the observer list so that this object no longer has any observers.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; bool:  true = sucess, false = failure.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual bool deleteObservers();
			
			/**
			 *  Tests if this object has changed.
			 *  <b>Notes:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; N/A<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; bool: true = has changed, false = has not changed.<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual bool hasChanged();
			
			/**
			 *  Notifies observers.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) If this object has changed, as indicated by the hasChanged method, then
			 *  notify all of its observers and then call the clearChanged method to
			 *  indicate that this object has no longer changed. Each notified observer
			 *  will be passed this object as an argument.<br>
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
			virtual void notifyObservers();
			
			/**
			 *  Notifies observers.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) If this object has changed, as indicated by the hasChanged method, then
			 *  notify all of its observers and then call the clearChanged method to
			 *  indicate that this object has no longer changed. Each notified observer
			 *  will be passed this object as an argument and the user reference.<br>
			 *  ------<br>
			 *  <b>Arguments:</b><br>
			 *  &nbsp; userRef: Passed to the observers during the update call.<br>
			 *  ------<br>
			 *  <b>Return:</b><br>
			 *  &nbsp; void: N/A<br>
			 *  ------<br>
			 *  <b>Throws:</b><br>
			 *  &nbsp; N/A<br>
			 */
			virtual void notifyObservers(EGIObject *userRef);
			
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
			virtual ClassID getClassID(){return Observable::classID;}
			
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
			virtual std::string toString() const {return EGIObject::toString() + "::Observable";}
			
			//####################################
			//Class variables.
			//####################################
			
			/**
			 *  Class ID<br>
			 *  Specifies the class ID for instances of this class.
			 */
			static const ClassID classID = 'OBLE';
			
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
			 *  Clear changed.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) Indicates that this object has no longer changed, or that it has already notified all
			 *  of its observers of its most recent change; the Observable::hasChanged() method will now
			 *  return false.<br>
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
			virtual void clearChanged();
			
			/**
			 *  Set changed.
			 *  <b>Notes:</b><br>
			 *  &nbsp; 1) Marks this Observable object as having been changed; the Observable::hasChanged()
			 *  method will now return false.<br>
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
			virtual void setChanged();
			
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
			struct ObservableImpl;
			ObservableImpl* mObservableImplRef;
			//####################################
			//End - Non-Inheritence tree variables.
			//####################################
			
		};
	}
}

#endif // Observable_DEFINED
