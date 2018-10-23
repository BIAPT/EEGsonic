
/**@file
 *  MFFNeighbor header.
 *  @author Robert Bell
 *  @date 16/08/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  Channel MFFNeighbor.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a neighbor detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-08-16: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-11-11: Added comments for all the properties.<br>
 *  ------<br>
 */
@interface MFFNeighbor : NSObject {
    
@private
    
    uint32_t channelNumber_;
    NSMutableArray *neighbors_;
    
}

/**
 *  The channel number.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint32_t channelNumber;

/**
 *  The list of neighbours.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type NSNumber initialized with numberWithUnsignedInt.<br>
 **/
@property (nonatomic, retain) NSMutableArray *neighbors;

@end
