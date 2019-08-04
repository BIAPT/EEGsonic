
/**@file
 *  LocalSignalFile header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFMarshallingProtocol.h"

@class MFFSignalBlock;
@class MFFFileSignalBlock;
@class MFFSignalResource;
@interface LocalSignalFile : NSObject <MFFMarshallingProtocol> {

@private
    
    NSString *uri_;
    MFFFileSignalBlock *savedFileSignalBlock_;
}

@property (nonatomic, copy) NSString *uri;


- (id)initWithURI :(NSString *)uri;

/**
 * Loads the metadata for the signal bin file.
 * 
 * @param loadDataBlock If true, the data block is read from the file.
 */
- (NSMutableArray *) loadSignalBlocks :(BOOL)loadDataBlocks;

- (MFFSignalBlock *) loadSignalBlockData :(MFFSignalBlock *)signalBlock;

- (MFFSignalBlock *) writeSignalBlockData :(MFFSignalBlock *)signalBlock;

- (void) printSignalBlockSummary :(MFFSignalBlock *)signalBlock;

/** 
 This method loads any new signal blocks into the resource that are new since the last time the resource was loaded
 */
- (void) updateSignalBlocks :(MFFSignalResource *)signalResource;
@end
