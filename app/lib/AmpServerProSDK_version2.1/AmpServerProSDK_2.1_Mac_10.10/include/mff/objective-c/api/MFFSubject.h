
/**@file
 *  MFFSubject header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFSubject Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a subject resource in the MFF. Please see
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
@interface MFFSubject : MFFResource {
    
@private
    
    NSMutableArray *fields_;
    NSMutableArray *mris_;
}

/**
 *  The field list for this subject.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type Field. See the Field class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *fields;

/**
 *  The MRI list for this subject.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type NSString, currently representing
 *  the filenames for the MRI files.<br>
 **/
@property (nonatomic, retain) NSMutableArray *mris;

@end
