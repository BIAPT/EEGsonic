
/**@file
 *  MFFChannel header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFChannel Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a channel detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFChannel : NSObject {

@private

    uint32_t channelNumber_;
    NSString *data_;
    
}

@property (nonatomic, assign) uint32_t channelNumber;
@property (nonatomic, copy) NSString *data;

@end
