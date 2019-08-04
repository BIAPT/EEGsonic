
/**@file
 *  EGITask header.
 *  @author Robert Bell
 *  @date 01/01/2008
 *  @remarks
 *  Copyright 2008 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef EGITask_DEFINED
#define EGITask_DEFINED

#include "EGIObject.h"

//namespace EGIBase{
//	namespace ObserverPattern{
//		class ObservableDelegate;
//		class Observer;
//	}
//}

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	namespace ObserverPattern{
		class ObservableDelegate;
		class Observer;
	}

	/**
	 *  EGITask Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  A task class.
	 *  Each task wraps a "job". This is an abstract class. Subclasses should implement
	 *  the performTask method.
	 *
	 *  ------<br>
	 *  Update (001): 2008-01-01: Class creation.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (002): 2010-03-29: Updated to include observer/observable functionality.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (003): 2010-05-14: Updated comments.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (004): 2010-05-14: Fixed copy, assignment, clone and create.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (005): 2010-05-14: Updated exception support.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (006): 2012-04-20: toString method now const.<br>
	 *  ------<br>
	 */
	class EGITask : virtual public EGIObject{
		
	public:
        
        /**
		 *  A typed enum representing task status.
		 */
		typedef enum{
			UNKNOWN,				/**< Task status unknown */
			WAITING,				/**< Task is waiting */
			RUNNING,				/**< Task is running */
			PENDING_CANCEL,			/**< Task has a pending cancel */
			RETURNED_WITH_ERROR,	/**< Task returned with error */
			RETURNED_SUCCESSFULLY,	/**< Task returned without error */
			RETURNED_CANCELED		/**< Task cancelled */
		}TaskStatus;
        
		//####################################
		//Constructor(s).
		//#################################### 	
		
		/**
		 *  Default contructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Thread safety is off.<br>
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
		EGITask();
		
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
		EGITask(bool threadSafe);
		
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
		EGITask(const EGITask& source);
		
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
		virtual ~EGITask();
		
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
		 *  &nbsp; EGIObject& : N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		EGITask&  operator=(const EGITask& source);
		
		/**
		 *  Init.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) eObject: Initialization object.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGITask *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGITask *init(EGIObject *eObject);
		
		/**
		 *  The perform task method.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This method is called by the task scheduler.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; taskScheduler: The task scheduler object calling this method.<br>
		 *  &nbsp; eObject: Optional user reference.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual void performTask(EGIObject *taskScheduler, EGIObject *eObject) = 0;
		
		/**
		 *  Get's the task's current status.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGITask::TaskStatus: The task's status.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual EGITask::TaskStatus getStatus();
		
		/**                                                                                                                                                                       
		 *  @name Observers.                                                                                                                                   
		 *  This interface provides observer functionality to a task. The exact
		 *  manner in which observers are dealt with is up to the observable
		 *  delegate supplied.
		 */
		//@{
		
		/**
		 *  Sets the observable delegate.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This sets the observable delegate this task uses to inform
		 *  observers.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; observableDelegate: The observable delegate (retained).<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool:  true = sucess, false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setObservableDelegate(ObserverPattern::ObservableDelegate *observableDelegate);
		
		/**
		 *  Adds an observer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This call is does nothing if no observable delegate is present.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; observer: The observer.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool:  true = sucess, false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool addObserver(ObserverPattern::Observer *observer);
		
		/**
		 *  Deletes an observer.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This call is does nothing if no observable delegate is present.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; observer: The observer.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool:  true = sucess, false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool deleteObserver(ObserverPattern::Observer *observer);
		
		/**
		 *  Deletes all observers.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This call is does nothing if no observable delegate is present.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool:  true = sucess, false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool deleteObservers();
		
		//@}
		
		/**                                                                                                                                                                       
		 *  @name Queue Scheduling.                                                                                                                                   
		 *  Task's can be single entities requiring no queue interaction, or they
		 *  can be placed into task queues. EGIRunLoop is an example of a task queue,
		 *  and uses the task schueduling interface extensively.                                                                                     
		 */
		//@{
		
		/**
		 *  Sets the repeat state of this task.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This is intended primarily for task in a task queue. Tasks in such a queue will not
		 *  be removed from the queue after a call to performTask if there repeat status is set to true,
		 *  otherwise they will be.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; repeatStatus: The task scheduler object calling this method.<br>
		 *  &nbsp; eObject: Optional user reference.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; void: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setRepeats(bool repeat);
		
		/**
		 *  Gets the repeat state of this task.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: Repeat state.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool getRepeats();
		
		/**
		 *  Sets the interval for this task.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; interval: Repeat interval is in microseconds.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success; false = fail.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setInterval(int64_t interval);
		
		/**
		 *  Gets the interval for this task.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int64_t: Repeat interval is in microseconds.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual int64_t getInterval();
		
		/**
		 *  Resets this task's queue scheduling.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Calling this method will cause the task's remaining queue
		 *  time to be reset to its repeat interview. If the overflow flag
		 *  is set, time already spent in the queue is taken into account. For
		 *  example, suppose the repeat interval is 1000us and the task has been
		 *  in the queue for 2450us (i.e., the queue was delayed), then the task
		 *  will keep returning true from bool EGITask::getTaskReady() until it
		 *  has been run enough times by the task scheduler to "catch up". In
		 *  our example, consider the following sequence (assume all called in
		 *  less than 1us):<br>
		 *  &nbsp; (-1450us) - (or 2450us - 1000us)<br>
		 *  &nbsp; EGITask::getTaskReady() - returns true<br>
		 *  &nbsp; EGITask::performTask(...)<br>
		 *  &nbsp; EGITask::resetQueueTime(true)<br>
		 *  &nbsp; (-450us)<br>
		 *  &nbsp; EGITask::getTaskReady() - returns true<br>
		 *  &nbsp; EGITask::performTask(...)<br>
		 *  &nbsp; EGITask::resetQueueTime(true)<br>
		 *  &nbsp; (650us)<br>
		 *  &nbsp; EGITask::getTaskReady() - returns false (and will do for 650us)<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success; false = fail.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool resetQueueTime(bool overflow);
		
		/**
		 *  Refreshes this task's queue time.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This should be called before EGITask::getTaskReady() so
		 *  that EGITask::getTaskReady() will correctly identify whether the
		 *  task is ready to be run.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success; false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool refreshQueueTime();
		
		/**
		 *  Gets this task's ready state.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) This task is ready for EGITask::performTask(...) to be
		 *  called.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: The task's ready state.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool getTaskReady();
		
		//@}
		
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
		virtual ClassID getClassID(){return EGITask::classID;}
		
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
		virtual std::string toString() const {return EGIObject::toString() + "::EGITask";}
		
		//####################################
		//Class variables.
		//####################################
		
		/**
		 *  Class ID<br><br>
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'EGSK';
		
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
		 *  Set's the task's current status.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) status: The task's status.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
         *  &nbsp; bool: true = success; false = failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setStatus(EGITask::TaskStatus status);
		
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
		struct EGITaskImpl;
		EGITaskImpl *mEGITaskImplRef;
		//####################################
		//End - Non-Inheritence tree variables.
		//####################################
		
	};
}

#endif // EGITask_DEFINED
