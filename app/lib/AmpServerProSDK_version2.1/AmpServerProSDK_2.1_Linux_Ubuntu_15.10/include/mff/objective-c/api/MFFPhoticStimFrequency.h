/**@file
 *  MFFPhoticStimFrequency header.
 *  @author David Borland
 *  @date 4/9/14
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>
/**
 *  MFFPhoticStimFrequency Class.
 *  @author David Borland
 *  @remarks
 *  This class wraps the concept of a photic stim pulse sequence. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2013-04-16: Class creation.<br>
 *  ------<br>
 */

#import <Foundation/Foundation.h>

@interface MFFPhoticStimFrequency : NSObject<NSCopying> {
@private
	float			frequency_;
	int32_t			duration_;
	int32_t			rest_;
	int32_t			repeatCount_;
}
@property (nonatomic) float frequency;
@property (nonatomic) int32_t duration;
@property (nonatomic) int32_t rest;
@property (nonatomic) int32_t repeatCount;


@end
