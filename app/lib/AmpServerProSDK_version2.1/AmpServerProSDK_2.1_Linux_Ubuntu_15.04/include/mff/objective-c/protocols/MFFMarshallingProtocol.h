
/**@file
 *  MFFMarshallingProtocol header.
 *  @author Robert Bell
 *  @date 10/02/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>
#import "MFFStreamProtocol.h"

/**
 *  MFFMarshallingProtocol.
 *  @author Robert Bell.
 *  @remarks
 *  The marshalling protocol is used by various classes that implement
 *  the persistence layer in the MFF.
 *
 *  ------<br>
 *  Update: 2011-02-10: Class creation.<br>
 *  ------<br>
 */
@protocol MFFMarshallingProtocol <NSObject>

- (id)marshal :(id)fromObject :(NSString *)uri;

- (id)unmarshal :(id)toObject :(NSString *)uri;

- (id)loadNewDataFromResource :(id)toObject;

- ( id<MFFStreamProtocol> )getStream :(id)forObject :(NSString *)uri;

@end
