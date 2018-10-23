
/**@file
 *  MFFGTENModulationConfigurationFile header.
 *  @author Robert Bell
 *  @date 04/10/2014
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFGTENModulationConfigurationFile Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing an info resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2014-10-04: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2015-02-12: Updated to new naming for this resource and added
 *  more content (also removed some).<br>
 *  ------<br>
 */
@interface MFFGTENModulationConfigurationFile : MFFResource {
    
@private
    
    NSString *name_;
    NSString *subjectID_;
    NSString *planGenerator_;
    NSString *executedBy_;
    NSString *dateExecuted_;
    NSMutableArray *trains_;
}

/**
 *  The patient or subject name.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The patient or subject ID.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *subjectID;

/**
 *  The plan generator.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *planGenerator;

/**
 *  The plan executor.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *executedBy;

/**
 *  The execution date.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is in the MFF date time format,
 *  for example: "2007-09-05T10:48:42.599000+07:00".<br>
 **/
@property (nonatomic, copy) NSString *dateExecuted;

/**
 *  The trains list for this source mcf.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, retain) NSMutableArray *trains;

@end
