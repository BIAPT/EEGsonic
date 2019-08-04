
/**@file
 *  MFFZone header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

/**
 *  MFFZone Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class wraps the concept of a zone detailed in the MFF
 *  specification. Please reference that document for details.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@interface MFFZone : NSObject {

@private
    
    NSMutableArray *color_;
    NSMutableArray *channels_;
    NSMutableArray *boundry_;
    
}

@property (nonatomic, retain) NSMutableArray *color;
@property (nonatomic, retain) NSMutableArray *channels;
@property (nonatomic, retain) NSMutableArray *boundry;

@end
