
/**@file
 *  XMLResource header.
 *  @author Robert Bell
 *  @date 15/04/2014
 *  @remarks
 *  Copyright 2014 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFXMLResource.h"

/**
 *  XMLStringMarshallingResource Class.
 *  @author Robert Bell.
 *  @remarks
 *  Essentially serialises MFF resourses to and from strings.
 *
 *  ------<br>
 *  Update (001): 2014-04-15: Class creation.<br>
 *  ------<br>
 */
@interface XMLStringMarshallingResource : MFFXMLResource {
    
@private
    
    BOOL statics_;
    
}

/**
 *  Statics option.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Some string conversion methods used in the local XML resource use statics to improve performance
 *  in non-threaded environments. If this is not desired (for example, you are using threads), set this to NO.<br>
 **/
@property (nonatomic, assign) BOOL statics;

/**
 * Init.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) Statics is on by default.<br>
 *  ------<br>
 * @return This object.
 */
-(id)init;

/**
 * Init with statics option.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A.<br>
 *  ------<br>
 * @param withStatics Sets statics to on or off.
 * @return This object.
 */
- (id)init:(BOOL)withStatics;

@end
