
/**@file
 *  MFFFields header.
 *  @author Robert Bell
 *  @date 27/09/2013
 *  @remarks
 *  Copyright 2013 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFFields Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a fields resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2013-09-27: Class creation.<br>
 *  ------<br>
 */
@interface MFFFields : MFFResource {
    
@private
    
    NSMutableArray *fields_;
}

/**
 *  The field list.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type Field. See the Field class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *fields;

@end
