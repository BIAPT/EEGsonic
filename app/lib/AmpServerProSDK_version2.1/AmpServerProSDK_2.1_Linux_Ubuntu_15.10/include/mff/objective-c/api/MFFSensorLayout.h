
/**@file
 *  MFFSensorLayout header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFSensorLayout Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a sensor layout detailed in the MFF
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
 *  Update: 2012-01-28: Added original layout support.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2015-09-14: Added blank spaces support.<br>
 *  ------<br>
 */
@interface MFFSensorLayout : MFFResource {

@private
    
    NSString *name_;
    NSMutableArray *sensors_;
    NSMutableArray *threads_;
    NSMutableArray *tilingSets_;
    NSMutableArray *neighbors_;
    NSMutableArray *zones_;
    NSString *originalLayout_;
    BOOL intercranial_;
    NSMutableArray *mapping_;
	NSMutableArray *spaces_;
}

/**
 *  The sensor layout name.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The sensor list for this sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type Sensor. See the Sensor class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *sensors;

/**
 *  The thread list for this sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFThread. See the MFFThread class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *threads;

/**
 *  The tiling set list for this sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type NSNumber initialized by [NSNumber numberWithUnsignedInt: ...].<br>
 **/
@property (nonatomic, retain) NSMutableArray *tilingSets;

/**
 *  The neigbor list for this sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFNeigbor. See the MFFNeigbor class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *neighbors;

/**
 *  The zone list for this sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFZone. See the MFFZone class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *zones;

/**
 *  The original layout.
 *  <b>Notes:</b><br> 
 *  &nbsp; 1) Specifies which layout the file came from when it's a subsampled file.<br>
 **/
@property (nonatomic, copy) NSString *originalLayout;

/**
 *  A flag indicating whether this is an intercranial sensor layout.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign, getter=isIntercranial) BOOL intercranial;

/**
 *  The mapping.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Todo: Do not know what this is for. It looks as if it might be unused and
 *  being confused with the mapping in the MFFPNSSensor class. Clarify whether this can
 *  be removed or has some other function!<br>
 **/
@property (nonatomic, retain) NSMutableArray *mapping;

/**
 *  The spaces.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is used to specifiy where blank spaces are meant to go into a sensor layout.
 * This is a list NSNumber objects specifying what sensor the space should go after.   IE, if it's zero, the
 * space will go after the sensor in the 0th place of the sensor array <br>
 **/
@property (nonatomic, retain) NSMutableArray *spaces;

@end
