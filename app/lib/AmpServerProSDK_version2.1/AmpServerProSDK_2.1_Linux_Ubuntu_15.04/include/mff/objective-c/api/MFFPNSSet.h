
/**@file
 *  MFFPNSSet header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFPNSSet Class.
 *  @author Robert Bell.
 *  @remarks
 *  An MFF resource representing a PNS set resource in the MFF. Please see
 *  a description of handling "proper" MFF resources contained in the introduction
 *  to the MFF API.
 *
 *  ------<br>
 *  Update: 2011-09-15: Class creation.<br>
 *  ------<br>
 *  Update: 2013-12-03: Added Amp Series String. DFB.<br>
 *  ------<br>
 */
@interface MFFPNSSet  : MFFResource {
    
@private
    
    NSString *name_;
    NSMutableArray *pnsSensors_;
    NSString *ampSeries_;
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic, retain) NSMutableArray *pnsSensors;
@property (nonatomic, copy) NSString *ampSeries;
@end
