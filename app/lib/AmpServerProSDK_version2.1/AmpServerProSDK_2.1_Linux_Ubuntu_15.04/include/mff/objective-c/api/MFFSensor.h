
/**@file
 *  MFFSensor header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFSensor Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a sensor detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *
 *  Update (001): 2013-02-08: Added identifier variable. DFB <br>
 *  ------<br>
 */
@interface MFFSensor : NSObject {

@private
    
    NSString *name_;
    uint32_t number_;
    uint32_t type_;
    float x_;
    float y_;
    float z_;
    
    BOOL originalNumberPresent_;
    uint32_t originalNumber_;
  
	BOOL identifierPresent_;
	uint32_t identifier_;
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) uint32_t number;
@property (nonatomic, assign) uint32_t type;
@property (nonatomic, assign) float x;
@property (nonatomic, assign) float y;
@property (nonatomic, assign) float z;

@property (nonatomic, assign) BOOL originalNumberPresent;
@property (nonatomic, assign) uint32_t originalNumber;

@property (nonatomic, assign) BOOL identifierPresent;
@property (nonatomic, assign) uint32_t identifier;

@end
