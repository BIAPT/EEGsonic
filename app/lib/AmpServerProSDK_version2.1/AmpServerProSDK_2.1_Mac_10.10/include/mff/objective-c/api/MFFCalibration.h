
/**@file
 *  MFFCalibration header.
 *  @author Robert Bell
 *  @date 15/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFCalibration Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a calibration detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update (001): 2011-07-15: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-02-08: Changed end time to optional.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2012-10-02: Added comments for all the properties.<br>
 *  ------<br>
 */
@interface MFFCalibration : NSObject {
    
@private
    
    uint64_t beginTime_;
    BOOL endTimePresent_;
    uint64_t endTime_;
    NSString *type_;
    NSMutableArray *channels_;
    
}

/**
 *  The calibration begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The calibration begin time.<br>
 **/
@property (nonatomic, assign) uint64_t beginTime;

/**
 *  A flag indicating whether the end time is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the end time.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL endTimePresent;

/**
 *  The calibration end time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The calibration end time.<br>
 **/
@property (nonatomic, assign) uint64_t endTime;

/**
 *  The filter type.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) For example, "ICAL".<br>
 **/
@property (nonatomic, copy) NSString *type;

/**
 *  The channel list for this calibration.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFChannel. See the MFFChannel class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *channels;

@end
