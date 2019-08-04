
/**@file
 *  XMLResource header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFXMLResource.h"

/**
 *  XMLLocalFileResource Class.
 *  @author Robert Bell.
 *  @remarks
 *  Local implementation of XML support. Currently, "local" means XML in
 *  files residing on the local file system.
 *
 *  ------<br>
 *  Update (001): 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-01-26:
 *  &nbsp; 1) Added JTF category support.<br>
 *  &nbsp; 2) Added MFF version support.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2012-01-26: Added support for MFF version number.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (004): 2012-01-31:
 *  &nbsp; 1) Added Event channel support.<br>
 *  &nbsp; 2) Added attributes to file paths in the source file list.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (005): 2012-02-02:
 *  &nbsp; 1) Added movie sync support.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (006): 2012-02-06:
 *  &nbsp; 1) Fixed "spectral" tag so that it follows lower case start.<br>
 *  &nbsp; 2) Fixed "sourceData" tag so that it follows lower case start.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (007): 2012-02-08: Updated a number of tags to be optional in the MFF.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (008): 2012-04-11: Fixed minPower, maxPower, minPhase, and maxPhase which were
 *  incorrectly being stored as 64-bit integers.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (009): 2013-02-08: Added support for optional tag in the MFFSensors. DFB <br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (0010): 2013-04-05: Added support for statics option. RB <br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (0011): 2013-04-16: Added support for Dipole Sets. DFB <br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (0012): 2013-10-03: Updated PNS Set for Physio 16. DFB <br>
 *  ------<br>

 */
@interface XMLLocalFileResource : MFFXMLResource {
    
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
