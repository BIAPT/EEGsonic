
/**@file
 *  MFFFileSignalBlock header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFSignalBlock.h"

/**
 *  MFFFileSignalBlock Class.
 *  @author Robert Bell.
 *  @remarks
 *  When dealing with local signal files, signal blocks are actually
 *  of type MFFFileSignalBlock.<br>
 *  ------<br>
 *  Type description for the below properties:<br>
 *  &nbsp; 1) header: NSData.<br>
 *  &nbsp; 2) optionalHeader: NSData.<br>
 *  &nbsp; 3) data: NSData.<br>
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-08-31: Added property comments, plus type descriptions for the "id" types.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-10-11: Added trailing underscores to match coding guidelines.<br>
 *  ------<br>
 */
@interface MFFFileSignalBlock : MFFSignalBlock {

@private
    
    long fileOffsetForHeader_;
    long fileOffsetForData_;
    
}

/**
 *  The actual offset in the file for this block's header.
 **/
@property (nonatomic, assign) long fileOffsetForHeader;

/**
 *  The actual offset in the file for this block's data.
 **/
@property (nonatomic, assign) long fileOffsetForData;

+ (id)signalBlock;

@end
