
/**@file
 *  ECIClientController header.
 *  @author Robert Bell
 *  @date 10/08/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#import <Foundation/Foundation.h>

class ConnectionObject;

@interface ECIClientController : NSObject {
    
@private
    
    IBOutlet NSButton *connectDisconnect_;
    IBOutlet NSTextField *eciServerAddress_;
    IBOutlet NSTextField *eciServerPort_;
    IBOutlet NSPopUpButton *simpleECICommand_;
    IBOutlet NSTextView *output_;
    
    ConnectionObject *connection_;
    char *eciServerCharStringAddress;
    int eciServerPortNumber_;
    
}

@property (assign) IBOutlet NSButton *connectDisconnect;
@property (assign) IBOutlet NSTextField *eciServerAddress;
@property (assign) IBOutlet NSTextField *eciServerPort;
@property (assign) IBOutlet NSPopUpButton *simpleECICommand;
@property (assign) IBOutlet NSTextView *output;

- (IBAction)connectToServer:(id)sender;

- (IBAction)sendSimpleECICommand:(id)sender;

- (IBAction)sendECICommandSequence:(id)sender;

- (void)log:(NSString *)message;

@end
