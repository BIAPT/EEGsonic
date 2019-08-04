
/**@file
 *  MFFResource header.
 *  @author Robert Bell
 *  @date 28/06/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>
#import "MFFStreamProtocol.h"

@class MFFResourceType;

/**
 *  MFFResource Class.
 *  @author Robert Bell.
 *  @remarks
 *  The parent class of all "proper" MFF resources. Currently, the concept of
 *  "proper" is that any resource that can be mapped to a URI.
 *
 *  ------<br>
 *  Update: 2011-06-28: Class creation.<br>
 *  ------<br>
 */
@interface MFFResource : NSObject {

@protected
    
    NSString *uri_;
    id resourceDelegate_;
    MFFResourceType *resourceType_;
    
}

@property (nonatomic, copy) NSString *uri;
@property (nonatomic, retain) id resourceDelegate;
@property (nonatomic, retain) MFFResourceType *resourceType;

/**
 * Init.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return Returns self.
 */
- (id)init;

/**
 * Init.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param uri The resource URI.
 * @return Returns self.
 */
- (id)initWithURI :(NSString *)uri;

/**
 * Init.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param uri The resource URI.
 * @param resourceDelegate The resource delegate.
 * @return Returns self.
 */
- (id)initWithURI :(NSString *)uri andResourceDelegate:(id)resourceDelegate
   andResourceType:(MFFResourceType *)resourceType;

/**
 * Saves the MFF resource.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return true = sucess; false = failure.
 */
- (BOOL)saveResource;

/**
 * Loads the MFF resource.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return true = sucess; false = failure..
 */
- (BOOL)loadResource;

/**
 * loads the new data from resource
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return true = sucess; false = failure..
 */
- (BOOL)loadNewDataFromResource;

/**
 * If this resource is able to be streamed, the stream is returned.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return true = sucess; false = failure.
 */
- ( id<MFFStreamProtocol> )getStream;

/**
 * Gets the string representation of this MFF resource.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @return The string representation of this MFF resource.
 */
- (NSString *)getStringRepresentation;

@end
