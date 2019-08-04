
/**@file
 *  MFFInfoNFileTypeJTF header.
 *  @author Robert Bell
 *  @date 19/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFInfoNFileTypeJTF Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an int(n) JTF file type detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-07-19: Class creation.<br>
 *  ------<br>
 */
@interface MFFInfoNFileTypeJTF : NSObject {
    
@private
    
    NSString *sensorLayoutName_;
    NSString *montageName_;
    NSString *path_;
    uint64_t samplingRate_;
    
}

@property (nonatomic, copy) NSString *sensorLayoutName;
@property (nonatomic, copy) NSString *montageName;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, assign) uint64_t samplingRate;

@end
