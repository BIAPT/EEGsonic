
/**@file
 *  MFFEpochs header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFEpochs Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a epochs resource in the MFF. Please see
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
@interface MFFEpochs : MFFResource {
    
@private
    
    NSMutableArray *epochs_;
}

/**
 *  The epochs list for this epochs.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type Epoch. See the Epoch class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *epochs;


@end
