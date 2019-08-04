
/**@file
 *  MFFSegment header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFSegment Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a segment detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-10-18: Added comments for all the properties.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2013-02-08: Changed the channels from being an array of NSNumbers 
 *		to being an array of MFFChannelStatus objects.
 *		Removed exclusion, because that is in the MFFChannelStatus object.<br>
 *  ------<br>
 
 */
@interface MFFSegment : NSObject {

@private
    
    NSString *status_;
    NSString *name_;
    NSMutableArray *faults_;
    
    BOOL clockStartTimePresent_;
    NSString *clockStartTime_;
    
    uint64_t beginTime_;
    uint64_t endTime_;
    uint64_t eventBegin_;
    uint64_t eventEnd_;
    NSMutableArray *channels_;
    NSMutableArray *keys_;
    
}

/**
 *  The segment status.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) For example: "good", "bad".<br>
 **/
@property (nonatomic, copy) NSString *status;

/**
 *  The segment name.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The segment faults.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) An array of NSString objects. Each string represents a fault.<br>
 **/
@property (nonatomic, retain) NSMutableArray *faults;

/**
 *  A flag indicating whether the clock start time is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the clock
 *  start time.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL clockStartTimePresent;

/**
 *  The segment clock start time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Todo: Add explanation here!<br>
 **/
@property (nonatomic, copy) NSString *clockStartTime;

/**
 *  The segment begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, assign) uint64_t beginTime;

/**
 *  The segment end time.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, assign) uint64_t endTime;

/**
 *  The segment event begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The event begin time around which this segment was created.<br>
 **/
@property (nonatomic, assign) uint64_t eventBegin;

/**
 *  The segment event begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The event end time around which this segment was created.<br>
 **/
@property (nonatomic, assign) uint64_t eventEnd;

/**
 *  A list of channels for this segment that have some attribute to take into
 *  account.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFChannelStatus.<br>
 **/
@property (nonatomic, retain) NSMutableArray *channels;

/**
 *  The key list for this segment.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFKey. See the MFFKey class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *keys;

@end
