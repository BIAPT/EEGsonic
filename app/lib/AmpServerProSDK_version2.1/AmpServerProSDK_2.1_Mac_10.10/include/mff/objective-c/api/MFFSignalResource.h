
/**@file
 *  MFFSignalResource header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

@class MFFSignalBlock;

/**
 *  MFFSignalResource Class.
 *  @author Robert Bell.
 *  @remarks
 *  Represents a the binary format of a signal resource in the MFF.<br>
 *  Please reference the MFF specification for a definition of the properties
 *  for this class.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update: 2011-08-31: Added property comments.<br>
 *  ------<br>
 */
@interface MFFSignalResource : MFFResource {
        
@private
    
    int32_t version_;
    int64_t numberOfBlocks_;
    NSMutableArray *signalBlocks_;
}

/**
 *  The version number of this signal file.
 **/
@property (nonatomic, assign) int32_t version;

/**
 *  The number of blocks in this signal file.
 **/
@property (nonatomic, assign) int64_t numberOfBlocks;

/**
 *  The signal blocks. Each member of the array is of base type "MFFSignalBlock",
 *  and the actual type will vary depending on the signal resource involved (for example,
 *  a "FileMFFSignalResource").
 **/
@property (nonatomic, retain) NSMutableArray *signalBlocks;


/**
 * 
 * Gets a signal block. As mentioned in the MFF notes, the MFFSignalResource object is
 * not quite a data transfer object in that it does encapsulate some
 * behaviour. In this case, when a signal file is unmarshalled, a map of
 * the blocks is created (as noted in the unmarshall notes). To load the
 * actual signal data for a particular block, this method must be called.
 * Please reference the example code for more details.
 * 
 * @param signalBlock The signal block to load.
 * @return The passed in signal block instance with the signal data loaded.
 */
- (MFFSignalBlock *)loadSignalBlockData :(MFFSignalBlock *)signalBlock;

/**
 * Writes a well-formed signal block to the end of uri resource.
 * 
 * @param signalBlock The signal block to write.
 * @return The passed in instance is returned as is.
 */
- (MFFSignalBlock *)writeSignalBlock :(MFFSignalBlock *)signalBlock;

@end
