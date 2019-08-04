
/**@file
 *  MFFCategory header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFCategory Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a category detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFCategory : NSObject {

@private
    
    NSString *name_;
    NSMutableArray *segments_;
    
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic, retain) NSMutableArray *segments;

@end
