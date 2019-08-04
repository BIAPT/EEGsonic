
/**@file
 *  MFFFactory header.
 *  @author Robert Bell
 *  @date 28/06/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResourceType.h"
#import "MFFFactoryDelegate.h"

/**
 *  MFFFactory Class.
 *  @author Robert Bell.
 *  @remarks
 *  Factory class for management of MFF resources.
 *
 *  ------<br>
 *  Update: 2011-06-28: Class creation.<br>
 *  ------<br>
 */
@interface MFFFactory : NSObject {

@private
    id <MFFFactoryDelegate>delegate_;
}

@property (nonatomic, assign) id delegate;

-(id)initWithDelegate :(id)delegate;

+ (id)factory;
+ (id)factoryWithDelegate:(id)delegate;

/**
 * Tests whether a resource exists at the specified URI.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param uri The URI to test.
 * @param resourceType The type of resource (pass kAny to simply test for any resource
 * at that URI).
 * @return Whether or not the resource exists.
 */
- (BOOL)resourceExistsAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

/**
 * Creates a resource of the specified type at the specified URI.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param uri The URI at which to create the resource.
 * @param resourceType The type of resource to create.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)createResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

/**
 * Deletes a resource of the specified type at the specified URI.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
 *  or the caller does not have permissions to delete the resource.<br>
 *  ------<br>
 * @param uri The URI of the resource to be deleted.
 * @param resourceType The type of resource to create.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)deleteResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

/**
 * Moves a resource of the specified type at the specified source URI to the 
 * the specified destination URI.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
 *  or the caller does not have permissions to copy the resource.<br>
 *  ------<br>
 * @param uri The URI of the resource to be moved.
 * @param resourceType The type of resource to create.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)moveResourceAtURI :(NSString *)sourceURI toURI:(NSString *)destinationURI ofType:(MFFResourceType *)resourceType;

/**
 * Copies a resource of the specified type at the specified source URI to the 
 * the specified destination URI.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Fails if the resource is not the correct type, does not exist,
 *  or the caller does not have permissions to move the resource.<br>
 *  ------<br>
 * @param uri The URI of the resource to be copied.
 * @param resourceType The type of resource to create.
 * @return Returns NO on failure, YES on success.
 */
- (BOOL)copyResourceAtURI :(NSString *)sourceURI toURI:(NSString *)destinationURI ofType:(MFFResourceType *)resourceType;

/**
 * Opens a resource at the specifed URI of the specified type.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param uri The URI at which the resource is located.
 * @param resourceType The type of resource.
 * @return The newly opened resource, or nil if the resource failed to open.
 */
- (id)openResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

/**
 * Closes specified resource.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param resource The resource to close.
 * @return Whether or not the closing of the resource was successful.
 */
- (BOOL)closeResource  :(id)resource;

@end
