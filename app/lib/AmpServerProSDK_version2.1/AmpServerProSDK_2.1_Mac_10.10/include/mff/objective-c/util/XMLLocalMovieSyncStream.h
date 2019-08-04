
/**@file
 *  XMLLocalMovieSyncStream header.
 *  @author Robert Bell
 *  @date 02/02/2012
 *  @remarks
 *  Copyright 2011 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

#import "MFFStreamProtocol.h"

@class MFFMovieSyncs;

@interface XMLLocalMovieSyncStream : NSObject <MFFStreamProtocol> {
    
@protected
    
    NSString *uri_;
    NSFileHandle *resource_;
    MFFMovieSyncs *mffMovieSyncs_;
    
}

@property (nonatomic, copy) NSString *uri;
@property (nonatomic, retain) NSFileHandle *resource;
@property (nonatomic, retain, getter=getMFFMovieSyncs, setter=setMFFMovieSyncs:) MFFMovieSyncs *mffMovieSyncs;

- (id)init;

- (id)initWithURI :(NSString *)uri andMovieSynchs:(MFFMovieSyncs *)mffMovieSyncs;

@end