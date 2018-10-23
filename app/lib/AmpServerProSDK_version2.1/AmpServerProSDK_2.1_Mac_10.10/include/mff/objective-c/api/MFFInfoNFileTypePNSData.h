
/**@file
 *  MFFInfoNFileTypePNSData header.
 *  @author Robert Bell
 *  @date 19/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFInfoNFileTypePNSData Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an int(n) PNS data file type detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-07-19: Class creation.<br>
 *  ------<br>
 */
@interface MFFInfoNFileTypePNSData : NSObject {
    
@private
    
    NSString *pnsSetName_;
    
}

@property (nonatomic, copy) NSString *pnsSetName;

+ (id)infoN;

@end
