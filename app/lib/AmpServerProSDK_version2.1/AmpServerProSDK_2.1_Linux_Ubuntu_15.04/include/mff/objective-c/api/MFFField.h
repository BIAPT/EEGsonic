
/**@file
 *  MFFField header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFField Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a field detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFField : NSObject {

@private
    
    NSString *name_;
    NSString *data_;
    NSString *dataType_;
    NSString *choices_;
    
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *data;
@property (nonatomic, copy) NSString *dataType;
@property (nonatomic, copy) NSString *choices;

@end
