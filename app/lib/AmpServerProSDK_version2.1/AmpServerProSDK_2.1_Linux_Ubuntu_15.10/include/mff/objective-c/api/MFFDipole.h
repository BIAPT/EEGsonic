/**@file
 *  MFFDipole header.
 *  @author David Borland
 *  @date 4/16/13
 *  @remarks
 *  Copyright 2013 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>
/**
 *  MFFDipole Class.
 *  @author David Borland
 *  @remarks
 *  This class wraps the concept of a dipole detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2013-04-16: Class creation.<br>
 *  ------<br>
 */

@interface MFFDipole : NSObject {

@private
	NSString *name_;
	float computationX_;
	float computationY_;
	float computationZ_;
	float visualizationX_;
	float visualizationY_;
	float visualizationZ_;
}

@property (nonatomic, copy) NSString *name;
@property (nonatomic) float computationX;
@property (nonatomic) float computationY;
@property (nonatomic) float computationZ;
@property (nonatomic) float visualizationX;
@property (nonatomic) float visualizationY;
@property (nonatomic) float visualizationZ;


@end
