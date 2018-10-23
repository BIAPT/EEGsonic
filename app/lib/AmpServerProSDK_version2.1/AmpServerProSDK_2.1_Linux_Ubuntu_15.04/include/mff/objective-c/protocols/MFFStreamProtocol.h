
/**@file
 *  MFFStreamProtocol header.
 *  @author Robert Bell
 *  @date 10/31/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFStreamProtocol Class.
 *  @author Robert Bell.
 *  @remarks
 *  Put notes here.
 *
 *  ------<br>
 *  Update: 2011-10-31: Class creation.<br>
 *  ------<br>
 */
@protocol MFFStreamProtocol <NSObject>

/**
 * Opens the element stream.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param withObject Currently not used.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)openStream :(id)withObject;

/**
 * Closes the element stream.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param withObject Currently not used.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)closeStream :(id)withObject;

/**
 * Writes an elemement to the stream.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param element The element to write.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)writeElement :(id)element;

@end
