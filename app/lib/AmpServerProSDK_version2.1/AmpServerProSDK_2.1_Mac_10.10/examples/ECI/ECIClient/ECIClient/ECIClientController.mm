
/*
 *  ECIClientController.cpp
 *  @author Robert Bell
 *  @date 08/10/2012
 *  @remarks
 *  Copyright 2012, 2015 EGI. All rights reserved.
 * 
 *  2015_06_18 changes:
 *    - "Send ECI command sequence" includes Keys using all data types.
 *    - eci_Query & eci_NewQuery check for success or failure
 */

#import "ECIClientController.h"

// EGI Base.
#include "EGIObject.h"
#include "EGIXStringWrap.h"

// MFF
#include "Event.h"
#include "Key.h"
#include "MFFUtils.h"

// Amp Server Pro SDK.
#include "AS_Network_Types.h"
#include "ConnectionFactory.h"
#include "ConnectionObject.h"

// Application support.
#include "ECIEvent.h"

#include <iostream>

using namespace EGIBase;
using namespace com::egi::services::mff::api;
using namespace com::egi::services::mff::util;

@interface ECIClientController ( hidden )

- (void)handleECIServerResponse:(AS_Network_Types::ECICommandType) eciReturnCommand
                withSendCommand:(NSString *)sendCommand;

@end

@implementation ECIClientController

@synthesize connectDisconnect=connectDisconnect_;
@synthesize eciServerAddress=eciServerAddress_;
@synthesize eciServerPort=eciServerPort_;
@synthesize simpleECICommand=simpleECICommand_;
@synthesize output=output_;

static const char *gDefaultServerAddress = "127.0.0.1";

- (id)init {
    
    self = [super init];
    
    if (self) {
        
        self->connection_ = NULL;
        
        // Set to defaults for address and port number.
        self->eciServerCharStringAddress = new char[strlen(gDefaultServerAddress) + 1];
        strcpy(self->eciServerCharStringAddress, gDefaultServerAddress);
        self->eciServerPortNumber_ = -1;
        
    }
    
    return self;
}

- (void)dealloc {
    
    [super dealloc];
    
    RELEASE(self->connection_);
    delete [] self->eciServerCharStringAddress;
    
}

- (void)awakeFromNib {
    
    [self log:@"ECIClient: version: 1.0 date: 2015_06_18\n"];
    
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    [self log:@"ECIClient: version: 1.0 date: 2015_06_18\n"];
    
}

- (IBAction)connectToServer:(id)sender {
    
    if ( self->connection_ == NULL ) {
        
        
        // Obtain the server address and port number from the interface.
        
        // Address
        const char *theServerAddress = [[self->eciServerAddress_ stringValue] cStringUsingEncoding:[NSString defaultCStringEncoding]];
        
        delete [] self->eciServerCharStringAddress;
        self->eciServerCharStringAddress = new char[strlen(theServerAddress) + 1];
        strcpy(self->eciServerCharStringAddress, theServerAddress);
        
        // Port number.
        self->eciServerPortNumber_ = [self->eciServerPort_ intValue];
        
        // Start the server.        
        if ( (self->eciServerCharStringAddress != NULL ) && (self->eciServerPortNumber_ >= 2048) && (self->eciServerPortNumber_ < 100000) ) {
            
            self->connection_ = ConnectionFactory::getGenericClientConnectionObject(self->eciServerCharStringAddress, self->eciServerPortNumber_);
            
            [self log:@"ECIClient: connected to server\n"];
            
        } else {
            
            [self log:@"ECIClient: error: allowed port range is: 2048 -> 10000\n"];
            self->eciServerPortNumber_ = -1;
            
        }
        
        // Update UI to indicate that the server is running.
        [self->connectDisconnect_ setTitle:@"Disconnect"];
        
    } else {
        
        [self log:@"ECIClient: error: disconnection not implemented, please close application to disconnect\n"];
        
    }
    
    
    
    [self log:@"ECIClient: - (IBAction)startStopECIClient:(id)sender\n"];
    
}

- (IBAction)sendSimpleECICommand:(id)sender{
    
    if ( self->connection_ != NULL ) {
        
        AS_Network_Types::ECICommandType eciSendCommand = 0;
        AS_Network_Types::ECICommandType eciReturnCommand = 0;
        
        // Get the simple ECI command.
        NSString *selectedECICommand = [self->simpleECICommand_ titleOfSelectedItem];
        
        if (  [selectedECICommand isEqualToString:@"eci_Query"] == YES ) {
            
            // This is the legacy method for conveying machine type.  It uses a four
            // character code.  Note that these are no longer descriptive of the actual
            // machine type or byte order.  NTEL, MAC+, etc., are not generally known to
            // be big or little endian.
            eciSendCommand = AS_Network_Types::eci_Query;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // Now send the machine type.
            const char *machineType = "NTEL";
            self->connection_->fwrite(machineType, 4, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Query"];
            
            
        } else if ( [selectedECICommand isEqualToString:@"eci_NewQuery"] == YES ) {
            
            // This is the new query for machine type and map specifically to the chip
            // used by the OS.
            eciSendCommand = AS_Network_Types::eci_NewQuery;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // Now send the new machine type.
            AS_Network_Types::ECIMachineType machineType = AS_Network_Types::eci_x86_64;
            self->connection_->fwrite(&machineType, 1, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_NewQuery"];


            
        } else if ( [selectedECICommand isEqualToString:@"eci_Exit"] == YES ) {
            
            // This ends the communications session.  The server can assume that
            // communications will no longer be sent after sending back the acknowledgement.
            eciSendCommand = AS_Network_Types::eci_Exit;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Exit"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_BeginRecording"] == YES ) {
            
            // Tells the server application to start recording.
            eciSendCommand = AS_Network_Types::eci_BeginRecording;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_BeginRecording"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_EndRecording"] == YES ) {
            
            // This tells the server application to stop recording.
            eciSendCommand = AS_Network_Types::eci_EndRecording;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_EndRecording"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_Attention"] == YES ) {
            
            // This command is sent in advance of the chosen sync command.  It provides
            // the server indication that the sync command is about to be sent so it knows
            // not to change anything on the server side that might affect synchronization.
            eciSendCommand = AS_Network_Types::eci_Attention;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            //[self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Attention"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_ClockSynch"] == YES ) {
            
            // This command indicates that no synchronization mechanism is being used other than
            // the initial alignment of clock offsets, after which, drift may occur.  Note that this
            // command can be sent multiple times during the session to realign the clocks as needed
            // to correct for drift.  The time sent is the current relative time in milliseconds from
            // the start of the client's clock.  The server will compare this with the current relative
            // time of its clock in milliseconds to determine the offset between clocks.  This method
            // may not be as accurate depending on server software and hardware.  Not recommended for
            // use with Net Station 4.5.6 or earlier.
            eciSendCommand = AS_Network_Types::eci_ClockSynch;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // create example timestamp
            int32_t timestamp = 37000; // milliseconds
            self->connection_->fwrite(&timestamp, 4, 1);

            
            // The return should be one byte.
            self->connection_->fread((char*)&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_ClockSynch"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_NTPClockSynch"] == YES ) {
            
            // This indicates that the client is also an NTP client and has a clock that is
            // synchronized with the server clock (and in the case of Net Station, it is
            // synchronized with the EEG being recorded.  The time sent below represents
            // the absolute start time of the clients clock in NTP time format.  The server
            // should compare this value with the absolute time of start of its clock to
            // determine the offset between clocks.  Sending this command more than once
            // will have no effect as the start times of each clock does not change.
            eciSendCommand = AS_Network_Types::eci_NTPClockSynch;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // create example NTP timestamp
            uint64_t timestamp = (3605338800 << 32)  +  123456789; // NTP time
            char* time_parts = reinterpret_cast<char *>(&timestamp); // send second 4 bytes first, then first
            self->connection_->fwrite(time_parts + 4, 4, 1);
            self->connection_->fwrite(time_parts, 4, 1);
            
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_NTPClockSynch"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_NTPReturnClockSynch"] == YES ) {
            
            // This command is identical to the eci_NTPClockSynch command except that the server
            // returns the start time of its clock in NTP form as well.  This allows the client to
            // adjust its clock or timestamps to already be relative to the server's clock sparing
            // the server the responsibility to adjust incoming timestamps in events.
            eciSendCommand = AS_Network_Types::eci_NTPReturnClockSynch;
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            
            // create example NTP timestamp
            uint64_t timestamp = (3605338800 << 32)  +  321654987; // NTP time
            char* time_parts = reinterpret_cast<char *>(&timestamp); // send second 4 bytes first, then first
            self->connection_->fwrite(time_parts + 4, 4, 1);
            self->connection_->fwrite(time_parts, 4, 1);
            
            // The return should be 8 byte NTP time from server.
            uint64_t returntime;
            
            self->connection_->fread(&returntime, 8, 1);
            
            // Report the return value to the client view
            [self log:[NSString stringWithFormat:@"ECIClient: sent: %llu got: %llull\n",timestamp,  returntime]];
            //[self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_NTPReturnClockSynch"];
            
        } else if ( [selectedECICommand isEqualToString:@"eci_EventData"] == YES ) {
            
            // This commands sends data as a timestamp event.  In all cases, timestamps will be 32
            // bit integers representing relative time from some absolute start time.  For normal
            // (eci_ClockSynch) and NTP (eci_NTPClockSynch) sync methods, the timestamps for these
            // events will be relative the the start time of the client's clock.  For NTP with return
            // time (eci_NTPReturnClockSynch), these relative times will already be converted so they
            // are relative to the servers clock.
            
            // All 'D' or eci_EventData commands have a common general form.  There are several higher
            // level constructs for events of this type as are used in conveying information for ERP
            // studies.  This example demonstrates a standard 'Trial Event' as are sent, for example,
            // by E-Prime in its NetStation_SendTrialEvent command.
            eciSendCommand = AS_Network_Types::eci_EventData;
            Event *event = new Event();
            std::vector<Key*> *keyset = new std::vector<Key*>();
            Key *onekey = new Key();
            
            // Create an event with a key
            event->setLabel("Event Label");
            event->setCode("EVLB");
            event->setBeginTime("2014-04-01T12:34:45.000000+07:00");
            event->setDescription("A test event");
            event->setDuration(1000000);
            
            onekey->setDescription("A Test Key");
            onekey->setKeyCode("TEST");
            onekey->setDataType("long");
            onekey->setData("3");
            
            keyset->push_back(onekey);
            event->setKeys(keyset);
            
            int timezone = 0;
            std::string starttime("2014-04-01T12:24:45.000000+07:00");
            
            // create a start time 10 minutes earlier than event (600 seconds)
            uint64_t basetime = MFFUtils::mffDateTimeToMicroseconds(starttime, timezone);
            
            ECIEvent::EncodedEvent *encodedEvent = ECIEvent::encodeEvent(event, false, basetime,timezone);
            
            self->connection_->fwrite(&eciSendCommand, 1, 1);
            self->connection_->fwrite(&(encodedEvent->dataLength), 2, 1);
            self->connection_->fwrite(encodedEvent->data,1,encodedEvent->dataLength);
            // The return should be one byte.
            self->connection_->fread(&eciReturnCommand, 1, 1);
            
            [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_EventData"];
            
        } else {
            
            [self log:@"ECIClient: error: ECI command not implemented yet\n"];
            
        }
        
    } else {
        
        [self log:@"ECIClient: error: no connection to server\n"];
        
    }
    
    
}

- (IBAction)sendECICommandSequence:(id)sender{
    
    if ( self->connection_ != NULL ) {
        
        AS_Network_Types::ECICommandType eciSendCommand = 0;
        AS_Network_Types::ECICommandType eciReturnCommand = 0;
        
        
        
        // Query
        
        // Use the original query type for this sequence.  This assumes an Intel
        // platform.
        eciSendCommand = AS_Network_Types::eci_Query;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        
        // Now send the machine type.
        const char *machineType = "NTEL";
        self->connection_->fwrite(machineType, 4, 1);
        
        // The return should be one byte followed by the ECI version number.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Query"];
        
        
        // Wait between commands
        sleep(2);
        
        // Attention
        
        // Indicate the the server that a time sync method is about to be called.  This
        // might indicate, for example, that the server should not make any changes that
        // would affect the sync process or timing.
        eciSendCommand = AS_Network_Types::eci_Attention;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Attention"];
        // No response to attention command.
        
        // Wait between commands
        sleep(2);
        
        
        // NTP Sync
        
        // Use the NTP sync method.  Both the client and the server have millisecond timers that
        // start at different absolute times.  By comparing the absolute times, the offset between
        // clocks can be determined.  Later when an event is sent, it will have a timestamp in ms
        // relative to the client's clock.  The server can add/subtract the offset to determine the
        // relative time to the server's clock, and then use that to re-create the absolute time.
        eciSendCommand = AS_Network_Types::eci_NTPClockSynch;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        
        // Create example NTP timestamp.
        int timezone = 0;
        
        // This is UNIX time in microseconds.  Here we are modeling the start time of the client
        // clock.  When using NTP, this time should be synced with the NTP clock, but for
        // demonstration purposes, this will be accurate enough.
        //uint64_t unixStartTime = MFFUtils::mffDateTimeToMicroseconds("2014-04-01T12:24:45.000000+07:00", timezone);
        uint64_t	unixStartTime = ([[NSDate date] timeIntervalSince1970])* 1000000;
        std::cout << "start time: " << unixStartTime << std::endl;
        
        // NTP time is 64 bits with the most significant 32 bits representing seconds, and
        // the least significant bits representing a fraction that can be determined by dividing
        // that value by 2^32.  The unix times returned by 'mffDateTimeToMicroseconds' is in microseconds
        // since Jan 1, 1970 while the NTP time is in seconds and fractions of a second since Jan 1, 1900.
        uint64_t ntpStartTime = unixStartTime * 4294.967296 + (2208988800 << 32);  // convert to NTP time for sending to server
        
        char* time_parts = reinterpret_cast<char *>(&ntpStartTime);
        self->connection_->fwrite(time_parts + 4, 4, 1);  // Send seconds first.
        self->connection_->fwrite(time_parts, 4, 1); // Send fractions of a seconds second.
        
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_NTPClockSynch"];
        
        // Wait between commands
        sleep(2);
        
        // Start Recording
        
        // Tells the server application to start recording.
        eciSendCommand = AS_Network_Types::eci_BeginRecording;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_BeginRecording"];
        
        // Wait between commands
        sleep(2);
        
        // Send an Event
        
        // This event happens 10 minutes after the start time sent above.
        eciSendCommand = AS_Network_Types::eci_EventData;
        Event *event = new Event();
        std::vector<Key*> *keyset = new std::vector<Key*>();
        
        /*
         Predefined data type descriptors:
         "bool"
         "short"
         "long"
         "sing"
         "doub"
         "type"
         "TEXT"
         "strn"
         */
        
        Key *boolKey = new Key();
        Key *shortKey = new Key();
        Key *longKey = new Key();
        Key *singleKey = new Key();
        Key *doubleKey = new Key();
        Key *typeKey = new Key();
        Key *textKey = new Key();
        Key *strnkey = new Key();
        
        // Create an event
        event->setLabel("Event Label");
        event->setCode("EVLB");
        
        // create an event time 10 minutes after the start time (600 seconds)
        // Here we will use the system time again to get the timestamp for the event.  Since
        // this is sent in relative time to the server, when used with Net Station, NS will decode
        // it and place it in the event track while the recording is active.
        
        uint64_t unixEventTime = ([[NSDate date] timeIntervalSince1970])* 1000000;
        std::string stringEventTime = MFFUtils::microsecondsToMFFDateTime(unixEventTime);
        std::cout << "event time: " << unixEventTime << std::endl;
        std::cout << "event time relative: " << unixEventTime - unixStartTime << std::endl;
        event->setBeginTime(stringEventTime);
        event->setDescription("A test event");
        event->setDuration(1000000);
        
        // Testing "bool"
        boolKey->setDescription("A Bool Key, true");
        boolKey->setKeyCode("BOOL");
        boolKey->setDataType("bool");
        boolKey->setData("1");
        
        keyset->push_back(boolKey);
        
        // Testing "shor"
        shortKey->setDescription("A Short Test Key, value 32,768");
        shortKey->setKeyCode("SHOR");
        shortKey->setDataType("short");
        shortKey->setData("32768");
        
        keyset->push_back(shortKey);
        
        // Testing "long"
        longKey->setDescription("A Long Key, 2,147,483,648");
        longKey->setKeyCode("LONG");
        longKey->setDataType("long");
        longKey->setData("2147483648");
        
        keyset->push_back(longKey);
        
        // Testing "sing"
        singleKey->setDescription("A Single Key, 3.1415926");
        singleKey->setKeyCode("SING");
        singleKey->setDataType("sing");
        singleKey->setData("3.1415926");
        
        keyset->push_back(singleKey);
        
        // Testing "doub"
        doubleKey->setDescription("A Double Key, 10.149999999999999999653055");
        doubleKey->setKeyCode("DOUB");
        doubleKey->setDataType("doub");
        doubleKey->setData("10.149999999999999999653055");
        
        keyset->push_back(doubleKey);
        
        // Testing "type"
        typeKey->setDescription("A Type Key, Four Character descriptor type");
        typeKey->setKeyCode("TYPE");
        typeKey->setDataType("type");
        typeKey->setData("NTEL");
        
        keyset->push_back(typeKey);
        
        
        // Testing "TEXT"
        textKey->setDescription("A TEXT Key, a sequence of characters.");
        textKey->setKeyCode("TEXT");
        textKey->setDataType("TEXT");
        textKey->setData("This is a sequence of characters.");
        
        keyset->push_back(textKey);
        
        // Testing "strn"
        strnkey->setDescription("A strn Key, a string of characters");
        strnkey->setKeyCode("STRN");
        strnkey->setDataType("strn");
        strnkey->setData("some data in text form");
        
        keyset->push_back(strnkey);
        event->setKeys(keyset);
        
        ECIEvent::EncodedEvent *encodedEvent = ECIEvent::encodeEvent(event, false, unixStartTime,timezone);
        
        
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        self->connection_->fwrite(&(encodedEvent->dataLength), 2, 1);
        self->connection_->fwrite(encodedEvent->data,1,encodedEvent->dataLength);
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_EventData"];
        
        // Wait between commands
        sleep(2);
        
        // Stop recording.
        
        // This tells the server application to stop recording.
        eciSendCommand = AS_Network_Types::eci_EndRecording;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_EndRecording"];
        
        // Wait between commands
        sleep(2);
        
        // Exit.
        
        // We are done.  Tell the server that there will be no further communciations.
        eciSendCommand = AS_Network_Types::eci_Exit;
        self->connection_->fwrite(&eciSendCommand, 1, 1);
        
        // The return should be one byte.
        self->connection_->fread(&eciReturnCommand, 1, 1);
        
        [self handleECIServerResponse:eciReturnCommand withSendCommand:@"eci_Exit"];
        
        
    } else {
        
        [self log:@"ECIClient: error: no connection to server\n"];
        
    }

    
    
}

-(void)log:(NSString *)message {
    
        [self->output_ setEditable:YES];
        [self->output_ replaceCharactersInRange:NSMakeRange([[self->output_ string] length], 0) withString:message];
        [self->output_ scrollRangeToVisible:NSMakeRange([[self->output_ string] length], 0)];
        [self->output_ setEditable:NO];

}


- (void)handleECIServerResponse:(AS_Network_Types::ECICommandType) eciReturnCommand
                withSendCommand:(NSString *)sendCommand{
    
    switch (eciReturnCommand) {
            
        // Response 'Z'
        // Follows any successful command other than the intial query
        case AS_Network_Types::eci_OK:
            
            [self log:[NSString stringWithFormat:@"ECIClient: sent: %@ got: eci_OK\n", sendCommand]];

            break;
        
        // Response 'F' followed by 2 shorts
        // Follows incorrectly contructed or undefined commands or is unable to
        //    comply with the command's instruction. No error numbers are
        //    currently defined
        case AS_Network_Types::eci_Failure:
        {
            // Read in the failure code
            self->connection_->fread(&eciReturnCommand, 2, 1);
            short eciFailure = eciReturnCommand;
            
            // Update the UI
            [self log:[NSString stringWithFormat:@"ECIClient: sent: %@ got: eci_Failure, code: %d\n", sendCommand, eciFailure]];
           
        }
            break;
            
        // Response 'I' followed by a single byte of data
        // The one byte of data indicates the version number of the protocol
        //    currently being supported.
        case AS_Network_Types::eci_Identify:
        {
            // Read in the version number
            self->connection_->fread(&eciReturnCommand, 1, 1);
            int32_t eciVersion = eciReturnCommand;
            
            // Update the UI
            [self log:[NSString stringWithFormat:@"ECIClient: sent: %@ got: eci_Identify, eci version: %d\n", sendCommand, eciVersion]];
            
        }
            break;
            
        default:
            
            // Update the UI
            [self log:[NSString stringWithFormat:@"ECIClient: sent: %@ got: unknown response\n", sendCommand]];
            
            
            break;
    }
    
}

@end

