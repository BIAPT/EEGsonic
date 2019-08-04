//
//  ECIClientAppDelegate.h
//  ECIClient
//
//  Created by Robert Bell on 7/31/12.
//  Copyright 2012 Electrical Geodesics, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ECIClientAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
