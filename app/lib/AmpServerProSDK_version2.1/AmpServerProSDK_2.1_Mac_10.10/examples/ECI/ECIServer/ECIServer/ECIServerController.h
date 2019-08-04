//
//  ECIServerController.h
//  ECIServer
//
//  Created by Robert Bell on 8/8/12.
//  Copyright 2012 Electrical Geodesics, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

class AS_TCP_Server;
class AS_TCP_PortHandler;


@interface ECIServerController : NSObject {

@private
    
    IBOutlet NSButton *startStopECIServer_;
    IBOutlet NSTextField *eciServerPort_;
    IBOutlet NSTextView *output_;
    
    AS_TCP_Server *eciServer_;
    AS_TCP_PortHandler *eciPortHandler_;
    int eciServerPortNumber_;
    
}

@property (assign) IBOutlet NSButton *startStopECIServer;
@property (assign) IBOutlet NSTextField *eciServerPort;
@property (assign) IBOutlet NSTextView *output;

- (IBAction)startStopECIServer:(id)sender; 

- (void)log:(NSString *)message;
- (void)logToInterface:(NSString *)message;

@end
