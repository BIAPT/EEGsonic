
/**@file
 *  EGIBase header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2007 EGI. All rights reserved.<br>
 *  Base header file for all EGIBase functionality.
 */

#ifndef EGIBase_DEFINED
#define EGIBase_DEFINED

#include "EGITypes.h"
#include "EGIObject.h"
#include "Observable.h"
#include "ObservableDelegate.h"
#include "Observer.h"
#include "EGIRunLoop.h"
#include "EGITask.h"
#include "EGIExceptions.h"

/**
 *  EGIBase namespace.
 */
namespace EGIBase{
	
	extern const char *getEGIBaseVersion();
	
}

#endif //EGIBase_DEFINED
