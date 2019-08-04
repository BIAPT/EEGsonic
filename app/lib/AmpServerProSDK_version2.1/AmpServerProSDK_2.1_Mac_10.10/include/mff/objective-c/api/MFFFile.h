
/**@file
 *  MFFFile header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFFile Class.
 *  @author Robert Bell.
 *  @remarks
 *  Conceptual wrapper of an MFF file.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-12-18: Added getMFFVersion.<br>
 *  ------<br>
 */
@interface MFFFile : MFFResource {

@private
    
}

/**
 * Gets the file listing for this MFF file.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * at that URI).
 * @return The list of files in an NSArray of type NSString *.
 */
- (NSArray *)getMFFFileListing;

/**
 * Get the MFF version.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) MFF versions start at 1. Thus, a value of zero indicates that no version
 *  is present.<br>
 *  ------<br>
 * at that URI).
 * @return The MFF version number.
 */
- (uint32_t)getMFFVersion;

@end
