/**@file
 *  MFFPhoticStimSequence header.
 *  @author David Borland
 *  @date 4/9/14
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>
/**
 *  MFFPhoticStimSequence Class.
 *  @author David Borland
 *  @remarks
 *  This class describes a photic stim sequences,called a Frequency Train in the SRS
 *
 *  ------<br>
 *  Update: 2014-04-9: Class creation.<br>
 *  ------<br>
 *///

#import <Foundation/Foundation.h>

@interface MFFPhoticStimSequence : NSObject <NSCopying> {
@private
	uint64_t		beginTime_;
	NSString		*name_;
	NSMutableArray  *sequences_;
	NSString		*startEventLabel_;
	bool			useStartEvent_;
	NSString		*endEventLabel_;
	bool			useEndEvent_;
	NSString		*flashEventLabel_;
	bool			useFlashEvent_;
}
@property (nonatomic) uint64_t beginTime;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, retain) NSMutableArray *sequences;
@property (nonatomic, copy) NSString *startEventLabel;
@property (nonatomic) bool useStartEvent;
@property (nonatomic, copy) NSString *endEventLabel;
@property (nonatomic) bool useEndEvent;
@property (nonatomic, copy) NSString *flashEventLabel;
@property (nonatomic) bool useFlashEvent;


@end
