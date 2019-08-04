/**@file
 *  MFFPhoticStimRunFile header.
 *  @author David Borland
 *  @date 4/10/14
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFPhoticStimRunFile Class.
 *  @author DavidBorland
 *  @remarks
 *  An MFF resource representing a series of photic stim sequences that were ran during the recording
 *
 *  ------<br>
 *  Update: 2014-04-10: Class creation.<br>
 *  ------<br>
*/
#import "MFFResource.h"

@interface MFFPhoticStimRunFile : MFFResource {
	NSMutableArray	*sequences_;

}
@property (nonatomic, retain) NSMutableArray *sequences;


@end
