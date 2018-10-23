
/**@file
 *  MFFJTFCategories header.
 *  @author Robert Bell
 *  @date 26/01/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFResource.h"

/**
 *  MFFJTFCategories Class.
 *  @author Robert Bell.
 *  @remarks
 *  With the category information contained in the JTFCategory file and the number
 *  of channels from the sensorlayout.xml file, you can make sense of how the
 *  signal blocks are organized in the signal bin files.<br>
 *<br>
 *  The signal bin file is organized in this manner, based on the category information.
 *  Each signal block is a channel's worth of data.
 *<br>  
 *  If the category has the flag set for having phase information, it looks like this:<br>
 *  Category 1:<br>
 *  Power matrix for channel 1<br>
 *  Circular Variance(called phase) for channel 1<br>
 *  Power matrix for channel 2<br>
 *  Circular Variance(called phase) for channel 2<br>
 *  :<br>
 *  :<br>
 *  Power matrix for channel N<br>
 *  Circular Variance(called phase) for channel N<br>
 *  Category 2:<br>
 *  Power matrix for channel 1<br>
 *  Circular Variance(called phase) for channel 1<br>
 *  Power matrix for channel 2<br>
 *  Circular Variance(called phase) for channel 2<br>
 *  :<br>
 *  :<br>
 *  Power matrix for channel N<br>
 *  Circular Variance(called phase) for channel N<br>
 *<br>
 *  Otherwise this:<br>
 *  Category 1:<br>
 *  Power matrix for channel 1<br>
 *  Power matrix for channel 2<br>
 *  :<br>
 *  :<br>
 *  Power matrix for channel N<br>
 *  Category 2:<br>
 *  Power matrix for channel 1<br>
 *  Power matrix for channel 2<br>
 *  :<br>
 *  :<br>
 *  Power matrix for channel N<br>
 *
 *  ------<br>
 *  Update: 2012-01-26: Class creation.<br>
 *  ------<br>
 */
@interface MFFJTFCategories : MFFResource {
    
@private
    
    NSMutableArray *categories_;
}

@property (nonatomic, retain) NSMutableArray *categories;


@end
