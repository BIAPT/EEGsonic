
/**@file
 *  StringMFFFactoryDelegate header.
 *  @author Robert Bell
 *  @date 15/04/2014
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFFactoryDelegate.h"

/**
 *  StringMFFFactoryDelegate Class.
 *  @author Robert Bell.
 *  @remarks
 *  Implements the MFFFactoryDelegate protocol for MFF resources in the local
 *  file system.
 *
 *  ------<br>
 *  Update: 2014-04-15: Class creation.<br>
 *  ------<br>
 */
@interface StringMFFFactoryDelegate : NSObject <MFFFactoryDelegate>{
    
@private
    
    BOOL threadSafe_;
    
}

/**
 *  Thread safe option.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Every attempt will be made to use thread safe methods for reading and writing
 *  files. The platform notes should be checked to ensure that setting this to true does
 *  actually provide thread safety.<br>
 **/
@property (nonatomic, assign) BOOL threadSafe;

/**
 * Init.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Thread safe is off by default.<br>
 *  ------<br>
 * @return This object.
 */
-(id)init;

/**
 * Init with thread safe option.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param withThreadSafe Sets thread safety to on or off.
 * @return This object.
 */
- (id)init:(BOOL)withThreadSafe;

- (BOOL)resourceExistsAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

- (BOOL)createResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

- (BOOL)deleteResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

- (BOOL)moveResourceAtURI :(NSString *)sourceURI toURI:(NSString *)destinationURI ofType:(MFFResourceType *)resourceType;

- (BOOL)copyResourceAtURI :(NSString *)sourceURI toURI:(NSString *)destinationURI ofType:(MFFResourceType *)resourceType;

- (id)openResourceAtURI :(NSString *)uri ofType:(MFFResourceType *)resourceType;

- (BOOL)closeResource  :(id)resource;

@end
