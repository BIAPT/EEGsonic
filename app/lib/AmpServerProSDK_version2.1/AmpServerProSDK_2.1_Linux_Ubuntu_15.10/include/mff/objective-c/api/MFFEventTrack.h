
/**@file
 *  MFFEventTrack header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFEventTrack Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing an event track resource in the MFF. Please see
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
@interface MFFEventTrack  : MFFResource {

@private
    
    NSString *filename_;
    BOOL loaded_;
    NSString *name_;
    NSString *type_;
    NSMutableArray *events_;
    
}

/**
 *  The event track file name.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Todo: Clarify what this means exactly!<br>
 **/
@property (nonatomic, copy) NSString *filename;

/**
 *  The loaded flag.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Todo: Clarify what this means exactly!<br>
 **/
@property (nonatomic, assign, getter=isLoaded) BOOL loaded;

/**
 *  The event name.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The name of the event track is also a mangled version of the filename.
 *  See the MFF reference documentation for more details.<br>
 **/
@property (nonatomic, copy) NSString *name;

/**
 *  The event track type.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Examples of MFF event track types currently in use are:
 *  'STIM' or 'EVNT'. Typically these will be string representations
 *  of old FourCC codes, and this you might often see things like 'PAT ',
 *  (note the space).<br>
 **/
@property (nonatomic, copy) NSString *type;

/**
 *  The list of events for this event track.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFEvent. See the MFFEvent class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *events;

@end
