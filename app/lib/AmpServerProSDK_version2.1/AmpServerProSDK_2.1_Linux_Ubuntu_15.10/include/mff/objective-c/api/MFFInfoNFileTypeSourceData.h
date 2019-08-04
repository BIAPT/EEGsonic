
/**@file
 *  MFFInfoNFileTypeSourceData header.
 *  @author Robert Bell
 *  @date 19/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFInfoNFileTypeSourceData Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an int(n) source data file type detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-07-19: Class creation.<br>
 *  ------<br>
 */
@interface MFFInfoNFileTypeSourceData : NSObject {
    
@private
    
    NSString *dipoleSetName_;
    uint64_t numberOfOrientation_;
    
}

@property (nonatomic, copy) NSString *dipoleSetName;
@property (nonatomic, assign) uint64_t numberOfOrientation;

@end
