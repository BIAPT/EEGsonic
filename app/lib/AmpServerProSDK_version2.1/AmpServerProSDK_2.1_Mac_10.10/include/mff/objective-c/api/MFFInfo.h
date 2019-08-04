
/**@file
 *  MFFInfo header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFInfo Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing an info resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-10-20: Added comments for all the properties.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2012-01-26: Added support for MFF version number.<br>
 *  ------<br>
 */
@interface MFFInfo : MFFResource {
    
@private
    
    
    BOOL mFFVersionPresent_;
    uint32_t mFFVersion_;
    
    NSString *recordTime_;
    NSString *ampSerialNumber_;
    NSString *ampFirmwareVersion_;
    
    BOOL movieDeltaPresent_;
    uint64_t movieDelta_;
	
	BOOL ampTypePresent_;
	NSString *ampType_;
	
	BOOL acquisitionVersionPresent_;
	NSString *acquisitionVersionNumber_;
}

/**
 *  Indicates whether the MFF version number is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the mff version.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign, getter=isMFFVersionPresent) BOOL mFFVersionPresent;

/**
 *  The MFF version number.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This number begins at 0.<br>
 **/
@property (nonatomic, assign) uint32_t mFFVersion;

/**
 *  The record time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in the MFF date time format,
 *  for example: "2007-09-05T10:48:42.599000+07:00".<br>
 **/
@property (nonatomic, copy) NSString *recordTime;

/**
 *  The amplifier serial number.
 *  <b>Notes:</b><br>
 *  &nbsp; See the MFF usage notes for explanation.<br>
 **/
@property (nonatomic, copy) NSString *ampSerialNumber;

/**
 *  The amplifier firmware version.
 *  <b>Notes:</b><br>
 *  &nbsp; See the MFF usage notes for explanation.<br>
 **/
@property (nonatomic, copy) NSString *ampFirmwareVersion;

/**
 *  A flag indicating whether the movie delta is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the movie delta.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign, getter=isMovieDeltaPresent) BOOL movieDeltaPresent;

/**
 *  The movie delta.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Todo: Add explanation here!<br>
 **/
@property (nonatomic, assign) uint64_t movieDelta;

/**
 *  Indicates whether the amp type is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the mff version.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic,getter=isAmpTypePresent) BOOL ampTypePresent;

/**
 *  The amplifier type.
 *  <b>Notes:</b><br>
 *  &nbsp; See the MFF usage notes for explanation.<br>
 **/
@property (nonatomic, copy) NSString *ampType;

/**
 *  Indicates whether the acquisition version number is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the mff version.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic,getter=isAcquistionVersionPresent) BOOL acquisitionVersionPresent;
/**
 *  The acquisition version number.
 *  <b>Notes:</b><br>
 *  &nbsp; See the MFF usage notes for explanation.<br>
 **/
@property (nonatomic, copy) NSString *acquisitionVersionNumber;

@end
