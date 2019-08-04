
/**@file
 *  MFFGTENBlock header.
 *  @author Robert Bell
 *  @date 13/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFGTENBlock Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an event detailed in the MFFGTENBlock
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2015-02-13: Class creation.<br>
 *  ------<br>
 */
@interface MFFGTENBlock : NSObject {
    
@private
    
    uint64_t id_;
    uint64_t duration_;
    uint64_t rest_;
    uint64_t waveformID_;
    NSMutableArray *electrodes_;
    
}

/**
 *  The block id.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t id;

/**
 *  The duration.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t duration;

/**
 *  The reset.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t rest;

/**
 *  The waveform id.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t waveformID;

/**
 *  The electrode list for this block.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is a list of type MFFGTENElectrode. See the MFFGTENElectrode class for more information.<br>
 **/
@property (nonatomic, retain) NSMutableArray *electrodes;

@end
