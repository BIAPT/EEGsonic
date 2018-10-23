
/**@file
 *  FileSignalBlock header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "SignalBlock.h"


@interface FileSignalBlock : SignalBlock {

@private
    
    long fileOffsetForHeader;
    long fileOffsetForData;
    
}

@property (nonatomic, assign) long fileOffsetForHeader;
@property (nonatomic, assign) long fileOffsetForData;

@end
