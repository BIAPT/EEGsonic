//
//  ECIServerController.m
//  ECIServer
//
//  Created by Robert Bell on 8/8/12.
//  Copyright 2012 Electrical Geodesics, Inc. All rights reserved.
//

#import "ECIServerController.h"

// Amp Server Pro SDK.
#include "AS_TCP_Server.h"
#include "ECICommandDelegate.h"

using namespace EGIBase;

@implementation ECIServerController

@synthesize startStopECIServer=startStopECIServer_;
@synthesize eciServerPort=eciServerPort_;
@synthesize output=output_;

- (id)init {
    
    self = [super init];
    
    if (self) {
        
        self->eciServer_ = NULL;
        self->eciPortHandler_ = NULL;
        
        // Set to a default port number.
        self->eciServerPortNumber_ = -1;
        
    }
    
    return self;
}

- (void)dealloc {
    
    [super dealloc];
    
    RELEASE(self->eciServer_);
    RELEASE(self->eciPortHandler_);
    
}

- (void)awakeFromNib {
    
    [self log:@"ECIServer: version: 1.0 date: 2012_08_08\n"];
    
    self->eciServer_ = NULL;
    self->eciPortHandler_ = NULL;
    
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    [self log:@"ECIServer: version: 1.0 date: 2012_08_08\n"];
    
}

- (IBAction)startStopECIServer:(id)sender {
    
    // Under normal circumstances, we would toggle a start / stop state. However,
    // AS_TCP_Server has no machinery to stop an active server at present. This will
    // be added soon, in the meantime however, once a server is started, all further
    // requests are ignored, and option to stop is not presented.
    //
    // Note: Quitting the application will stop the server.
    
    if ( self->eciServer_ == NULL ) {
        
        // Start the server.
        self->eciServerPortNumber_ = [self->eciServerPort_ intValue];
        
        if ( (self->eciServerPortNumber_ >= 2048) && (self->eciServerPortNumber_ < 100000) ) {
            
            self->eciServer_ = new AS_TCP_Server();
            
            // Start the command server.
            self->eciPortHandler_ = self->eciServer_->initPortHandler(AS_TCP_PortHandler::ECI, self->eciServerPortNumber_, NULL);
            ECICommandDelegate *eciCommandDelegate = new ECICommandDelegate();
            eciCommandDelegate->init(NULL);
            eciCommandDelegate->setController(self);
            self->eciPortHandler_->setDelegate(eciCommandDelegate);
            
            
        } else {
            
            [self log:@"ECIServer: error: allowed port range is: 2048 -> 10000\n"];
            self->eciServerPortNumber_ = -1;
            
        }
        
        // Update UI to indicate that the server is running.
        [self->startStopECIServer_ setTitle:@"ECI Server Running..."];
        
    } else {
        
        [self log:@"ECIServer: error: server already running\n"];
        
    }
    
    [self log:@"ECIServer: - (IBAction)startStopECIServer:(id)sender\n"];
    
}

-(void)log:(NSString *)message {
    
	[self->output_ setEditable:YES];
	[self->output_ replaceCharactersInRange:NSMakeRange([[self->output_ string] length], 0) withString:message];
	[self->output_ scrollRangeToVisible:NSMakeRange([[self->output_ string] length], 0)];
	[self->output_ setEditable:NO];
    
}

- (void)logToInterface:(NSString *)message{
    
	[self performSelectorOnMainThread:@selector(log:) withObject:message waitUntilDone:NO];

}


@end
