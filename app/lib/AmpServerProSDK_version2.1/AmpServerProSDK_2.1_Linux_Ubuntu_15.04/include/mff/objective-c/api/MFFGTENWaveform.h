
/**@file
 *  MFFGTENWaveform header.
 *  @author Robert Bell
 *  @date 12/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFGTENWaveform Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an event detailed in the MFFGTENWaveform
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2015-02-12: Class creation.<br>
 *  ------<br>
 */
@interface MFFGTENWaveform : NSObject {
    
@private
    
    uint64_t id_;
    NSMutableArray *samples_;
    float frequency_;
    uint64_t pulseLength_;
    uint64_t delayLength_;
    
}

/**
 *  The waveform id.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t id;

/**
 *  The waveform samples.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The list of samples that characterize the waveform.
 *  &nbsp; 2) This is a list of type NSNumber initialized by [NSNumber numberWithFloat: ...].<br>
 **/
@property (nonatomic, retain) NSMutableArray *samples;

/**
 *  The frequency.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) float frequency;

/**
 *  The pulse length.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is currently in miroseconds.<br>
 **/
@property (nonatomic, assign) uint64_t pulseLength;

/**
 *  The delay length id.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This is currently in miroseconds.<br>
 **/
@property (nonatomic, assign) uint64_t delayLength;

@end
