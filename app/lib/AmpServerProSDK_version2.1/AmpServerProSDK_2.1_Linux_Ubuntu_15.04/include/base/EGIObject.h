
/**@file
 *  EGIObject header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  The EGI object is the base of all classes.
 */


#ifndef EGIObject_DEFINED
#define EGIObject_DEFINED

#include "EGITypes.h"
#include <string>

#define RETAIN(object)		do {\
	if((object) != NULL){		\
		(object)->retain();		\
	}                           \
    } while (0)

#define RELEASE(object)		do {\
	if((object) != NULL){		\
		(object)->release();	\
		(object) = NULL;		\
    }                           \
    } while (0)

#define ASSIGN(object, toObject)    do {\
        if((object) != NULL)            \
            (object)->retain();         \
        (toObject) = (object);          \
    } while (0)

#define REPLACE(object, withObject)     do {\
	if((object) != (withObject)){           \
		if((object) != NULL)                \
			(object)->release();            \
		(object) = (withObject);            \
		if((withObject) != NULL)            \
			(withObject)->retain();         \
	}                                       \
    } while (0)

#define DETACH(object, ObjectClass)                                                     do {\
	if((object) != NULL){																	\
		ObjectClass *newObject = dynamic_cast<ObjectClass *>((object)->duplicate(true));	\
		(object)->release();																\
		(object) = newObject;																\
	}                                                                                       \
    } while (0)

// Releasing and replacing vectors of EGI objects is a common practice. The below
// macros peform those task on references to vectors that contain EGI objects.

#define RELEASE_VECTOR_REFERENCE(object, type)                  do {\
    if((object) != NULL){                                           \
        for(std::vector<type>::iterator itr = (object)->begin();    \
            itr != (object)->end();                                 \
            ++itr){                                                 \
            (*itr)->release();                                      \
        }                                                           \
        (object)->clear();                                          \
        delete (object);                                            \
        (object) = NULL;                                            \
    }                                                               \
    } while (0)

#define REPLACE_VECTOR_REFERENCE(object, withObject, type)          do {\
    if((object) != (withObject)){                                       \
        if((object) != NULL){                                           \
            for(std::vector<type>::iterator itr = (object)->begin();    \
                itr != (object)->end();                                 \
                ++itr){                                                 \
                (*itr)->release();                                      \
            }                                                           \
            (object)->clear();                                          \
            delete (object);                                            \
            (object) = NULL;                                            \
        }                                                               \
        (object) = (withObject);                                        \
    }                                                                   \
    } while (0)

// This is a generic replace of a heap allocated object that first checks
// to see if the object being replaced is equal before deleting.

#define GENERIC_HEAP_REPLACE(object, withObject)    do {\
    if((object) != (withObject)){                       \
        delete (object);                                \
        (object) = (withObject);                        \
    }                                                   \
    } while (0)

// Useful define for printing debug information.

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt, ...)                               do {\
    if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__,    \
    __LINE__, __func__, __VA_ARGS__);                           \
    } while (0)

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	/** EGIObject Class.
	 *  @author Robert Bell.
	 *  @remarks
	 *  The EGI object is the base of all classes. And this serves as the "generic" type in a
	 *  number of situations.
	 *
	 *  A guarantee is given to all objects descended from EGIObject which states: When their
	 *  destructors are called, the reference count is zero, and will remain zero for the duration
	 *  of the destructor if you follow the following usage:
     *
     *  1) You must use the retain/release model.
     *
     *  2) BEFORE transfering an object reference to another thread, you must assume that either you
     *  no longer own it, OR you must retain it for the other thread PRIOR to handing it over."
	 *
	 *  3) Do not use the instance lock/ulock methods whilst in the destructor.
	 *
	 *  ------<br>
	 *  Update (001): 2008-10-23: EGIObject now uses a separate mutex for retaining and releasing objects.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (002): 2009-05-12: Added lockMutex and unlockMutex methods.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (003): 2009-07-20: Fixed retain/release model to correctly handle stack-based objects.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (004): 2009-07-21: Begun the process of conditional exception support.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (005): 2010-05-05: Added clone, create, init, setInitalized, and getInitalized methods
	 *  to the interface. Note that the first three are declared pure virtual, and thus EGIObject is now
	 *  an abstract class.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (006): 2010-05-07: Corrected assignment and copy.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (007): 2010-05-11: Finished the process of conditional exception support.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (008): 2010-05-14: EGIObject is now not an abstract class.<br>
	 *  ------<br>
	 *
	 *  ------<br>
	 *  Update (009): 2010-05-14: Thread locking functions now throw resource lock and unlock
	 *  exceptions if exception support is on.<br>
	 *  ------<br>
     *
     *  ------<br>
     *  Update (010): 2015-07-27: Fixed the defines to work nicely in the presense
     *  things like single-line 'if' statements.<br>
     *  ------<br>
     *
     *  ------<br>
     *  Update (011): 2015-10-29: The initialized was not being set to false on object creation.<br>
     *  ------<br>
	 */
	class EGIObject{
		
	public:
		
		//####################################
		// Constructor(s).
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
		EGIObject();
		
		/**
		 *  Contructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) threadSafe: true = thread safe; false = not thread safe<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		EGIObject(bool threadSafe);
		
		/**
		 *  Copy Constructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) The memory management state (retain counts, etc.), are not
		 *  transferred during invocation of the copy constructor.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		EGIObject(const EGIObject& source);
		
		//####################################
		// End - Constructor(s).
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
		virtual ~EGIObject();
		
		//##################
		// Assignment.
		//##################
		
		/**
		 *  Assignment.
		 *  <b>Notes:</b><br>
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) The memory management state (retain counts, etc.), are not
		 *  transferred during invocation of the assignment operator.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIObject& : N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		EGIObject& operator=(const EGIObject& source);
		
		//##################
		// End - Assignment.
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
		 *  &nbsp; EGIObject *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIObject *clone() const;
		
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
		 *  &nbsp; EGIObject *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIObject *create() const;
		
		/**
		 *  Create.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Implements the virtual constructor idiom.<br>
		 *  &nbsp; 2) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) threadSafe: true = thread safe; false = not thread safe<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIObject *: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; N/A<br>
		 */
		virtual EGIObject *create(bool threadSafe) const;
		
		/**
		 *  @name Initialization interface.
		 *  &nbsp; 1) Excessive work in constructors should be avoided. The initialization
		 *  interface attempts to enforce this concept by requiring that descendants
		 *  implement an init method.<br>
		 *  &nbsp; 2) Please covarient return types when implementing
		 *  the init method in derived classes.<br>
		 *  &nbsp; 3) On failure, at least an EGIBase::Init_EGIException should be thrown
		 *  unless exceptions are not in use, otherwise return NULL.
		 */
		//@{
		
		/**
		 *  Init.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Use covariant return types in descended classes.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; eObject: Initialization object.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; 1) EGIObject *: This object.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
		 *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
		 */
		virtual EGIObject *init(EGIObject *eObject);
		
		/**
		 *  Sets the initialized state of this object.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; initialized: The initialized state.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setInitialized(bool aInitialized);
		
		/**
		 *  Gets the initialized state of this object.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: The initialized state.<br>
		 *  ------<br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 *  &nbsp; N/A<br>
		 */
		virtual bool getInitialized();
		
		//@}
		
		/**                                                                                                                                                                       
		 *  @name Memory Management.                                                                                                                                   
		 *  Memory Management.                                                                                     
		 */
		//@{
		
		/**
		 *  Retains this object.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; EGIObject *: NULL on failure.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 *  &nbsp; 2) EGIBase::Retain_EGIException: N/A<br>
		 */
		virtual EGIObject *retain();
		
		/**
		 *  Releases this object.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 *  &nbsp; 2) EGIBase::Release_EGIException: N/A<br>
		 */
		virtual bool release();
		
		/**
		 *  Auto releases this object.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; 1) Not supported at this time.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		virtual bool autoRelease();
		
		/**
		 *  Gets the reference count for this instance.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int64_t: The reference count.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual int64_t getRefCount();
		
		//@}
		
		/**                                                                                                                                                                       
		 *  @name Threading.                                                                                                                                   
		 *  Threading.                                                                                     
		 */
		//@{
		
		/**
		 *  Locks this instance's instance lock.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int: Return values are platform specific:<br>
		 *  1) Mac OS X, Unix, Linux: return values match those of pthread_mutex_lock.<br>
		 *  2) Windows: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual int lock();
		
		/**
		 *  Unlocks this instance's instance lock.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int: Return values are platform specific:<br>
		 *  1) Mac OS X, Unix, Linux: return values match those of pthread_mutex_lock.<br>
		 *  2) Windows: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual int unlock();
		
		/**
		 *  Locks given mutex.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) If lockDefault is true, then this
		 *  instance's lock method will be called.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; mutex: The mutex to lock.<br>
		 *  &nbsp; useDefault: Whether to use default mutex (see note above).<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int: Return values are platform specific:<br>
		 *  1) Mac OS X, Unix, Linux: return values match those of pthread_mutex_lock.<br>
		 *  2) Windows: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual int lockMutex(void *mutex, bool useDefault);
		
		/**
		 *  Unlocks given mutex.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) If lockDefault is true, then this
		 *  instance's unlock method will be called.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; mutex: The mutex to unlock.<br>
		 *  &nbsp; useDefault: Whether to use default mutex (see note above).<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; int: return values are platform specific:<br>
		 *  1) Mac OS X, Unix, Linux: return values match those of pthread_mutex_lock.<br>
		 *  2) Windows: N/A<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual int unlockMutex(void *mutex, bool useDefault);
		
		//@}
		
		/**
		 *  Sets debug state.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; debug: true = on, false = off<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool setDebug(bool debug);
		
		/**
		 *  Gets debug state.
		 *  <b>Notes:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: The current debug state.<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::NULL_EGIException.<br>
		 */
		virtual bool getDebug();
		
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
		virtual ClassID getClassID(){return EGIObject::classID;}
		
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
		virtual std::string toString() const {return "EGIObject";}
		
		/**                                                                                                                                                                       
		 *  @name Memory Management.
		 *  Memory Management.
		 */
		//@{
		
		/**
		 *  Empties the auto release pool for the caller's thread.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) Not supported at this time.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; bool: true = success, false = failure<br>
		 *  ------<br>
		 *  <b>Throws:</b><br>
		 *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
		 */
		static bool emptyAutoReleasePool();
		
		//@}
		
		//####################################
		//Class variables.
		//####################################
		
		/**
		 *  Class ID<br>.
		 *  Specifies the class ID for instances of this class.
		 */
		static const ClassID classID = 'EGIO';
				
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
		struct EGIObjectImpl;
		EGIObjectImpl* mEGIObjectImplRef;
		//####################################
		//End - Non-Inheritence tree variables.
		//####################################
		
	};	
}

#endif // EGIObject_DEFINED
