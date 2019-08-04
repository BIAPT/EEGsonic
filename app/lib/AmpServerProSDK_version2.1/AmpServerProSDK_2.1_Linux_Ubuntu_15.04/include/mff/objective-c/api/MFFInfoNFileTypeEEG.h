
/**@file
 *  MFFInfoNFileTypeEEG header.
 *  @author Robert Bell
 *  @date 19/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFInfoNFileTypeEEG Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an int(n) EEG file type detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-07-19: Class creation.<br>
 *  ------<br>
 */
@interface MFFInfoNFileTypeEEG : NSObject {
    
@private
    
    NSString *sensorLayoutName_;
    NSString *montageName_;
	NSString *referenceScheme_;
}

@property (nonatomic, copy) NSString *sensorLayoutName;
@property (nonatomic, copy) NSString *montageName;
@property (nonatomic, copy) NSString *referenceScheme;
+ (id)infoN;

@end
