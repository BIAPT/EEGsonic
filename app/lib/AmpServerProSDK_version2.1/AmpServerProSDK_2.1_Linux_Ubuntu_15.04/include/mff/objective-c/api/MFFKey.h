
/**@file
 *  MFFKey header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFKey Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a key detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFKey : NSObject {

@private
    
    NSString *keyCode_;
    NSString *description_;
    NSString *data_;
    NSString *dataType_;
    
}

@property (nonatomic, copy) NSString *keyCode;
@property (nonatomic, copy) NSString *description;
@property (nonatomic, copy) NSString *data;
@property (nonatomic, copy) NSString *dataType;

@end
