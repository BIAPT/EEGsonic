
/**@file
 *  MFFFilePath header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFFilePath Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a file path detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-01-31: Changed "name" property to "creator".<br>
 *  ------<br>
 */
@interface MFFFilePath : NSObject {

@private
    
    NSString *filePath_;
    NSString *type_;
    NSString *creator_;
    
}

@property (nonatomic, copy) NSString *filePath;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSString *creator;

@end
