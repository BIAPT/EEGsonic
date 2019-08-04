
/**@file
 *  SignalUtil header.
 *  @author Robert Bell
 *  @date 14/06/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>


@interface SignalUtil : NSObject {

@private
    
}

+ (void *)packSignalInfo :(int32_t)signalDepth :(int32_t)signalFrequency;

+ (int32_t *)unpackSignalInfo :(const void *)signalInfo;

@end
