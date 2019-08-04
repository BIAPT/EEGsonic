
/**@file
 *  AppController Header File
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright (c) 2015 EGI. All rights reserved.<br>
 */

#import <Cocoa/Cocoa.h>

@class AmpPropertiesTableDelegate;

/**
 *  AppController Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class is the main controller class for the UI. Most functionality starts here with
 *  helper classes being invoked to enable the application to accomplish it's tasks.<br>
 *
 *  <b> Important Notes: N/A</b><br>
 *
 *  ------<br>
 *  Update (001): 2015-09-30: Class creation.<br>
 *  ------<br>
 */
@interface AppController : NSObject {
    
    IBOutlet NSButton *connectButton_;
    IBOutlet NSButton *startStopButton_;
    IBOutlet NSButton *recordButton_;
    IBOutlet NSProgressIndicator *recordingInProgressIndicator_;
    
    IBOutlet NSButton *setSamplingRate_;
    IBOutlet NSPopUpButton *samplingRateList_;
    IBOutlet NSTextField *currentSamplingRate_;
    IBOutlet NSButton *forceMFFSamplingRate;
    
    IBOutlet NSPopUpButton *commandList_;
    IBOutlet NSTextField *commandChannel_;
    IBOutlet NSTextField *commandValue_;
    IBOutlet NSButton *sendCommand_;
    
    IBOutlet NSTextField *ipAddress_;
    IBOutlet NSButton *setFilePathButton_;
    IBOutlet NSTextField *filePath_;
    IBOutlet NSTextField *fileName_;
    
    // Most of this application's ouput is written to this area. There are
    IBOutlet NSTextView *logOutput_;
    
    // UI and related elements to display the currently connected amplifier's properties.
    IBOutlet NSTableView *ampPropertiesTable_;
    IBOutlet AmpPropertiesTableDelegate *ampPropertiesTableDelegate_;
    
    // Amp Server Pro SDK and related upport.
    //
    // This is being defined in this manner so as to minimize
    // the C++ type exposure to other objective-c files.
    struct SDKImpl* sdkWrapper_;
    
    // Command lists.
    // This could be placed in an XML file for easier loading.
    NSArray *na300CommandList_;
    NSArray *na400CommandList_;
    
    // Sample rate lists.
    NSArray *na300SamplingRateList_;
    NSArray *na400SamplingRateList_;
    NSArray *na410SamplingRateList_;
    int currentSamplingRateValue_;
    
    BOOL isRunning_;
    BOOL isRecording_;
    
}

@property int currentSamplingRateValue;
@property BOOL isRunning;
@property BOOL isRecording;

// Attempts to connect to the Amp Server at the address specified in
// the ip address text field.
- (IBAction)connect:(id)sender;

// Starts and stops the amplifer.
- (IBAction)startStop:(id)sender;

// Sets the amplifier to the desired sampling rate.
- (IBAction)setSamplingRate:(id)sender;

// Sends the selected command to the amplifier.
- (IBAction)sendCommand:(id)sender;

// Starts and stops recording.
//
// Note: This is an example application. If if you start and stop recording, the previous file
// (if it exists) will be overwritten.
- (IBAction)recordOnOff:(id)sender;

// Opens a dialog to set the file path in the file path text field.
- (IBAction)setFilePath:(id)sender;

// Quits the application.
- (IBAction)quit:(id)sender;

// Start amp.
- (BOOL) startAmp;

// Stop amp.
- (BOOL) stopAmp;

// Start recording.
- (BOOL)startRecording;

// Stop recording.
- (BOOL)stopRecording;

// Send desired sampling rate to the amp.
- (BOOL)sendSamplingRate: (int)samplingRate;

// Frees up resources in the controller when it is expected that the controller
// will no longer be used (e.g., when the application is quitting).
- (void)freeResources;

// Pops up an alert window with the given type and message.
-(void)alert:(NSAlertStyle)alertType withMessage:(NSString *)message;

// Checks the format of the string for a valid IP address.
//
// Note 1: It does not try to see if the address is valid from a connection perspective.
//
// Note 2: True if the string is a valid IPv4 or IPv6 address.
- (BOOL)isValidIPAddress:(NSString *)ipAddress;

// Logs messages to the log window of this application directly.
//
// Note: Do NOT use this method to log from a different thread.
- (void)log:(NSString *)message;

// Logs messages to the log window of this application indirectly.
//
// Note: Use this method to log from a different thread.
- (void)logToInterface:(NSString *)message;

// Error message.
//
// Note: Do NOT use this method to flag an error from a different thread.
- (void)error:(NSString *)message;

// Error message.
//
// Note: Use this method to flag an error from a different thread.
- (void)errorToInterface:(NSString *)message;

// Tests.
- (IBAction)layoutTest:(id)sender;

- (IBAction)fileTest:(id)sender;


@end
