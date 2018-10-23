
/**@file
 *  Pair header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>


@interface Pair : NSObject {
@private
    id first_;
    id second_;
}

@property (nonatomic, retain) id  first;
@property (nonatomic, retain) id  second;

- (id)initWithValues :(id)first :(id)second;

@end
