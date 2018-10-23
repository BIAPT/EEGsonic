
/**@file
 *  Simple Client.
 *  @author Robert Bell
 *  @date 2015/08/28
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 *
 *  This example code does the following:
 *  1) Connects to the Amp Server using the high-level C++ API.
 *  2) Registers itself to receive Amp Server notifications.
 *  3) If an amp is installed:
 *     a) Prints out various information about the installed amplifier.
 *     b) Turns the amp on.
 *     c) Starts the amp.
 *     d) Stops the amp.
 *     e) Turns the amp off.
 *  4) Responds to Amp Server notifications.
 *  5) Registers a data receiver, collects and converts data.
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// EGIBase's utility functions.
#include "UtilityFunctions.h"

// Helper class specific to this example application
#include "DataStreamObserver.h"
#include "NotificationObserver.h"

// Other includes.
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/signal.h>

using namespace EGIBase;
using namespace EGIBase::ObserverPattern;

// These are the default ports for Amp Server.
#define SERVER_COMMAND_PORT 9877
#define SERVER_NOTIFICATION_PORT 9878
#define SERVER_STREAM_PORT 9879

// Some other useful defines.
#define DEFAULT_COLLECTION_DURATOIN 60
#define MAX_COLLECTION_DURATION 600

// Note: The max collection duration is artificial. You can change is to what you
// like. It is only there as a sanity check for the commandline arguments.

// Globals.
static const char *gDefaultIP = "10.10.10.51";
static AS_Network_Client *gClient = NULL;
static DataStreamObserver *gDataStreamObserver = NULL;

// Function definitions.
static void signalCatch(int signo);
static bool runScript(const char *commandScript, bool dummyMode);

/**
 *  Debugging Types.
 *
 *  Note: This is just for ease of use when sending the data observer different debugging modes.
 */
typedef enum {
        
  dbUnknown,
  dbSampleStatistics,
  dbPhysioSamples
        
} DebuggingOutputType;

int main(int argc, const char **args){

  const char *ipaddress = gDefaultIP;
  int collectionDuration = DEFAULT_COLLECTION_DURATOIN;
  const char *commandScript = NULL;

  std::ostringstream usage;
  usage << "usage: " << args[0] << ": -a x.x.x.x (for example, -ipaddress 10.10.10.51)" <<
	  " -t x (where x is a positive integer less than or equal to ("<< MAX_COLLECTION_DURATION << ")" <<
	  " -s scriptfile (where scriptfile is the file name for the script)." << std::endl;

  // Register the signal handler so we can shut down cleanly on ctrl-c, etc.
  if ( signal(SIGPIPE, signalCatch) == SIG_ERR ) {
    std::cerr << "error: can't catch SIGPIPE" << std::endl;
    exit(1);
  }

  if ( signal(SIGINT, signalCatch) == SIG_ERR ) {
    std::cerr << "error: can't catch SIGINT" << std::endl;
    exit(1);
  }

  // Check arguments for a user defined ip address.
  for (int i=1; i<argc; i++) {

    if (strcmp(args[i], "-a" ) == 0) {
      
      // Check to ensure the next argument is present.
      if ( (i+1) < argc ) {
	
	ipaddress = args[i+1];

	// Note:
	// A sanity check would be appropriate here.

	// Skip the argument just processed.
	i++;

      } else {

	// Error, we need an ip address.
	std::cout << "error: no ip address specified" << std::endl;
	std::cout << usage.str() << std::endl;

	exit(1);

      }

    } else if (strcmp(args[i], "-t" ) == 0) {

      // Check to ensure the next argument is present.
      if ( (i+1) < argc ) {
	
	// Convert argument to an integer.
	collectionDuration = UtilityFunctions::from_char_string<int>(args[i+1], std::dec);
	
	// Ensure we have something reasonable.
	if ((collectionDuration <= 0) ||
	    (collectionDuration > MAX_COLLECTION_DURATION)) {
	  
	  // Error, we need a duration.
	  std::cout << "error: the duration specified is either <=0 or greater than the max (" << MAX_COLLECTION_DURATION<< ")." << std::endl;
	  std::cout << usage.str() << std::endl;
	  
	  exit(1);
	}
	
	// Skip the argument just processed.
	i++;
	
      } else {
	
	// Error, we need a duration.
	std::cout << "error: no duration specified" << std::endl;
	std::cout << usage.str() << std::endl;

	exit(1);

      }

    } if (strcmp(args[i], "-s" ) == 0) {
      
      // Check to ensure the next argument is present.
      if ( (i+1) < argc ) {
	
	commandScript = args[i+1];
	
	// Debug.
	//runScript(commandScript, true);
	//exit(0);

	// Skip the argument just processed.
	i++;

      } else {

	// Error, we need an ip address.
	std::cout << "error: no script file specified" << std::endl;
	std::cout << usage.str() << std::endl;

	exit(1);

      }

    }

  }

  std::cout << std::endl << "------" << std::endl;
  std::cout << "Using the following settings:" << std::endl;
  std::cout << "Amplifier IP Address: " << ipaddress << std::endl;
  std::cout << "Collection duration: " << collectionDuration << std::endl;
  std::cout << "------" << std::endl << std::endl;

  // Pause for a moment to allow the user to see the values
  // being used.
  sleep (3);

  // Create a client object.
  gClient = new AS_Network_Client();

  // Uncomment of you want debugging on!
  ///*
  //gClient->setDebug(true);
  //*/

  // Add an observer to grab notifications.
  // This will enable us to get all notifications from the Amp Server, even those that are
  // not amp specific. It can safely be done before connecting to the Amp Server.
  gClient->addNotificationObserver(new NotificationObserver(), NULL);
  
  // Create a connection prefs instance. The defaults are fine except for the server address, which for
  // this example, we'd like the option to change.
  AS_Network_Types::ConnPrefsRef connPrefsRef = AS_Network_Types::createConnPrefs();
  delete connPrefsRef->serverAddress; // Remove the default.
  connPrefsRef->serverAddress = new char[strlen(ipaddress) + 1];
  strcpy(connPrefsRef->serverAddress, ipaddress);

  // Example: Only connect to the command port. (uncomment if you want to test).
  // By uncommenting, the client will only connect to the command port. Similarly, you could
  // only connect to the stream port if that's all you needed.
  ///*
  //connPrefsRef->notificationProtocol = AS_Network_Types::AS_NONE;
  //connPrefsRef->streamProtocol = AS_Network_Types::AS_NONE;
  //*/

  std::cout << "info: connecting to Amp Server at address: " << ipaddress << "... ";
  if ( gClient->connect(connPrefsRef) == 0 ) {

    // We connected successfully.
    std::cout << "connected" << std::endl;

    // Check to see we have an amplifier to connect to.
    if(gClient->getNumberOfAmps() > 0 ){

      std::cout << "info: amplifer detected" << std::endl;

      // Determine the packet format so that we can pass it to the data observer.
      AS_Network_Types::AmpInfo ampInfo = gClient->getAmpInfo(0);

      // Display the amplifier information.
      std::cout << "info: amplifier serial number: " << ampInfo.serialNumber << std::endl;
      std::cout << "info: number of EEG channels:: " << ampInfo.numberOfChannels << std::endl;

      if ( ampInfo.packetType == AS_Network_Types::pkType1 ) {
	std::cout << "info: amplifier using packet type 1" << std::endl;
      } else if  ( ampInfo.packetType == AS_Network_Types::pkType2 ) {
	std::cout << "info: amplifier using packet type 2" << std::endl;
      } else {
	std::cout << "error: could not deterine amplifer packet type" << std::endl;
	exit(1);
      }

      if ( ampInfo.amplifierType ==  AS_Network_Types::naNA300) {
	std::cout << "info: amplifier type NA300" << std::endl;
      } else if  ( ampInfo.amplifierType == AS_Network_Types::naNA400 ) {
	std::cout << "info: amplifier type NA400" << std::endl;
      } else if  ( ampInfo.amplifierType == AS_Network_Types::naNA410 ) {
	std::cout << "info: amplifier type NA410" << std::endl;
      } else {
	std::cerr << "error: could not deterine amplifer type" << std::endl;
	exit(1);
      }

      // Pause for display.
      sleep(3);

      // Setup the data observer.
      std::cout << "info: adding data observer. Press ctrl-c to exit program during acquisition!" << std::endl;
      sleep(3);
      gDataStreamObserver = new DataStreamObserver(ampInfo);
      gClient->addDataStreamObserver(gDataStreamObserver, 0, NULL);

      // Now startup the amplifier and set it to the default signal generation state.
      // This will set the amplifer to generate sinewaves. There are two commands that are
      // most comonly used:
      //
      // 1) cmd_DefaultAcquisitionState - The actual acquisition state used by Net Station
      // 2) cmd_DefaultSignalGeneration - Often used to test signal output.

      if (commandScript != NULL) {

	runScript(commandScript, false);
	
      } else {
	
	std::cout << "info: sending power on command..." << std::endl;
	gClient->sendCommand(0, "cmd_SetPower",-1,1);
	sleep(2);
	
	std::cout << "info: sending decimation rate command..." << std::endl;
	gClient->sendCommand(0, "cmd_SetDecimatedRate",-1,1000);
	sleep(2);
	
	std::cout << "info: sending cmd_DefaultAcquisitionState command..." << std::endl;
	//gClient->sendCommand(0, "cmd_DefaultSignalGeneration",-1,-1);
	gClient->sendCommand(0, "cmd_DefaultAcquisitionState",-1,-1);
	sleep(2);
	
	std::cout << "info: sending start on command..." << std::endl;
	gClient->sendCommand(0, "cmd_Start",-1,-1);
	sleep(2);
	
	// We will let the amp go for about one minute.
	sleep(collectionDuration);
	
	std::cout << "info: sending stop on command..." << std::endl;
	gClient->sendCommand(0, "cmd_Stop",-1,-1);
	sleep(2);
	
	std::cout << "info: sending power off command..." << std::endl;
	gClient->sendCommand(0, "cmd_SetPower",-1,0);

      }

      // Put this thread to sleep. The main work will occur in the data update thread.
      while(true) {
	std::cout << "info: acquisiton has ended, press ctrl-c to exit." << std::endl;
	sleep(10);
      }

    }

  } else {

    std::cout << "failed" << std::endl;
    exit(1);

  }

  delete [] (connPrefsRef->serverAddress);
  delete connPrefsRef;
  RELEASE(gClient);

  exit(0);

}

static bool runScript(const char *commandScript, bool dummyMode) {

  bool rVal = false;

  // Attempt to open the script file.
  try {
    std::ifstream commandScriptFile(commandScript);
    if( commandScriptFile.is_open() ){
      
      bool exitScript = false;
      std::string line;
      int lineNumber = 1;
      while((! exitScript) && (! UtilityFunctions::safeGetLine(commandScriptFile, line).eof())){

	// Tokenize the line.
	int tokenCount = 0;
	bool printFlag = false;
	bool sendCommandFlag = false;
	std::ostringstream sendCommandString;
	bool sleepFlag = false;
	bool noisySleep = false;
	bool debuggingOutputFlag = false;
	DebuggingOutputType debuggingOutputType = dbUnknown;

	// Debug.
	//std::cout << "processing ling: " << line << std::endl;
	//std::cout << "------" << std::endl;

	// Preprocess to remove comments.
	std::string processedString = line.substr(0,line.find_first_of("#"));

	std::vector<std::string> *tokens = UtilityFunctions::tokenize(processedString);
	for(std::vector<std::string>::iterator itr = tokens->begin();
	    itr != tokens->end();
	    ++itr){

	  std::string token = *itr;
	  
	  if (tokenCount == 0) {
	    if (token == "exit") {
	      exitScript = true;
	      break;
	    } else if (token == "print") {
	      printFlag = true;
	    } else if (token == "sendCommand") {
	      sendCommandFlag = true;
	    } else if (token == "sleep") {
	      sleepFlag = true;
	    } else if (token == "noisySleep") {
	      sleepFlag = true;
	      noisySleep = true;
	    } else if (token == "debuggingOutput") {
	      debuggingOutputFlag = true;
	    } else if (token.compare(0, 1, "#") == 0) {
	      break;
	    } else {
	      // We do not understand the instruction.
	      std::cout << "error: unrecognized script instruction on line " << lineNumber << ": " << token << std::endl;
	      break;
	    }
	  }

	  if (token.compare(0, 1, "#") == 0) {
	    break;
	  } else if (printFlag == true) {
	    
	    if (tokenCount == 1) {
	      std::cout << token;
	    } else if (tokenCount > 1) {
	      std::cout << " " << token;
	    }

	  } if (sendCommandFlag == true) {
	    
	    if (tokenCount == 0) {
	      sendCommandString << "(" << token;
	    } else if ((tokenCount > 0) && (tokenCount < 4)) {
	      sendCommandString << " " << token;
	    } else if (tokenCount == 4) {
	      sendCommandString << " " << token << ")";
	      
	      std::cout << "info: sending command: " << sendCommandString.str() << std::endl;

	      if (dummyMode == false) {
		if ((gClient != NULL)) {
		  gClient->sendCommand(sendCommandString.str());
		} else {
		  std::cout << "error: could not send command because client is not available" << std::endl;
		}
	      }
	      
	      break;
	    }
	  } else if (sleepFlag == true) {
	    if (tokenCount == 1) {
	      std::cout << "info: sleeping for: " << token << "s" << std::endl;

	      int sleepDuration = UtilityFunctions::from_string<int>(token, std::dec);
	      if (noisySleep == true) {
		for (int sleepCount=0; sleepCount<sleepDuration; sleepCount++) {
		  if (sleepCount == 0) {
		    std::cout << "info: sleeping " << sleepCount+1 << "(" << sleepDuration << ")" << std::flush;
		  } else {
		    std::cout << "..." << sleepCount+1 << "(" << sleepDuration << ")" << std::flush;
		  }
		  sleep(1);
		}
		std::cout << std::endl;
	      } else {
		sleep(sleepDuration);
	      }

	    }

	  } else if (debuggingOutputFlag == true) {
	    if (tokenCount == 1) {
	      // Find the debugging mode desired.
	      if (token == "sampleStatistics") {
		debuggingOutputType = dbSampleStatistics;
	      } else if (token == "physioSamples") {
		debuggingOutputType = dbPhysioSamples;
	      }
	    } else if (tokenCount == 2) {

	      if (gDataStreamObserver != NULL ) {

		bool debugFlag = false;
		if (token == "on") {
		  debugFlag = true;
		} else if (token == "off") {
		  debugFlag = false;
		} else {
		  // This is an error. We need the flag to be on or off.
		  std::cout << "error: the error flag must be on or off, for example \"sampleStatistics on\"" << std::endl;
		  break;
		}
		
		// Now try and set the debugging state.
		switch (debuggingOutputType) {
		case dbSampleStatistics:
		  gDataStreamObserver->setSampleStatisticsDebuggingOutput(debugFlag);
		  std::cout << "info: setting sample stastics debugging to " << token << std::endl;
		  break;
		case dbPhysioSamples:
		  gDataStreamObserver->setPhysioDebuggingOutput(debugFlag);
		  std::cout << "info: setting physio sample debugging to " << token << std::endl;
		default:
		  std::cout << "error: unknown debugging output requested" << std::endl;
		  break;
		}
		
	      } else {
		std::cout << "error: could not set debugging mode because no data observer available" << std::endl;
	      }
	      
	    }
	  }
	  
	  tokenCount++;
	}

	// End the line if we are printing.
	if (printFlag == true) {
	  std::cout << std::endl;
	}
	
	// Debug.
	//std::cout << "------" << std::endl;
	
	lineNumber++;
      }
      
    }

  } catch (std::ifstream::failure exp) {
    rVal = false;
  }

  return rVal;

}

static void signalCatch(int signo) {

  if (signo == SIGPIPE) {
    std::cout << "SIGPIPE received" << std::endl;
  } else if (signo == SIGINT) {
    std::cout << "SIGPIPE received" << std::endl;
  }

  RELEASE(gClient);
  exit(0);
}
