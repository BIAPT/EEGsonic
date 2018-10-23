
/**@file
 *  EGIRunLoop header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2007 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef EGIRunLoop_DEFINED
#define EGIRunLoop_DEFINED

#include "EGIObject.h"
#include <pthread.h>

/**
 *  EGIBase namespace.
 */
namespace EGIBase{

	class EGITask;

	/**
	 *  EGIRunLoop Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  RunLoop class.
	 *
	 *  ------<br>
	 *  Update (001): 2008-10-22: Added non-locking versions of deleteTask and deleteTasks. This fixes a locking issue
	 *  when release is call on a runloop.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (002): 2008-10-23: Added default runloop delay as a class constant.
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (003): 2008-10-23: The run loop's internal thread now retains the run loop at start, and releases
	 *  it when stopped. This will mean that all users of EGIRunLoop MUST remember to stop the run loop if they
	 *  started it. Include comments in the usage section above (when that section is created).<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (004): 2010-05-07: Updated comments.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (005): 2010-05-07: Fixed copy, assignment, clone and create.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (006): 2010-05-14: Updated exception support.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (007): 2012-04-20: toString method now const.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (008): 2013-07-26: Added the "size_t getNumberOfTasksOnRunLoop()" method.<br>
	 *  ------<br>
     *
     *  ------<br>
	 *  Update (009): 2013-10-13: Added thread detach call to signal system to clean thread resources after exit.<br>
	 *  ------<br>
	 */
	class EGIRunLoop : virtual public EGIObject{
		
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
		EGIRunLoop();
		
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
		EGIRunLoop(bool threadSafe, bool deleteLock);
		
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
		virtual ~EGIRunLoop();
		
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
		 *  &nbsp; EGIRunLoop *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIRunLoop *clone() const;
		
		/**
		 *  Create.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Implements the virtual constructor idiom.<br>
		 *  &nbsp; 2) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIRunLoop *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIRunLoop *create() const;
		
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
		 *  &nbsp; EGIRunLoop *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIRunLoop *create(bool threadSafe, bool deleteLock) const;
		
		/**
		 *  Init.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) eObject: Initialization object.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIRunLoop *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIRunLoop *init(EGIObject *eObject);
		
		/**
		 *  Sets the runloop delay in microseconds.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) microseconds: The runloop delay.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setRunLoopDelay(uint64_t microseconds);
		
		/**
		 *  Gets the runloop delay in microseconds.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int64_t : The runloop delay in microseconds.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual int64_t getRunLoopDelay();
		
		/**
		 *  Starts the runloop.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; pthread_t *: The runloop's thread ID.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual pthread_t *startRunLoop();
		
		/**
		 *  Stops the runloop.
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
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool stopRunLoop();
		
		/**
		 *  Adds an EGITask to the runloop.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) The task is not added if it is already present in the set,
		 *  or the passed in pointer is null.<br>
		 *  ------<br>
		 *  <b>Arguments: task: The task.</b><br>
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
		virtual bool addTask(EGITask *task);
		
		/**
		 *  Deletes an EGITask from the runloop.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool:  true = task found and deleted, false = not found.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool deleteTask(EGITask *task);
		
		/**
		 *  Deletes all tasks.
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
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool deleteTasks();
        
        /**
		 *  Gets the number of tasks on the runloop.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Please remember that on return from this method, the
         *  value might have changed if another thread adds a task.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; size_t: The number of tasks on the runloop.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::ResourceLock_EGIException.<br>
		 *  &nbsp; 2) EGIBase::ResourceUnlock_EGIException.<br>
		 *  &nbsp; 3) EGIBase::NULL_EGIException.<br>
		 */
        virtual size_t getNumberOfTasksOnRunLoop();
		
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
		virtual ClassID getClassID(){return EGIRunLoop::classID;}
		
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
		virtual std::string toString() const {return EGIObject::toString() + "::EGIRunLoop";}
		
		//####################################
		//Class variables.
		//####################################
		
		/**
		 *  Class ID<br>
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'EGOP';
		
		/**
		 *  Run loop delay defaults to 1 second.
		 */
		static const int64_t kDefaultRunLoopDelay = 1000000;
		
		//####################################
		//End - Class variables.
		//####################################
		
		//####################################
		//Class methods.
		//####################################
		//####################################
		//End - Class methods.
		//####################################
		
		/**
		 *  A forward declaration supporting internal implementation.
		 *  For implementation reasons, this forward declaration is public.
		 */
		struct EGIRunLoopImpl;
		
		
	protected:
		
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
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		EGIRunLoop(const EGIRunLoop& source);
		
		//####################################
		// End - Constructor(s).
		//####################################
		
		
		//####################################
		// Assignment.
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
		 *  &nbsp; EGIRunLoop& : N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		EGIRunLoop& operator=(const EGIRunLoop& source);
		
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
		EGIRunLoopImpl* mEGIRunLoopImplRef;
		//####################################
		//End - Non-Inheritence tree variables.
		//####################################
		
	};
}

#endif // EGIRunLoop_DEFINED
