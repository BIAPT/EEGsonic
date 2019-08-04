
/*
 *  AppDelegate.m
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright (c) 2015 EGI. All rights reserved.<br>
 */

#import "AppDelegate.h"

@interface AppDelegate ()

@property IBOutlet NSWindow *window;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [self->appController_ log:@"AmpServerProSDKWriteToMFF - version:1.0 date: 2015-09-30\n"];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    [self->appController_ freeResources];
}

@end
