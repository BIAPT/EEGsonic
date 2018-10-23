
/**@file
 *  MFFCoordinates header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

@class MFFSensorLayout;

/**
 *  MFFCoordinates Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a coordinates resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-10-18: Added comments for all the properties.<br>
 *  ------<br>
 */
@interface MFFCoordinates : MFFResource {

@private

    MFFSensorLayout *sensorLayout_;
    NSString *acquisitionTime_;
    NSString *acquisitionMethod_;
    BOOL defaultSubject_;
    
}

/**
 *  The sensor layout for this coordinates resource.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 **/
@property (nonatomic, retain) MFFSensorLayout *sensorLayout;

/**
 *  The acquisition time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in the MFF date time format,
 *  for example: "2007-09-05T10:48:42.599000000+07:00".<br>
 **/
@property (nonatomic, copy) NSString *acquisitionTime;

/**
 *  The acquisition method.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This can be any string describing the acquisition method, for example:
 *  "An Average of Many Data Sets"<br>
 **/
@property (nonatomic, copy) NSString *acquisitionMethod;

/**
 *  A flag for the default subject.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign, getter=isDefaultSubject) BOOL defaultSubject;

@end
