
/**@file
 *  MFFGTENTrain header.
 *  @author Robert Bell
 *  @date 12/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFGTENTrain Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an train detailed in the MFFGTENTrain
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2015-02-12: Class creation.<br>
 *  ------<br>
 */
@interface MFFGTENTrain : NSObject {
    
@private

    uint64_t id_;
    BOOL conditioning_;
    NSMutableArray *waveforms_;
    NSMutableArray *blocks_;
    
}

/**
 *  The waveform id.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t id;

/**
 *  Whether or not this is a conditioning train.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) BOOL conditioning;

/**
 *  A list of waveforms pertaining to this train.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFGTENWaveforms. See the MFFGTENWaveforms class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *waveforms;

/**
 *  A list of blocks pertaining to this train.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFGTENBlocks. See the MFFGTENBlocks class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *blocks;

@end
