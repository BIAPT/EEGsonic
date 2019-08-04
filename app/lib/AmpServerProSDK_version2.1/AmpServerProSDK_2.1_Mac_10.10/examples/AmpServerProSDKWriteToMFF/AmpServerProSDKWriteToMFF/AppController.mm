
/*
 *  AppController.mm
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright (c) 2015 EGI. All rights reserved.<br>
 */

#import "AppController.h"

#include "AS_Network_Client_Base.h"
#include "DataStreamObserver.h"

// Other EGI Base includes.
#include "EGIBase.h"
#include "EGIBuffer.h"
#include "EGICircularBuffer.h"

#include "EGICircularBuffer.h"
#include "EGIExceptions.h"
#include "EGIRunLoop.h"

// Local MFF.
#include "MFFWriter.h"
#include "MFFFileWriterUtilities.h"

// Links to interface resources.
#import "AmpPropertiesTableDelegate.h"

// Other includes.
#include <arpa/inet.h>

using namespace EGIBase;
using namespace com::egi::services::mff::api;

// Some useful defines.

// 1152 * 1264 * 700 = 1019289600 (Just over a GB).
// This number is chosen because it is an mulitple of both the packet 1 and packet 2
// sizes. This will ensure that if the buffer wraps, it will wrap in a manner that keeps
// the data consistent.
#define BUFFER_SIZE_BYTES 1019289600

struct SDKImpl {
    
    AS_Network_Client *client;
    AS_Network_Types::AmpInfo ampInfo;
    DataStreamObserver *dataStreamObserver;
    EGIRunLoop *egiRunLoop;
    MFFWriter *mffWriter;
    EGICircularBuffer *ampBuffer = NULL;
    EGIBuffer::Opts *ampBufferOpts = NULL;
    
};

@implementation AppController

@synthesize currentSamplingRateValue = currentSamplingRateValue_;
@synthesize isRunning = isRunning_;
@synthesize isRecording = isRecording_;

-(void)awakeFromNib {
    
    // As this object is instantiated from the NIB, allocate the dependent objects
    // we need for the lifecycle of this application.
    self->sdkWrapper_ = new SDKImpl();
    
    // Amp Server Pro SDK's main client object. Just as in the SimpleClient example of the
    // SDK, this is the gateway to Amp Server functionality (and thus the amplifer).
    self->sdkWrapper_->client = new AS_Network_Client();
    
    // This gets created after we have connected (when we now all about the amplifer).
    self->sdkWrapper_->dataStreamObserver = NULL;
    
    // In this example, handling the writing of data to the MFF file is performed as a task on
    // an EGI runloop. The initilization of it here, and the use of a runloop is purely a matter
    // of preference, and you should feel free to modify the logic of the code as you see fit.
    //
    // Note: An EGI runloop spawns an additional thread of execution, and thus appropriate threading
    // techniques are employed to ensure data integrity.
    //
    self->sdkWrapper_->egiRunLoop = new EGIRunLoop(true, true);
    self->sdkWrapper_->egiRunLoop->setRunLoopDelay(10000);
    self->sdkWrapper_->egiRunLoop->startRunLoop();
    self->sdkWrapper_->mffWriter = NULL;
    
    // Initialize the amplifier buffer. This is the buffer into which we will temporarily place data
    // received from the amplifer before we process it into an MFF file.
    //
    // Note: As mentioned above, the use of an EGI buffer here is purely an example, and feel free to
    // use any data structure you see fit.
    
    EGIBuffer::Code bufferRet = EGIBuffer::NEUTRAL;
    self->sdkWrapper_->ampBuffer = new EGICircularBuffer(true); // The true option ensures the buffer is thread safe.
    bufferRet = self->sdkWrapper_->ampBuffer->createBuffer(BUFFER_SIZE_BYTES);
    if ( bufferRet != EGIBuffer::SUCCESS ) {
        std::cout << "Error: unable to create amplifer buffer: " << bufferRet << std::endl;
    } else {
        std::cout << "Info: created buffer, size: " << BUFFER_SIZE_BYTES / 1048576 << "MB" << std::endl;
    }
    
    // EGI buffers have various options, one is unfortunately named as "uByCopy". This indicates
    // whether the EGI buffer will be responsible for allocating memory in response to reads, or whether
    // the caller passes in a pointer to already allocated memory. In this case, our task will pre-allocate
    // the memory to avoid excessive allocations, hence "uByCopy" is false. You will see this used in the MFFTask
    // class.
    self->sdkWrapper_->ampBufferOpts = new EGIBuffer::Opts();
    self->sdkWrapper_->ampBufferOpts->uByCopy = false;
    
    // Populate the command list arrays.
    self->na300CommandList_ = [[NSArray alloc ] initWithObjects:@"cmd_Start", @"cmd_Stop", @"cmd_SetLowpass", @"cmd_TurnAll10KOhms",
                               @"cmd_TurnChannel10KOhms", @"cmd_TurnAllDriveSignals", @"cmd_TurnChannelDriveSignals", @"cmd_SetPoint01HighPass",
                               @"cmd_SetSubjectGround", @"cmd_SetCurrentSource", @"cmd_SetChannelResets", @"cmd_SetCalibrationSignalFreq",
                               @"cmd_SetChannelResetThreshold", @"cmd_SetBufferedReference", @"cmd_SetOscillatorGate", @"cmd_SetReference10KOhms",
                               @"cmd_SetReferenceDriveSignal", @"cmd_SetEllipticalFilter", @"cmd_SetNotchFilter", @"cmd_SetMaster",
                               @"cmd_SetPower", /*@"cmd_Reset",*/ @"cmd_SetWaveShape", @"cmd_SetCalibrationSignalRange",
                               @"cmd_SetDrivenCommon", @"cmd_SetCalibrationSignalAmplitude", @"cmd_SetAnalogOutput", @"cmd_SetDigitalOutputData",
                               @"cmd_SetDigitalInOutDirection", @"cmd_IQAmpData", @"cmd_GetStartTime", @"cmd_GetCurrentTime",
                               @"cmd_GetCurrentDrift", /*@"cmd_SetFilterAndDecimate", @"cmd_SetDecimatedRate",*/ @"cmd_SetMRIPulseInfo",
                               @"cmd_SetPIBChannelGain", /*@"cmd_SetCOM10KOhms", @"cmd_SetCOMDriveSignal",*/ @"cmd_SetCalibrationControl",
                               /*@"cmd_TurnChannelZeroOhms", @"cmd_TurnAllZeroOhms", @"cmd_SetPhoticStimSequence", @"cmd_GetPhysioConnectionStatus",*/
                               /*@"cmd_SetADCDynamicRange", @"cmd_SetNativeRate",*/ @"cmd_GetAmpDetails", @"cmd_GetAmpStatus",
                               @"cmd_DefaultAcquisitionState", @"cmd_DefaultSignalGeneration", @"cmd_NumberOfAmps", @"cmd_NumberOfActiveAmps", nil];
    
    self->na400CommandList_ = [[NSArray alloc ] initWithObjects:@"cmd_Start", @"cmd_Stop", @"cmd_SetLowpass", @"cmd_TurnAll10KOhms",
                               @"cmd_TurnChannel10KOhms", @"cmd_TurnAllDriveSignals", @"cmd_TurnChannelDriveSignals", @"cmd_SetPoint01HighPass",
                               @"cmd_SetSubjectGround", @"cmd_SetCurrentSource", @"cmd_SetChannelResets", @"cmd_SetCalibrationSignalFreq",
                               @"cmd_SetChannelResetThreshold", @"cmd_SetBufferedReference", @"cmd_SetOscillatorGate", @"cmd_SetReference10KOhms",
                               @"cmd_SetReferenceDriveSignal", @"cmd_SetEllipticalFilter", @"cmd_SetNotchFilter", @"cmd_SetMaster",
                               @"cmd_SetPower", @"cmd_Reset", @"cmd_SetWaveShape", @"cmd_SetCalibrationSignalRange",
                               @"cmd_SetDrivenCommon", @"cmd_SetCalibrationSignalAmplitude", /*@"cmd_SetAnalogOutput",*/ @"cmd_SetDigitalOutputData",
                               @"cmd_SetDigitalInOutDirection", /*@"cmd_IQAmpData",*/ @"cmd_GetStartTime", @"cmd_GetCurrentTime",
                               @"cmd_GetCurrentDrift", /*@"cmd_SetFilterAndDecimate", @"cmd_SetDecimatedRate",*/ @"cmd_SetMRIPulseInfo",
                               @"cmd_SetPIBChannelGain", @"cmd_SetCOM10KOhms", @"cmd_SetCOMDriveSignal", @"cmd_SetCalibrationControl",
                               @"cmd_TurnChannelZeroOhms", @"cmd_TurnAllZeroOhms", @"cmd_SetPhoticStimSequence", @"cmd_GetPhysioConnectionStatus",
                               @"cmd_SetADCDynamicRange", /*@"cmd_SetNativeRate",*/ @"cmd_GetAmpDetails", @"cmd_GetAmpStatus",
                               @"cmd_DefaultAcquisitionState", @"cmd_DefaultSignalGeneration", @"cmd_NumberOfAmps", @"cmd_NumberOfActiveAmps", nil];
    
    // Populate the sample rate list arrays.
    //
    // Important note: If you change the order / members here, please update the method: setSamplingRate.
    //
    self->na300SamplingRateList_ = [[NSArray alloc ] initWithObjects:@"20,000", @"1,000", @"500", @"250", nil];
    self->na400SamplingRateList_ = [[NSArray alloc ] initWithObjects:@"8,000", @"4,000", @"2,000", @"1,000", @"500", @"250", nil];
    self->na410SamplingRateList_ = [[NSArray alloc ] initWithObjects:@"20,000", @"1,000", @"500", @"250", nil];
    
    self.currentSamplingRateValue = 1000;
    self.isRecording = NO;
    self.isRunning = NO;
    
    // Set the current MFF directory path to the user's desktop.
    [self->filePath_ setStringValue:[NSHomeDirectory() stringByAppendingString:@"/Desktop"]];
    
}

-(void)dealloc {
    
    [self freeResources];
    
    [super dealloc];
    
}

- (IBAction)connect:(id)sender {
    
    bool success = false;
    
    // For the sake of simplicity, we'll use the button state to determine whether we should
    // attempt to disconnect or connect.
    if ([[self->connectButton_ title] isEqualToString:@"Connect"]) {
        
        // Get the IP address of the amplifier.
        NSString *ipAddress = [self->ipAddress_ stringValue];
        
        // Check the IP address before attempting to connect.
        if ( [self isValidIPAddress:ipAddress] == YES) {
            
            // Create a connection prefs instance. The defaults are fine except for the server address.
            static AS_Network_Types::ConnPrefsRef connPrefsRef = AS_Network_Types::createConnPrefs();
            
            if ((connPrefsRef != NULL) &&
                (self->sdkWrapper_ != NULL) &&
                (self->sdkWrapper_->client != NULL)) {
                
                // First delete the default server address.
                delete connPrefsRef->serverAddress;
                
                // Allocate appropriately for the new address.
                connPrefsRef->serverAddress = new char[[ipAddress length] + 1];
                strcpy(connPrefsRef->serverAddress, [ipAddress UTF8String]);
                
                // Now attempt the connection.
                if (self->sdkWrapper_->client->connect(connPrefsRef, true, 20) == AS_Network_Types::ste_OK) {
                    
                    // We will only consider this a successful connection if there is an amplifer attached to
                    // the Amp Server.
                    // Check to see we have an amplifier to connect to.
                    if(self->sdkWrapper_->client->getNumberOfAmps() > 0 ) {
                     
                        // Obtain the amplifier information.
                        //
                        // Note: We will assume the amplifer is at id 0 (as will be the case throughout this example).
                        // For NA400 amplifiers, this is ALWAYS the case, and for NA300 it is usually so.
                        self->sdkWrapper_->ampInfo = self->sdkWrapper_->client->getAmpInfo(0);
                        
                        
                        // Set the UI to the appropriate amplifer values (via the AmpPropertiesTableDelegate).
                        if ( self->sdkWrapper_->ampInfo.amplifierType ==  AS_Network_Types::naNA300) {
                            self->ampPropertiesTableDelegate_.ampType = @"NA300";
                            
                            // Populate the command list appropriately.
                            [self->commandList_ removeAllItems];
                            [self->commandList_ addItemsWithTitles:self->na300CommandList_];
                            
                            // Populate the sample rate list appropriately.
                            [self->samplingRateList_ removeAllItems];
                            [self->samplingRateList_ addItemsWithTitles:self->na300SamplingRateList_];
                            
                        } else if ( self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA400 ) {
                            self->ampPropertiesTableDelegate_.ampType = @"NA400";
                            
                            // Populate the command list appropriately.
                            [self->commandList_ removeAllItems];
                            [self->commandList_ addItemsWithTitles:self->na400CommandList_];
                            
                            // Populate the sample rate list appropriately.
                            [self->samplingRateList_ removeAllItems];
                            [self->samplingRateList_ addItemsWithTitles:self->na400SamplingRateList_];
                            
                        } else if ( self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA410 ) {
                            self->ampPropertiesTableDelegate_.ampType = @"NA410";
                            
                            // Populate the command list appropriately.
                            [self->commandList_ removeAllItems];
                            // Note, 400 for the command list is ok here since the supported 400 and 410 commands
                            // are the same, though the 400 and 410 might react differently in the case of command
                            // sampling rates.
                            [self->commandList_ addItemsWithTitles:self->na400CommandList_];
                            
                            // Populate the sample rate list appropriately.
                            [self->samplingRateList_ removeAllItems];
                            [self->samplingRateList_ addItemsWithTitles:self->na410SamplingRateList_];
                            
                        }
                        
                        // Enable the appropriate items.
                        [self->setSamplingRate_ setEnabled:YES];
                        [self->samplingRateList_ setEnabled:YES];
                        [self->forceMFFSamplingRate setEnabled:YES];
                        
                        [self->commandList_ setEnabled:YES];
                        [self->commandChannel_ setEnabled:YES];
                        [self->commandValue_ setEnabled:YES];
                        [self->sendCommand_ setEnabled:YES];
                        
                        if ( self->sdkWrapper_->ampInfo.packetType == AS_Network_Types::pkType1 ) {
                            self->ampPropertiesTableDelegate_.ampPacketType = @"Packet 1";
                        } else if  ( self->sdkWrapper_->ampInfo.packetType == AS_Network_Types::pkType2 ) {
                            self->ampPropertiesTableDelegate_.ampPacketType = @"Packet 2";
                        }
                        
                        self->ampPropertiesTableDelegate_.ampSerialNumber = [NSString stringWithCString:self->sdkWrapper_->ampInfo.serialNumber.c_str() encoding:NSUTF8StringEncoding];
                        self->ampPropertiesTableDelegate_.ampSystemVersion = [NSString stringWithCString:self->sdkWrapper_->ampInfo.ampSystemVersion.c_str() encoding:NSUTF8StringEncoding];
                        self->ampPropertiesTableDelegate_.ampNumberOfChannels = [NSString stringWithFormat:@"%d", self->sdkWrapper_->ampInfo.numberOfChannels];
                        
                        // We are done setting amplifier properties, reload the UI.
                        [self->ampPropertiesTable_ reloadData];
                        
                        // Now add a data stream observer.
                        self->sdkWrapper_->dataStreamObserver = new DataStreamObserver(self->sdkWrapper_);
                        self->sdkWrapper_->client->addDataStreamObserver(self->sdkWrapper_->dataStreamObserver, 0, NULL);
                        
                        success = true;
                        
                    } else {
                        [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- No amplifier."];
                    }
                    
                } else {
                    [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- Please ensure that your IP Address is correct."];
                }
                
            } else {
                [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- Internal error."];
            }
            
        } else {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- Invalid IP address format."];
        }
        
        if (success == true) {
            [self->connectButton_ setTitle:@"Disconnect"];
            [self->startStopButton_ setEnabled:YES];
        }
        
    } else if ([[self->connectButton_ title] isEqualToString:@"Disconnect"]) {
        
        // If we are running, stop first.
        if (self.isRunning == YES) {
            [self stopAmp];
        }
        
        // Attempt to disconnect.
        if ((self->sdkWrapper_ != NULL) &&
            (self->sdkWrapper_->client != NULL)) {
            
            if (self->sdkWrapper_->client->disconnect() == AS_Network_Types::ste_OK) {
                
                // Reset the amplifier properties in the UI.
                self->ampPropertiesTableDelegate_.ampType =  @"unknown";
                self->ampPropertiesTableDelegate_.ampPacketType =  @"unknown";
                self->ampPropertiesTableDelegate_.ampSerialNumber =  @"unknown";
                self->ampPropertiesTableDelegate_.ampNumberOfChannels =  @"unknown";
                [self->ampPropertiesTable_ reloadData];
                
                RELEASE(self->sdkWrapper_->dataStreamObserver);
                
                success = true;
            } else {
                [self alert:NSInformationalAlertStyle withMessage:@"Unable to disconnect- reason unknown."];
            }
            
        } else {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to disconnect- Internal error."];
        }
        
        if (success == true) {
            [self->connectButton_ setTitle:@"Connect"];
            
            [self->startStopButton_ setEnabled:NO];
            
            [self->setSamplingRate_ setEnabled:NO];
            [self->samplingRateList_ removeAllItems];
            [self->samplingRateList_ setEnabled:NO];
            [self->forceMFFSamplingRate setEnabled:NO];
            
            [self->commandList_ setEnabled:NO];
            [self->commandList_ removeAllItems];
            [self->commandChannel_ setEnabled:NO];
            [self->commandValue_ setEnabled:NO];
            [self->sendCommand_ setEnabled:NO];
        }
        
    } else {
        // Some sort of wierd state which we should never get into...
    }

}

- (IBAction)startStop:(id)sender {
    
    if ([[self->startStopButton_ title] isEqualToString:@"Start"]) {
        
        if ([self startAmp] != YES) {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to start amp."];
        }
        
    } else if ([[self->startStopButton_ title] isEqualToString:@"Stop"]) {
        
        if ([self stopAmp] != YES) {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to stop amp."];
        }
        
    } else {
        // Some sort of wierd state which we should never get into...
    }
    
}

- (IBAction)setSamplingRate:(id)sender {
    
    int samplingRate = 0;
    
    if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA300) {
        
        switch ([self->samplingRateList_ indexOfSelectedItem]) {
            case 0:
                samplingRate = 20000;
                break;
            case 1:
                samplingRate = 1000;
                break;
            case 2:
                samplingRate = 500;
                break;
            case 3:
                samplingRate = 250;
                break;
            default:
                break;
        }
        
    } else if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA400) {
        
        switch ([self->samplingRateList_ indexOfSelectedItem]) {
            case 0:
                samplingRate = 8000;
                break;
            case 1:
                samplingRate = 4000;
                break;
            case 2:
                samplingRate = 2000;
                break;
            case 3:
                samplingRate = 1000;
                break;
            case 4:
                samplingRate = 500;
                break;
            case 5:
                samplingRate = 250;
                break;
            default:
                break;
        }
        
    } else if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA410) {
        
        switch ([self->samplingRateList_ indexOfSelectedItem]) {
            case 0:
                samplingRate = 20000;
                break;
            case 1:
                samplingRate = 1000;
                break;
            case 2:
                samplingRate = 500;
                break;
            case 3:
                samplingRate = 250;
                break;
            default:
                break;
        }
        
    }
    
    [self sendSamplingRate:samplingRate];
    
}

- (IBAction)sendCommand:(id)sender {
    
    NSRunLoop* currentRunLoop = [NSRunLoop currentRunLoop];
    
    if (self->sdkWrapper_->client != NULL) {
        
        // Build the command we need to send.
        NSString *command = [self->commandList_ titleOfSelectedItem];
        NSString *channel = [self->commandChannel_ stringValue];
        NSString *commandValue = [self->commandValue_ stringValue];
        
        if (channel == nil ||
            ([channel length] == 0)) {
            channel = @"-1";
        }
        
        if (commandValue == nil ||
            ([commandValue length] == 0)) {
            commandValue = @"-1";
        }
        
        NSString *commandToSend = [NSString stringWithFormat:@"(sendCommand %@ 0 %@ %@)", command, channel, commandValue];
        [self log:@"\ninfo: --- Send Command ---\n"];
        [self log:[NSString stringWithFormat:@"sending command: %@...\n", commandToSend]];
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        AS_ReturnValue *commandReturn = self->sdkWrapper_->client->sendCommand([commandToSend UTF8String]);
        [self log:@"Command result:\n"];
        
        if (commandReturn != NULL) {
            [self log:[NSString stringWithFormat:@"%s", commandReturn->getValue().c_str()]];
        } else {
            [self log:@"error: no command result.\n"];
        }
        
        [self log:@"info: --- End Send Command ---\n"];
        
        
    } else {
        [self log:@"error: could not send command, no client available.\n"];
    }
    
}

- (IBAction)recordOnOff:(id)sender {
    
    if ([[self->recordButton_ title] isEqualToString:@"Start Recording"]) {
        
        if ([self startRecording] != YES) {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to start recording."];
        }
        
    } else if ([[self->recordButton_ title] isEqualToString:@"Stop Recording"]) {
        
        if ([self stopRecording] != YES) {
            [self alert:NSInformationalAlertStyle withMessage:@"Unable to stop recording."];
        }
        
    } else {
        // Some sort of wierd state which we should never get into...
    }
    
}

- (IBAction)setFilePath:(id)sender {
    
    NSOpenPanel* openPanel = [NSOpenPanel openPanel];
    
    // Set various desired properties.
    [openPanel setCanChooseFiles:NO];
    [openPanel setCanChooseDirectories:YES];
    [openPanel setAllowsMultipleSelection:NO];
    
    // Change default prompt.
    [openPanel setPrompt:@"Select File Path"];
    
    if ( [openPanel runModal] == NSFileHandlingPanelOKButton ) {
        
        // There should only be one since we disabled multiple selection.
        if ([openPanel.URLs count] > 0) {
            [self->filePath_ setStringValue:[[openPanel.URLs objectAtIndex:0] path]];
        }
    }
    
}

- (void)freeResources {
    
    NSLog(@"Freeing all resources in the application controller (we are probably quitting)...");
    
    // Release the client layer.
    if (self->sdkWrapper_ != NULL) {
        if (self->sdkWrapper_->client != NULL) {
            self->sdkWrapper_->client->disconnect();
        }
        RELEASE(self->sdkWrapper_->client);
        
        // Stop the runloop and release it.
        self->sdkWrapper_->egiRunLoop->stopRunLoop();
        RELEASE(self->sdkWrapper_->egiRunLoop);
        
        // Cleanup the buffer.
        RELEASE(self->sdkWrapper_->ampBuffer);
        RELEASE(self->sdkWrapper_->ampBufferOpts);
        
        delete self->sdkWrapper_;
        self->sdkWrapper_ = NULL;
    }
    
}

- (IBAction)quit:(id)sender {
    
    // If we are running, stop first.
    if (self.isRunning == YES) {
        [self stopAmp];
    }
    
    [NSApp terminate:self];
    
}


- (BOOL) startAmp {
    
    BOOL rVal = NO;
    
    if ((self->sdkWrapper_ != NULL) &&
        (self->sdkWrapper_->client != NULL)) {

        NSRunLoop* currentRunLoop = [NSRunLoop currentRunLoop];
        
        [self log:@"info: sending power on command...\n"];
        self->sdkWrapper_->client->sendCommand(0, "cmd_SetPower",-1,1);
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self log:@"info: sending decimation rate command...\n"];
        [self sendSamplingRate:self.currentSamplingRateValue];
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self log:@"info: sending cmd_DefaultAcquisitionState command...\n"];
        self->sdkWrapper_->client->sendCommand(0, "cmd_DefaultAcquisitionState",-1,-1);
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self log:@"info: sending start on command...\n"];
        self->sdkWrapper_->client->sendCommand(0, "cmd_Start",-1,-1);
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self->startStopButton_ setTitle:@"Stop"];
        self.isRunning = YES;
        
        [self->recordButton_ setEnabled:YES];
        
        rVal = YES;
        
    } else {
        [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- Internal error."];
    }
    
    return rVal;
    
}

- (BOOL) stopAmp {
    
    BOOL rVal = NO;
    
    if ((self->sdkWrapper_ != NULL) &&
        (self->sdkWrapper_->client != NULL)) {
        
        // If we are recording, stop recording.
        if (self.isRecording == YES) {
            [self stopRecording];
        }
        
        NSRunLoop* currentRunLoop = [NSRunLoop currentRunLoop];
        
        [self log:@"info: sending stop on command...\n"];
        self->sdkWrapper_->client->sendCommand(0, "cmd_Stop",-1,-1);
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self log:@"info: sending power off command...\n"];
        self->sdkWrapper_->client->sendCommand(0, "cmd_SetPower",-1,0);
        [currentRunLoop runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1]];
        
        [self->startStopButton_ setTitle:@"Start"];
        self.isRunning = NO;
        
        [self->recordButton_ setEnabled:NO];
        
        rVal = YES;
        
    } else {
        [self alert:NSInformationalAlertStyle withMessage:@"Unable to connect- Internal error."];
    }
    
    return rVal;
    
}

- (BOOL)startRecording {
    
    BOOL rVal = NO;
    
    // Obtain the MFF file URI.
    NSString *mffFilePath = [self->filePath_ stringValue];
    NSString *mffFileName = [self->fileName_ stringValue];
    
    std::string mffFileURI = "";
    if (mffFileName != nil) {
        
        if (mffFilePath != nil) {
            mffFileURI = [[NSString stringWithFormat:@"%@/%@", mffFilePath, mffFileName] UTF8String];
        } else {
            mffFileURI = [mffFileName UTF8String];
        }
    }
    
    // Todo:
    // Put a few checks in here...
    
    if ((sdkWrapper_ != NULL) &&
        (sdkWrapper_->dataStreamObserver != NULL)) {
        
        sdkWrapper_->dataStreamObserver->setRecordingState(true);
        
        // If the sampling rate is above 1000s/s, check to see if we want to force a
        // rate of 1000s/s regardless. This will enable current versions of Net Station to
        // be able to review the file.
        
        int samplingRateToUse = self->currentSamplingRateValue_;
        if ((self->currentSamplingRateValue_ > 1000) &&
            ([self->forceMFFSamplingRate state] == NSOnState)) {
            samplingRateToUse = 1000;
        }
        
        self->sdkWrapper_->mffWriter = new MFFWriter(self->sdkWrapper_->ampInfo, self->sdkWrapper_->ampBuffer,
                                                     mffFileURI, samplingRateToUse, self);
        
        
        self->sdkWrapper_->mffWriter->setInterval(1000000);
        self->sdkWrapper_->mffWriter->setRepeats(false);
        self->sdkWrapper_->egiRunLoop->addTask(self->sdkWrapper_->mffWriter);
        
        [self->setSamplingRate_ setEnabled:NO];
        [self->samplingRateList_ setEnabled:NO];
        [self->forceMFFSamplingRate setEnabled:NO];
        
        [self->setFilePathButton_ setEnabled:NO];
        [self->filePath_ setEnabled:NO];
        [self->fileName_ setEnabled:NO];
        
        [self->recordingInProgressIndicator_ startAnimation:self];
        [self->recordButton_ setTitle:@"Stop Recording"];
        self.isRecording = YES;
        
        rVal = YES;
    }
    
    return rVal;
    
}

- (BOOL)stopRecording {
    
    BOOL rVal = NO;
    
    if ((sdkWrapper_ != NULL) &&
        (sdkWrapper_->dataStreamObserver != NULL) &&
        (self->sdkWrapper_->mffWriter != NULL)) {
        
        sdkWrapper_->dataStreamObserver->setRecordingState(false);
        
        self->sdkWrapper_->mffWriter->stopRecording();
        RELEASE(self->sdkWrapper_->mffWriter);
        
        [self->setSamplingRate_ setEnabled:YES];
        [self->samplingRateList_ setEnabled:YES];
        [self->forceMFFSamplingRate setEnabled:YES];
        
        [self->setFilePathButton_ setEnabled:YES];
        [self->filePath_ setEnabled:YES];
        [self->fileName_ setEnabled:YES];
        
        [self->recordingInProgressIndicator_ stopAnimation:self];
        [self->recordButton_ setTitle:@"Start Recording"];
        self.isRecording = NO;
        
        rVal = YES;
    }
    
    return rVal;
    
}

- (BOOL)sendSamplingRate: (int)samplingRate {
    
    BOOL rVal = NO;
    
    if ((self->sdkWrapper_ != NULL) &&
        self->sdkWrapper_->client != NULL) {
        
        AS_ReturnValue *commandReturn1 = NULL;
        AS_ReturnValue *commandReturn2 = NULL;
        
        if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA300) {
            
            switch (samplingRate) {
                case 20000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetFilterAndDecimate 0 0 0)");
                    [currentSamplingRate_ setStringValue:@"20,000"];
                    self.currentSamplingRateValue = 20000;
                    break;
                case 1000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetFilterAndDecimate 0 0 1)");
                    commandReturn2 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 1000)");
                    [currentSamplingRate_ setStringValue:@"1,000"];
                    self.currentSamplingRateValue = 1000;
                    break;
                case 500:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetFilterAndDecimate 0 0 1)");
                    commandReturn2 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 500)");
                    [currentSamplingRate_ setStringValue:@"500"];
                    self.currentSamplingRateValue = 500;
                    break;
                case 250:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetFilterAndDecimate 0 0 1)");
                    commandReturn2 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 250)");
                    [currentSamplingRate_ setStringValue:@"250"];
                    self.currentSamplingRateValue = 250;
                    break;
                default:
                    break;
            }
            
        } else if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA400) {
            
            switch (samplingRate) {
                case 8000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetNativeRate 0 0 8000)");
                    [currentSamplingRate_ setStringValue:@"8,000"];
                    self.currentSamplingRateValue = 8000;
                    break;
                case 4000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetNativeRate 0 0 4000)");
                    [currentSamplingRate_ setStringValue:@"4,000"];
                    self.currentSamplingRateValue = 4000;
                    break;
                case 2000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetNativeRate 0 0 2000)");
                    [currentSamplingRate_ setStringValue:@"2,000"];
                    self.currentSamplingRateValue = 2000;
                    break;
                case 1000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 1000)");
                    [currentSamplingRate_ setStringValue:@"1,000"];
                    self.currentSamplingRateValue = 1000;
                    break;
                case 500:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 500)");
                    [currentSamplingRate_ setStringValue:@"500"];
                    self.currentSamplingRateValue = 500;
                    break;
                case 250:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 250)");
                    [currentSamplingRate_ setStringValue:@"250"];
                    self.currentSamplingRateValue = 250;
                    break;
                default:
                    break;
            }
            
        } else if (self->sdkWrapper_->ampInfo.amplifierType == AS_Network_Types::naNA410) {
            
            switch (samplingRate) {
                case 20000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetNativeRate 0 0 20000)");
                    [currentSamplingRate_ setStringValue:@"20,000"];
                    self.currentSamplingRateValue = 20000;
                    break;
                case 1000:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 1000)");
                    [currentSamplingRate_ setStringValue:@"1,000"];
                    self.currentSamplingRateValue = 1000;
                    break;
                case 500:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 500)");
                    [currentSamplingRate_ setStringValue:@"500"];
                    self.currentSamplingRateValue = 500;
                    break;
                case 250:
                    commandReturn1 = self->sdkWrapper_->client->sendCommand("(sendCommand cmd_SetDecimatedRate 0 0 250)");
                    [currentSamplingRate_ setStringValue:@"250"];
                    self.currentSamplingRateValue = 250;
                    break;
                default:
                    break;
            }
            
        }
        
        // Push any output to the log.
        if (commandReturn1 != NULL) {
            [self log:[NSString stringWithFormat:@"info: sample rate change: %s", commandReturn1->getValue().c_str()]];
            rVal = YES;
        }
        
        if (commandReturn2 != NULL) {
            [self log:[NSString stringWithFormat:@"info: sample rate change: %s", commandReturn2->getValue().c_str()]];
            rVal = YES;
        }
        
        // Todo:
        // Check the command returns to ensure an error did not occur before updating the current sampling rate.
    }
    
    return rVal;
    
}

-(void)alert:(NSAlertStyle)alertType withMessage:(NSString *)message {
    
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setAlertStyle :alertType];
    [alert setMessageText:message];
    
    [alert runModal];
    [alert release];
    
}

- (BOOL)isValidIPAddress:(NSString *)ipAddress {
    struct in_addr  dst;
    struct in6_addr dst6;
    const char      *utf8 = [ipAddress UTF8String];
    
    if(inet_pton(AF_INET, utf8, &dst) == 1)
        return YES;
    if(inet_pton(AF_INET6, utf8, &dst6) == 1)
        return YES;
    
    return NO;
}

-(void)log:(NSString *)message {
    
    [self->logOutput_ setEditable:YES];
    [self->logOutput_ replaceCharactersInRange:NSMakeRange([[self->logOutput_ string] length], 0) withString:message];
    [self->logOutput_ scrollRangeToVisible:NSMakeRange([[self->logOutput_ string] length], 0)];
    [self->logOutput_ setEditable:NO];
    
}

- (void)logToInterface:(NSString *)message {
    
    [self performSelectorOnMainThread:@selector(log:) withObject:message waitUntilDone:NO];
    
}

- (void)error:(NSString *)message {
    
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setAlertStyle:NSInformationalAlertStyle];
    [alert setMessageText:message];
    
    [alert runModal];
    [alert release];
    
}

- (void)errorToInterface:(NSString *)message{
    
    [self performSelectorOnMainThread:@selector(error:) withObject:message waitUntilDone:NO];
    
}

// Tests.
- (IBAction)layoutTest:(id)sender {
    
    // Try getting some layout URIs.
    std::cout << "debug: looking for: Geodesic Sensor Net 64 2.0.xml coordinates.." << std::endl;
    std::cout << "debug: got: " << MFFFileWriterUtilities::getLayoutURIForNetType(AS_Network_Types::GSN64_2_0, "CoordinateLayouts") << std::endl;
    
    std::cout << "debug: looking for: HydroCel GSN 32 1.0 sensor layout..." << std::endl;
    std::cout << "debug: got: " << MFFFileWriterUtilities::getLayoutURIForNetType(AS_Network_Types::HCGSN32_1_0, "SensorLayouts") << std::endl;
    
}

- (IBAction)fileTest:(id)sender {
    
}

@end
