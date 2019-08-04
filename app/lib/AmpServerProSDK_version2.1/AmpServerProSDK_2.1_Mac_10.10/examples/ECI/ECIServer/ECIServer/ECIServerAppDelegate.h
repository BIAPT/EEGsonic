//
//  ECIServerAppDelegate.h
//  ECIServer
//
//  Created by Robert Bell on 7/31/12.
//  Copyright 2012 Electrical Geodesics, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ECIServerAppDelegate : NSObject <NSApplicationDelegate> {
    
@private
    
    NSWindow *window;

}

@property (assign) IBOutlet NSWindow *window;

@end
