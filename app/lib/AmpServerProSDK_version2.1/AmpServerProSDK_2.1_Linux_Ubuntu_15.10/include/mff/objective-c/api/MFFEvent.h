
/**@file
 *  MFFEvent header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

@class MFFKey;

/**
 *  MFFEvent Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an event detailed in the MFF
 *  specification. Please reference that document for details.
 *  ------<br>
 *  Update: 2015-11-9: Added relative begin time and segmentation Event.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFEvent : NSObject {
    
@private
    
    NSString *beginTime_;
	uint64_t relativeBeginTime_;
    uint64_t duration_;
    NSString *code_;
    NSString *label_;
    NSString *description_;
    NSString *sourceDevice_;
    NSMutableArray *channels_;
    NSMutableArray *keys_;
	BOOL segmentationEvent_;
    
}

+ (id)event;

/**
 *  The event begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in MFF datetime format.<br>
 **/
@property (nonatomic, copy) NSString *beginTime;

/**
 *  The events relative begin time from the begining of the recording.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) N/A. <br>
 **/
@property (nonatomic,assign) uint64_t relativeBeginTime;

/**
 *  The event duration.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, assign) uint64_t duration;

/**
 *  The event code.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a 4 character code in string format - <br>
 *  &nbsp; example: cel#<br>
 **/
@property (nonatomic, copy) NSString *code;

/**
 *  The event label.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) A longer event descripter than the code.
 **/
@property (nonatomic, copy) NSString *label;

/**
 *  The event label.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) A description of the event.
 **/
@property (nonatomic, copy) NSString *description;

/**
 *  The event source device.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Describes the event source - example: Multi-Port ECI.<br>
 *  &nbsp; example: Multi-Port ECI.<br>
 **/
@property (nonatomic, copy) NSString *sourceDevice;

/** 
 *	Is this event one that the user segmented upon 
 **/
@property (nonatomic) BOOL segmentationEvent;

/**
 *  A list of channels pertaining to this event.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type NSNumber initialized by [NSNumber numberWithUnsignedInt: ...].<br>
 **/
@property (nonatomic, retain) NSMutableArray *channels;

/**
 *  The key list for this segment.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFKey. See the MFFKey class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *keys;

@end
