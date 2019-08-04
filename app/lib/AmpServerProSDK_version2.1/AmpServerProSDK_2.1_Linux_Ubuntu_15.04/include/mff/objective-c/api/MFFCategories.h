
/**@file
 *  MFFCategories header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFCategories Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a categories resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFCategories : MFFResource {
    
@private
    
    NSMutableArray *categories_;
}

@property (nonatomic, retain) NSMutableArray *categories;


@end
