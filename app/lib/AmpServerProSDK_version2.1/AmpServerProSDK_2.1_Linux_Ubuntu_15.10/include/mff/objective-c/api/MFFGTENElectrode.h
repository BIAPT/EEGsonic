
/**@file
 *  MFFGTENElectrode header.
 *  @author Robert Bell
 *  @date 18/02/2015
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFGTENElectrode Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an event detailed in the MFFGTENElectrode
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2015-02-18: Class creation.<br>
 *  ------<br>
 */
@interface MFFGTENElectrode : NSObject {
    
@private
    
    uint64_t channelNumber_;
    float amplitude_;
    
}

/**
 *  The channel number.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t channelNumber;

/**
 *  The amplitude.
 *  <b>Notes:</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) float amplitude;

@end
