
/**@file
 *  MFFPNSSensor header.
 *  @author Robert Bell
 *  @date 15/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFPNSSensor Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a PNS sensor detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-07-15: Class creation.<br>
 *  ------<br>
 *  Update: 2013-12-03: Added Physio 16 additions. DFB.<br>
 *  ------<br>
 */
@interface MFFPNSSensor : NSObject {
    
@private
    
    NSString *name_;
    uint32_t number_;
    NSString *unit_;
    uint32_t psgType_;
    uint32_t mapping_;
    uint64_t samplingRate_;
    
	NSString *sensorType_;
	
    BOOL highpassPresent_;
    double highpass_;
    
    BOOL lowpassPresent_;
    double lowpass_;
    
    BOOL notchPresent_;
    double notch_;
    
    BOOL groupNumberPresent_;
    uint32_t groupNumber_;
    
    BOOL conversionPresent_;
    uint32_t conversion_;
	
	BOOL gainPresent_;
	float gain_;

	BOOL defaultAmplitudePresent_;
	float defaultAmplitude_;
    
	BOOL defaultDisplayHighpassPresent_;
	double defaultDisplayHighpass_;

	BOOL defaultDisplayLowpassPresent_;
	double defaultDisplayLowpass_;

	BOOL defaultDisplayNotchPresent_;
	double defaultDisplayNotch_;

	BOOL colorPresent_;
	NSString *colorString_;
	
	BOOL polarityPresent_;
	BOOL positiveUp_;
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) uint32_t number;
@property (nonatomic, copy) NSString *unit;
@property (nonatomic, assign) uint32_t psgType;
@property (nonatomic, assign) uint32_t mapping;
@property (nonatomic, assign) uint64_t samplingRate;
@property (nonatomic, copy) NSString *sensorType;

@property (nonatomic, assign, getter=isHighpassPresent) BOOL highpassPresent;
@property (nonatomic, assign) double highpass;

@property (nonatomic, assign, getter=isLowpassPresent) BOOL lowpassPresent;
@property (nonatomic, assign) double lowpass;

@property (nonatomic, assign, getter=isNotchpassPresent) BOOL notchPresent;
@property (nonatomic, assign) double notch;

@property (nonatomic, assign, getter=isGroupNumberPresent) BOOL groupNumberPresent;
@property (nonatomic, assign) uint32_t groupNumber;

@property (nonatomic, assign, getter=isConversionPresent) BOOL conversionPresent;
@property (nonatomic, assign) uint32_t conversion;

@property (nonatomic, assign, getter=isGainPresent) BOOL gainPresent;
@property (nonatomic, assign) float gain;
@property (nonatomic, assign, getter=isDefaultAmplitudePresent) BOOL defaultAmplitudePresent;
@property (nonatomic, assign) float defaultAmplitude;
@property (nonatomic, assign, getter=isDefaultDisplayHighpassPresent) BOOL defaultDisplayHighpassPresent;
@property (nonatomic, assign) double defaultDisplayHighpass;
@property (nonatomic, assign, getter=isDefaultDisplayLowpassPresent) BOOL defaultDisplayLowpassPresent;
@property (nonatomic, assign) double defaultDisplayLowpass;
@property (nonatomic, assign, getter=isDefaultDisplayNotchPresent) BOOL defaultDisplayNotchPresent;
@property (nonatomic, assign) double defaultDisplayNotch;
@property (nonatomic, assign, getter=isColorPresent) BOOL colorPresent;
@property (nonatomic, copy) NSString *colorString;
@property (nonatomic, assign, getter = isPolarityPresent) BOOL polarityPresent;
@property (nonatomic, assign) BOOL positiveUp;
@end
