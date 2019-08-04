
/**@file
 *  MFFSignalBlock header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>


/**
 *  MFFSignalBlock Class.
 *  @author Robert Bell.
 *  @remarks
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
@interface MFFSignalBlock : NSObject {

@private
    
    // Header.
    int32_t version_;
    int32_t headerSize_;
    int32_t dataBlockSize_;
    int32_t numberOfSignals_;
    int32_t *offsets_;
    int32_t *signalDepth_;
    int32_t *signalFrequency_;
    
    // Optional header.
    int32_t optionalHeaderSize_;
    int32_t optionalHeaderType_;
    
    // Actual data abstraction.
    //
    // Depending on the actual persistence layer, these
    // are often null.
    id header_;
    id optionalHeader_;
    id data_;
    
}

/**
 *  The block version.
 **/
@property (nonatomic, assign) int32_t version;

/**
 *  The header size for the block.
 **/
@property (nonatomic, assign) int32_t headerSize;

/**
 *  The data size for the block.
 **/
@property (nonatomic, assign) int32_t dataBlockSize;

/**
 *  The number of signals contained in the data block.
 **/
@property (nonatomic, assign) int32_t numberOfSignals;

/**
 *  An array of "int32_t" of offsets of length equal to the number of signals.
 **/
@property (nonatomic, assign) int32_t *offsets;

/**
 *  An array of "int32_t" of signal depths of length equal to the number of signals.
 **/
@property (nonatomic, assign) int32_t *signalDepth;

/**
 *  An array of "int32_t" of signal frequencies of length equal to the number of signals.
 **/
@property (nonatomic, assign) int32_t *signalFrequency;

/**
 *  The optional header size.
 **/
@property (nonatomic, assign) int32_t optionalHeaderSize;

/**
 *  The optional header type (see MFF specification).
 **/
@property (nonatomic, assign) int32_t optionalHeaderType;

/**
 *  The header for this block as defined in the MFF specification.<br>
 *  The type will be subclass specific, please see subclasses for information.
 **/
@property (nonatomic, retain) id header;

/**
 *  The optional header for this block as defined in the MFF specification.
 *  The type will be subclass specific, please see subclasses for information.
 */
@property (nonatomic, retain) id optionalHeader;

/**
 *  The data for this block as defined in the MFF specification.<br>
 *  The type will be subclass specific, please see subclasses for information.
 */
@property (nonatomic, retain) id data;

@end
