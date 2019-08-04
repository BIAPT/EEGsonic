
/**@file
 *  MFFThread header.
 *  @author Robert Bell
 *  @date 16/08/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFThread Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a thread detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-08-16: Class creation.<br>
 *  ------<br>
 */
@interface MFFThread : NSObject {
    
@private
    
    uint32_t first_;
    uint32_t second_;
    
}

@property (nonatomic, assign) uint32_t first;
@property (nonatomic, assign) uint32_t second;

@end
