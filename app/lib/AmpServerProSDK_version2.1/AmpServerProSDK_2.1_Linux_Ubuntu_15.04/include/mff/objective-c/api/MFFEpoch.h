
/**@file
 *  MFFEpoch header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFEpoch Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an epoch detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFEpoch : NSObject {

@private
    
    uint64_t beginTime_;
    uint64_t endTime_;
    uint64_t firstBlock_;
    uint64_t lastBlock_;
    
}

@property (nonatomic, assign) uint64_t beginTime;
@property (nonatomic, assign) uint64_t endTime;
@property (nonatomic, assign) uint64_t firstBlock;
@property (nonatomic, assign) uint64_t lastBlock;

+ (id)epoch;

@end
