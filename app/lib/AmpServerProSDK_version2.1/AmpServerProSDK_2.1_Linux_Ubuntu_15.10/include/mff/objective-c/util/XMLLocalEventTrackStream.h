
/**@file
 *  XMLLocalEventTrackStream header.
 *  @author Robert Bell
 *  @date 31/10/2011
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFStreamProtocol.h"

@class MFFEventTrack;

@interface XMLLocalEventTrackStream : NSObject <MFFStreamProtocol> {
        
@protected
    
    NSString *uri_;
    NSFileHandle *resource_;
    MFFEventTrack *eventTrack_;
    
}

@property (nonatomic, copy) NSString *uri;
@property (nonatomic, retain) NSFileHandle *resource;
@property (nonatomic, retain) MFFEventTrack *eventTrack;

- (id)init;

- (id)initWithURI :(NSString *)uri andEventTrack:(MFFEventTrack *)eventTrack;

@end