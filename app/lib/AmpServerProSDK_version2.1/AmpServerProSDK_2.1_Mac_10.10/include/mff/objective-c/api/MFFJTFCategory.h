

/**@file
 *  MFFJTFCategory header.
 *  @author Robert Bell
 *  @date 26/01/2012
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFJTFCategory Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a jtf category detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2012-01-26: Class creation.<br>
 *  ------<br>
 */
@interface MFFJTFCategory : NSObject {
    
@private
    
    NSString *name_;
    uint64_t numberOfSegments_;
    uint64_t segmentEventTime_;
    uint64_t duration_;
    NSMutableArray *frequencies_;
    double minPower_;
    double maxPower_;
    
    BOOL phasePresent_;
    double minPhase_;
    double maxPhase_;
    
}

/**
 *  The category name.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The number of segments.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is the number of segments that were combined together in the
 *  JTF calculations to create this category.<br>
 **/
@property (nonatomic, assign) uint64_t numberOfSegments;

/**
 *  The segment event time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The event begin time around which the original segments were created.<br>
 **/
@property (nonatomic, assign) uint64_t segmentEventTime;

/**
 *  The duration.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The duration of each segment in this category.<br>
 **/
@property (nonatomic, assign) uint64_t duration;

/**
 *  A list of frequencies for this category.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The frequencies for which the JTF data was calculated.<br>
 *  &nbsp; 2) This is a list of type NSDouble.<br>
 **/
@property (nonatomic, retain) NSMutableArray *frequencies;

/**
 *  The min power.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The minimum power value for the whole category.<br>
 **/
@property (nonatomic, assign) double minPower;

/**
 *  The max power.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The maximum power value for the whole category.<br>
 **/
@property (nonatomic, assign) double maxPower;

/**
 *  Indicates whether the phase is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The user has the choice of whether to compute circular variance or not.<br>
 **/
@property (nonatomic, assign, getter=isPhasePresent) BOOL phasePresent;

/**
 *  The min phase.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The minimum circular variance value for the whole category.<br>
 **/
@property (nonatomic, assign) double minPhase;

/**
 *  The max phase.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The maximum circular variance value for the whole category.<br>
 **/
@property (nonatomic, assign) double maxPhase;

@end
