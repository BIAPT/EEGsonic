
/**@file
 *  MFFMovieSyncs header.
 *  @author Robert Bell
 *  @date 02/02/2012
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFMovieSyncs Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a movie syncs resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 02/02/2012: Class creation.<br>
 *  ------<br>
 */
@interface MFFMovieSyncs : MFFResource {
    
@private
    
    NSMutableArray *movieSyncs_;
}

/**
 *  The movie synchronizations list for this movie synchronization resource.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFMovieSync. See the MFFMovieSync class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *movieSyncs;


@end
