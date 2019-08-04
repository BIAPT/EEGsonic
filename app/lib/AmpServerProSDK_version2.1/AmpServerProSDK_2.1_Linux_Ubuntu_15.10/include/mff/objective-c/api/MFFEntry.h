
/**@file
 *  MFFEntry header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFEntry Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a entry detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFEntry : NSObject {

@private
    
    id entry_;
    NSString *type_;
    
}

@property (nonatomic, retain) id entry;
@property (nonatomic, copy) NSString *type;

@end
