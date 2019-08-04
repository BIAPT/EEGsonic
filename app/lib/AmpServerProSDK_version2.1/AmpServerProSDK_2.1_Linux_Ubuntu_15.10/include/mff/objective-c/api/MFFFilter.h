
/**@file
 *  MFFFilter header.
 *  @author Robert Bell
 *  @date 15/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFFilter Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a filter detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update (001): 2011-07-15: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-02-08: Changed end time, sampling frequency, cutoff frequency
 *  and passband attenuation to optional.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2012-10-02: Added comments for all the properties.<br>
 *  ------<br>
 */
@interface MFFFilter : NSObject {
    
@private
    
    uint64_t beginTime_;
    
    BOOL endTimePresent_;
    uint64_t endTime_;
    
    NSString *method_;
    NSString *type_;
    
    BOOL samplingFrequencyPresent_;
    uint64_t samplingFrequency_;
    NSString *samplingFrequencyUnits_;
    
    BOOL cutoffFrequencyPresent_;
    double cutoffFrequency_;
    NSString *cutoffFrequencyUnits_;
    
    BOOL passbandAttenuationPresent_;
    double passbandAttenuation_;
    NSString *passbandAttenuationUnits_;
    
}

/**
 *  The filter begin time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The filter begin time.<br>
 **/
@property (nonatomic, assign) uint64_t beginTime;

/**
 *  A flag indicating whether the end time is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the end time.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL endTimePresent;

/**
 *  The filter end time.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) The filter end time.<br>
 **/
@property (nonatomic, assign) uint64_t endTime;

/**
 *  The filter method.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) For example, "Hardware", or "FIR". This is interesting because "Hardware" does
 *  not tell one much. Ellaborate here!<br>
 **/
@property (nonatomic, copy) NSString *method;

/**
 *  The filter type.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) For example, "highpass", or "lowpass".<br>
 **/
@property (nonatomic, copy) NSString *type;

/**
 *  A flag indicating whether the sampling frequency is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the sampling frequency.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL samplingFrequencyPresent;

/**
 *  The sampling frequency.
 *  <b>Notes: 1) The units for this are in samplingFrequencyUnits_.</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) uint64_t samplingFrequency;

/**
 *  The sampling frequency units.
 *  <b>Notes: N/A</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *samplingFrequencyUnits;

/**
 *  A flag indicating whether the cutoff frequency is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the cutoff frequency.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL cutoffFrequencyPresent;

/**
 *  The cutoff frequency.
 *  <b>Notes: 1) The units for this are in cutoffFrequencyUnits_.</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) double cutoffFrequency;

/**
 *  The cutoff frequency units.
 *  <b>Notes: N/A</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *cutoffFrequencyUnits;

/**
 *  A flag indicating whether the pass band attenuation is present.
 *  <b>Notes:</b><br>
 *  &nbsp; 1) This flag is set automatically when setting the pass band attenuation.<br>
 *  &nbsp; 2) As with all optional entities in the MFF, this flag must be
 *  set to true if it is to be persisted.<br>
 **/
@property (nonatomic, assign) BOOL passbandAttenuationPresent;

/**
 *  The passband attenuation.
 *  <b>Notes: 1) The units for this are in passbandAttenuationUnits_.</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, assign) double passbandAttenuation;

/**
 *  The passband attenuation units.
 *  <b>Notes: N/A</b><br>
 *  &nbsp; N/A<br>
 **/
@property (nonatomic, copy) NSString *passbandAttenuationUnits;

@end
