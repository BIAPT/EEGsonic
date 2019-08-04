
/**@file
 *  MFFInfoNFileTypeSpectral header.
 *  @author Robert Bell
 *  @date 19/07/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFInfoNFileTypeSpectral Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of an int(n) spectral file type detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update (001): 2011-07-19: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-02-08: Changed end time to optional.<br>
 *  ------<br>
 */
@interface MFFInfoNFileTypeSpectral : NSObject {
    
@private
    
    NSString *sensorLayoutName_;
    NSString *montageName_;
    double deltaF_;
    NSString *path_;
    uint64_t beginTime_;
    
    BOOL endTimePresent_;
    uint64_t endTime_;
    
    float minX_;
    float maxX_;
    float minY_;
    float maxY_;
    
}

@property (nonatomic, copy) NSString *sensorLayoutName;
@property (nonatomic, copy) NSString *montageName;
@property (nonatomic, assign) double deltaF;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, assign) uint64_t beginTime;

@property (nonatomic, assign) BOOL endTimePresent;
@property (nonatomic, assign) uint64_t endTime;

@property (nonatomic, assign) float minX;
@property (nonatomic, assign) float maxX;
@property (nonatomic, assign) float minY;
@property (nonatomic, assign) float maxY;

@end
