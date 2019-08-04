
/**@file
 *  MFF Types and defines header.
 *  @author Robert Bell
 *  @date 04/08/2013
 *  @remarks
 *  Copyright 2013 EGI. All rights reserved.<br>
 *  A collection of type definitions.
 */

#ifndef MFFTypesAndDefines_DEFINED
#define MFFTypesAndDefines_DEFINED

#include <stdint.h>

/**
*
*  The different types of InfoN files.
*
*/
typedef enum {
    
    kMFF_UnknownInfoNFileType   = -1,
    kMFF_EEG                    = 0,
    kMFF_Spectral               = 1,
    kMFF_SourceData             = 2,
    kMFF_PNSData                = 3,
    kMFF_JTF                    = 4,
    kMFF_TValues                = 5
    
} MFF_InfoNFileType;

#endif //MFFTypesAndDefines_DEFINED

