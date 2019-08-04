
/**@file
 *  Amp Server Pro SDK types header.
 *  @author Robert Bell
 *  @date 1/1/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  This class groups Amp Server Pro SDK types, and associated helper functions.
 */

#ifndef AS_Network_Types_DEFINED
#define AS_Network_Types_DEFINED

#include "EGIObject.h"

#include <netinet/in.h>
#include <pthread.h>
#include <climits>
#include <unistd.h>

//####################################
// Useful defines.
//####################################

//######
// Detecting byte ordering.
//######

#if CHAR_BIT != 8
#error "error: unsupported char size"
#endif

enum
{
    O32_LITTLE_ENDIAN = 0x03020100ul,
    O32_BIG_ENDIAN = 0x00010203ul,
    O32_PDP_ENDIAN = 0x01000302ul
};

static const union { unsigned char bytes[4]; uint32_t value; } o32_host_order =
{ { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

//######
// End - Detecting byte ordering.
//######

//####################################
// End - Useful defines.
//####################################

/**
 *  Amp Server Pro SDK's types header.
 *  @author Robert Bell.
 *  @remarks
 *  This class groups Amp Server Pro SDK types and associated helper functions.
 *
 *  ------<br>
 *  Update (001): 2009-04-06: Added cmd_StopListeningToAmp and cmd_StopReceivingNotifications.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2009-08-19: Added support for AS_Network_Types::cmd_SetMRIPulseInfo.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2009-10-20: Added support for AS_Network_Types::cmd_NumberOfActiveAmps.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (004): 2009-11-13: CommandType value parameter is now int64_t.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (005): 2012-01-29: Added cmd_SetMRIPulseInfo and cmd_SetPIBChannelGain command types.
 *  Note that cmd_SetMRIPulseInfo was added earlier, however the update for it was not added here.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (006): 2012-05-07: Added ECI related types type.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (007): 2012-07-23: Added useful endian tests.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (008): 2012-08-02: Added a new ECI command (NewQuery). This command uses a 1-byte architecture
 *  type, and is clearer on the processor specification.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (009): 2013-11-19: Added support for NA400 COM commands.<br>
 *  ------<br>
 */
class AS_Network_Types : virtual public EGIBase::EGIObject{
	
public:
	
	// It is unforntunate that forward declaring of enums is not portable. :-(
    
    /**
	 *  A typed enum representing an architecture type.
	 *  
	 *  Notes:
	 *
	 *  Used for indicating architecture types (primarily for helping to determine
     *  byte ordering).<br>
	 */
	typedef enum{
        
        ARCH_TYPE_UNKNOWN,  /** */
		ARCH_TYPE_I386,     /** */
        ARCH_TYPE_X86_64,   /** */
        ARCH_TYPE_PPC,      /** */
		
	}ArchType;
	
	/**
	 *  A typed enum representing protocol type (loosely based on netinet/in.h)
	 */
	typedef enum{
        
		AS_IPPROTO_TCP = 0,                            /**< TCP communication */
		AS_IPPROTO_UDP = 1,                            /**< UDP communication */
		AS_SHARED_MEM  = 2,                            /**< Shared memory */
		AS_NONE = 3,                                   /**< Don't communicate */
        
	}AS_Protocol;
	
	/**
	 *  Amp Server Detection Preferences.
	 *  Amp Server detection preferences simply specifies the network location
	 *  at which to search for Amp Server. The convenience function for creating
	 *  an instance of AS_Network_Types::DetPrefs will fill in the default values listed.
	 */
	typedef struct{
        
		/**
		 *  The server address (for example: 10.0.0.71 or myserver.myplace.net).
		 *  Default: 127.0.0.1<br>
		 *  Only numeric addresses are supported.
		 */
		char *serverAddress;
		
		/**
		 *  The port.
		 *  Default: 9880
		 */
		in_port_t port;
        
	}DetPrefs, *DetPrefsRef;
    
    /**
     *  Low-level connection structure. This is usually wrapped by a connection
     *  object (ConnectionOject).
     */
    typedef struct AS_TCP_Port_Connection{
        
        // Used when references to the port handler are needed.
		void *portHandler;
        
		// Socket information.
        socklen_t socklen;
		struct sockaddr_in sockaddr;
		
        // The connection ID and handle to the actual connection.
        int32_t connectionID;
		int connection;
		
        // If using standard IO, these will be available.
        FILE *fin;
		FILE *fout;
		
        // Flags to indicate the state of reading and writing on the connection.
        // A value of true means the connection can be used for that purpose, and
        // false means it cannot.
        bool read;
		bool write;
        
	} *AS_TCP_Port_ConnectionRef;
	
	/**
	 * Connection Preferences.
	 * Connection preferences are used to specify the network interaction between Amp Server
	 * and its clients. The convenience function for creating an instance of AS_Network_Types::ConnPrefs
	 * will fill in the default values listed.
	 */
	typedef struct{
		/**
		 *  The server address, for example: 10.0.0.71 or myserver.myplace.net.
		 *  Default: 127.0.0.1<br>
		 *  Only numeric addresses are supported.
		 */
		char *serverAddress;
		
		/**
		 *  The port to use for command exchange.
		 *  Default: 9877
		 */
		in_port_t commandPort;
		
		/**
		 *  The network protocol to use for command exchange.
		 *  Default: AS_Network_Types::AS_IPPROTO_TCP<br>
		 *  See AS_Network_Types::Protocol for valid options<br>
		 *  Only AS_Network_Types::AS_IPPROTO_TCP is supported.
		 */
		AS_Network_Types::AS_Protocol commandProtocol;
		
		/**
		 *  The port to use for notification exchange.
		 *  Default: 9878
		 */
		in_port_t notificationPort;
		
		/**
		 *  The network protocol to use for notification exchange.
		 *  Default: AS_Network_Types::AS_IPPROTO_TCP<br>
		 *  See AS_Network_Types::Protocol for valid options<br>
		 *  Beta 1.0 release notes: Only AS_Network_Types::AS_IPPROTO_TCP is supported.
		 */
		AS_Network_Types::AS_Protocol notificationProtocol;
		
		/**
		 *  The port to use for data streaming.
		 *  Default: 9879
		 */
		in_port_t streamPort;
		
		/**
		 *  The network protocol to use for data streaming.
		 *  Default: AS_Network_Types::AS_IPPROTO_TCP<br>
		 *  See AS_Network_Types::Protocol for valid options<br>
		 *  Beta 1.0 release notes: Only AS_Network_Types::AS_IPPROTO_TCP is supported.
		 */
		AS_Network_Types::AS_Protocol streamProtocol;
		
	}ConnPrefs, *ConnPrefsRef;
	
	/**
	 *  Command.
	 *  <i>Format:</i><br>
	 *  {<br>
	 *     int64_t id;           // Used to identify the command.<br>
	 *     int64_t command;      // The command itself (specified in the AmpServerCommand enum).<br>
	 *     int64_t ampID;        // The amplifier for which this command is intended (if applicable).<br>
	 *     unsigned char[4072];  // The optional argument (will be different for each command).<br>
	 *  }<br>
	 */
	typedef char *Command;
	
	/**
	 *  Notification.
	 *  <i>Format:</i><br>
	 *  {<br>
	 *     int64_t id;           // Used to identify the notification.<br>
	 *     int64_t notification; // The notification itself (specified in the Notification enum).<br>
	 *     int64_t ampID;        // The ampID associated with this notification (if appropriate).<br>
	 *     unsigned char[4080];  // The optional argument (will be different for each notification).<br>
	 *  }<br>
	 */
	typedef char *Notification;
    
    /**
     *  Amplifier Types.
     *
     *  Notes:
     *
     *  1) Given that all clients are distributing these fourcc types as simple char strings,
     *  is is probably better to move these to char strings in the future.
     */
    typedef enum {
        
        naUnknown,   // Amplifer type is unknown.
        naNA200,     // Net Amps 200 amplifer *Obsolete*
        naNA300,     // Net Amps 300 amplifer
        naNA400,     // Net Amps 400 amplifer
        naNA410      // Net Amps 410 amplifer
        
    } AmplifierType;

    /**
     *  Packet Format Types.
     */
    typedef enum {
      
      pkUnknown,   // Amplifer type is unknown.
      pkType1,     // Packet format 1.
      pkType2      // Packet format 2.
      
    } PacketType;
    
    /**
     *  Amplifer and Packet Type Information.
     *
     *  Notes:
     *
     *  1) This is definitely NOT a complete type, but it is useful for the present. Obviously, there is more information
     *  present for each amplifier, but it is sufficient for current usage.
     */
    typedef struct {
        PacketType packetType;
        AmplifierType amplifierType;
        std::string serialNumber;
        std::string ampSystemVersion;
        int16_t numberOfChannels;
    } AmpInfo;
    
#pragma pack(1)
    
	/**
	 *  AmpDataPacket Header.
	 */
	typedef struct{
		
		/**
		 *  The ampID associated with this data packet (if appropriate).
		 */
		int64_t ampID;
		
		/**
		 *  Specifies the length of the data field.
		 */
		uint64_t length;
		
	}AmpDataPacketHeader;
    
#pragma pack()
	
	/**
	 *  AmpDataPacket.
	 *  <i>Format:</i><br>
	 *  {<br>
	 *     AmpDataPacketHeader;<br>
	 *     unsigned char[length(specified in the length field above)];<br>
	 *  }<br>
	 */
	typedef char *AmpDataPacket;

#pragma pack(1)
    
    /**
     *  Packet Format 1 Used by the NA300 and NA400 prior to and including
     *  version 1.4.3 of the NA400 firmware.).
     *
     *  <b>Notes:</b><br>
     *  &nbsp; 1) Used by the NA300 and NA400 prior to and including
     *  version 1.4.3 of the NA400 firmware.<br>
     *
     *  &nbsp; 2) If this is raw data from the amplifier, it will be in analog to digital units
     *  and this will need to be converted to microvolts. Please see the Amp Server Pro SDK documentation
     *  for details.<br>
     *
     *  &nbsp; 3) Data in this packet format is always in network byte order.<br>
     */
    typedef struct
    {
        uint32_t  header[8];    // DINS (Digital Inputs) 1-8/9-16 at bytes 24/25; net type at byte 26.
        float     eeg[256];     // EEG Data.
        float     pib[7];       // PIB data.
        float     unused1;      // N/A
        float     ref;          // The reference channel.
        float     com;          // The common channel.
        float     unused2;      // N/A
        float     padding[13];  // N/A
    } PacketFormat1;
    
    /**
     *  Packet Format 2 (Used NA400 in firmware versions AFTER 1.4.3.).
     *
     *  <b>Notes:</b><br>
     *  &nbsp; 1) If this is raw data from the amplifier, it will be in analog to digital units
     *  and this will need to be converted to microvolts. Please see the Amp Server Pro SDK documentation
     *  for details.<br>
     *
     *  &nbsp; 2) If this is raw data from the amplifier, it will be in analog to digital units
     *  and this will need to be converted to microvolts. Please see the Amp Server Pro SDK documentation
     *  for details.<br>
     *
     *  &nbsp; 3) Data in this packet format is always in little endian byte order.<br>
     */
    typedef struct
    {
        uint8_t digitalInputs;
        uint8_t status;
        uint8_t batteryLevel[ 3 ];
        uint8_t temperature[ 3 ];
        uint8_t sp02;
        uint8_t heartRate[ 2 ];
    } PacketFormat2_PIB_AUX;
    
    typedef struct
    {
        uint16_t                digitalInputs;
        uint8_t                 tr;
        PacketFormat2_PIB_AUX   pib1_aux;
        PacketFormat2_PIB_AUX   pib2_aux;
        uint64_t                packetCounter;
        uint64_t                timeStamp;
        uint8_t                 netCode;
        uint8_t                 reserved[ 38 ];
        int32_t                 eegData[ 256 ];
        uint32_t                auxData[ 3 ];
        uint32_t                refMonitor;
        uint32_t                comMonitor;
        uint32_t                driveMonitor;
        uint32_t                diagnosticsChannel;
        uint32_t                currentSense;
        int32_t                pib1_Data[ 16 ];
        int32_t                pib2_Data[ 16 ];
    } PacketFormat2;
    
#pragma pack()
	
	/**
	 *  A typed enum representing Amp Server or an amplifier command.
	 *  
	 *  Command Notes:
	 *  The channel and value fields must be placed consecutively in the optional argument potion
	 *  of the amplifier command. Note that both are assumed present (even if one is N/A), meaning that
	 *  if the command is N/A, the value cannot be placed directly after the ampID, but must occupy
	 *  its usual position after the amplifier ID.
	 * 
	 *  All commands sent should use this enum list.<br>
	 *  <i>IMPORTANT</i>: Do not substitute the value (i.e., use value x instead of cmd_X)
	 *  as the values themselves are subject to change.<br>
	 */
	typedef enum{
		cmd_None = 0,							/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_Start = 1,							/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_Stop = 2,							/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_SetLowpass = 3,						/**< int64_t amplifier ID, int16_t filter x 10 */
		cmd_TurnAll10KOhms = 4,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (0 = Off, 1 = On) */
		cmd_TurnChannel10KOhms = 5,				/**< int64_t amplifier ID, int16_t channel (channels 0-287), int64_t value (0 = Off, 1 = On) */
		cmd_TurnAllDriveSignals	= 6,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (0 = Off, 1 = On) */
		cmd_TurnChannelDriveSignals = 7,		/**< int64_t amplifier ID, int16_t channel (channels 0-287), int64_t value (0 = Off, 1 = On) */
		cmd_SetPoint01HighPass = 8,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetSubjectGround = 9,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t state (0 = Off, 1 = On) */
		cmd_SetCurrentSource = 10,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetChannelResets = 11,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetCalibrationSignalFreq = 12,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (frequency) */
		cmd_SetChannelResetThreshold = 13,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (percent) */
		cmd_SetBufferedReference = 14,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (0 = On, 1 = Off) */
		cmd_SetOscillatorGate = 15,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetReference10KOhms = 16,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetReferenceDriveSignal = 17,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetEllipticalFilter	= 18,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (filter setting) */
		cmd_SetNotchFilter	= 19,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (filter setting) */
		cmd_SetMaster = 20,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t (0 = slave, 1 = master) */
		cmd_SetPower = 21,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t (0 = Off, 1 = On) */
		cmd_Reset = 22,							/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_SetWaveShape = 23,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t (0 = Off (default sine wave), 1 = square wave, 2 = triangle wave) */
		cmd_SetCalibrationSignalRange = 24,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t (0 = low range, 1 = high range) <br>*/
		cmd_SetDrivenCommon = 25,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t state (0 = Off, 1 = On) */
		cmd_SetCalibrationSignalAmplitude = 26,	/**< int64_t amplifier ID, int16_t channel (set by default to channel 8), int64_t value (12 bit range) */
		cmd_SetAnalogOutput = 27,				/**< int64_t amplifier ID, int16_t channel (), int64_t value (12 bit range) */
		cmd_SetDigitalOutputData = 28,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (bit mask of DIO line to be set) */
		cmd_SetDigitalInOutDirection = 29,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (bit mask indicating the direction status of the I/O lines) */
		cmd_IQAmpData = 30,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GetStartTime = 31,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GetCurrentTime = 32,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GetCurrentDrift = 33,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_SetFilterAndDecimate = 34,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (0 = Off, 1 = On) */
		cmd_SetDecimatedRate = 35,				/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetMRIPulseInfo = 36,				/**< int64_t amplifier ID, int16_t channel, int64_t value (high byte = DIN line (0 = detection off), low byte = DIN value) */
		cmd_SetPIBChannelGain = 37,				/**< int64_t amplifier ID, int16_t channel, int64_t value (valid gains: 2, 20, 200, 2000) <p> */
		
		// New commands added for the NA 400 amplifiers. Note that the explanations above will need to change as well
		// since NA300 and NA400 amplifiers often need to handle commands in different ways.
		cmd_SetCOM10KOhms = 38,                 /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetCOMDriveSignal = 39,             /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value */
		cmd_SetCalibrationControl = 40,         /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_TurnChannelZeroOhms = 41,           /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_TurnAllZeroOhms = 42,               /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_UpdateFPGA = 43,                    /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (FPGA version code) */
		cmd_SetPhoticStimSequence = 44,         /**< int64_t amplifier ID, int16_t channel (N/A), char *value */
		cmd_GetPhysioConnectionStatus = 45,     /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_SetADCDynamicRange = 46,            /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value ( valid values: 400, 666 ) */
		cmd_SetNativeRate = 47,                 /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value ( valid values: 500, 1000, 2000, 4000, 8000, 16000 ) */
		
		// Amp Status.
		cmd_GetAmpDetails = 50,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GetAmpStatus = 51,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) <p>*/
		
		// Extended Amp Configuration Settings.		
		cmd_DefaultAcquisitionState = 75,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_DefaultSignalGeneration = 76,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) <p>*/
		
		// Amp Server
		cmd_NumberOfAmps = 100,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_NumberOfActiveAmps = 101,			/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_ListenToAmp  = 102,					/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
		cmd_StopListeningToAmp  = 103,			/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
		cmd_ReceiveNotifications  = 104,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_StopReceivingNotifications  = 105,	/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_SelectChannelsForAmp  = 106,		/**< Not Supported */
		cmd_GetStatus  = 107,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_InstallEGINA300TestAmp = 108,		/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_Exit = 199,							/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */		

		//GTEN
		cmd_GTENSetTrain         = 225,         /**< int64_t amplifier ID, int16_t channel (N/A), char *value */
		cmd_GTENStartTrain       = 226,         /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GTENAbortTrain       = 227,         /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GTENGetStatus        = 228,         /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GTENGetTimeRemaining = 229,          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		cmd_GTENResetAlarm       = 230          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
		
	}CommandType;
	
	/**
	 *  A typed enum representing a notification.
	 *  
	 *  Notification Notes:
	 *
	 *  All notifications sent should use this enum list.<br>
	 *  <i>IMPORTANT</i>: Do not substitute the value (i.e., use value x instead of ntn_X)
	 *  as the values themselves are subject to change.<br>
	 */
	typedef enum{
	  ntn_None = 0,							/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpInstalled = 1,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpRemoved = 2,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpPowerOn = 3,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpPowerOff = 4,					/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpStarted = 5,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpStopped = 6,						/**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_PhysioConnectionStatus = 7,         /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENSetTrainSucceeded = 8,          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENSetTrainFailed = 9,             /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENStartTrainSucceeded = 10,       /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENStartTrainFailed = 11,          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENAbortTrainSucceeded = 12,       /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENAbortTrainFailed = 13,          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENGetStatus = 14,                 /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENResetAlarmSucceeded = 15,       /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  ntn_GTENResetAlarmFailed = 16,          /**< int64_t amplifier ID, int16_t channel (N/A), int64_t value (N/A) */
	  
	  // Amp Server
	  ntn_AmpServerAvailable = 100,			/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpServerNotAvailable = 101,		/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  ntn_ConnectedToAmpServer = 102,			/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  ntn_DisonnectedFromAmpServer = 103,		/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  ntn_AmpServerExiting = 199				/**< int64_t amplifier ID (N/A), int16_t channel (N/A), int64_t value (N/A) */
	  
	}NotificationType;
	
	/**
	 *  A typed enum representing status.
	 */
	typedef enum{
		ste_OK = 0,                                 /**< Normal or correct state */
		ste_ERROR = 1                               /**< Error state */
	}Status;
    
    // Net codes
    typedef enum {
        GSN64_2_0,      //  GSN 64
        GSN128_2_0,     //  GSN 128
        GSN256_2_0,     //  GSN 256
        
        HCGSN32_1_0,    //  HGSN 32
        HCGSN64_1_0,    //  HGSN 64
        HCGSN128_1_0,   //  HGSN 128
        HCGSN256_1_0,   //  HGSN 256
        
        MCGSN32_1_0,    //  MGSN 32
        MCGSN64_1_0,    //  MGSN 64
        MCGSN128_1_0,   //  MGSN 128
        MCGSN256_1_0,   //  MGSN 256
        
        AMP_SAMPLE,     //  EAmpSample displayable channels (internal use only)
        TestConnector = 14,
        NoNet = 15,     //  net not connected
        Unknown = 0xFF  //  Unknown or net not connected
    }NetCode;
    
    /**
	 *  ECICommandType.
	 *  
     *  Notes:<br>
     *
     *  A 1-byte command type used for basic ECI communication.
     *
	 */
    typedef uint8_t ECICommandType;
    
    /**
	 *  ECICommandType.
	 *  
     *  Notes:<br>
     *
     *  A 1-byte machine type used for basic ECI communication.
     *
	 */
    typedef uint8_t ECIMachineType;
    
    // ECI command types.
    static const ECICommandType  eci_Query =                    'Q';
    static const ECICommandType  eci_NewQuery =                 'Y';
    static const ECICommandType  eci_Exit =                     'X';
    static const ECICommandType  eci_BeginRecording =           'B';
    static const ECICommandType  eci_EndRecording =             'E';
    static const ECICommandType  eci_Attention =                'A';
    static const ECICommandType  eci_ClockSynch =               'T';
    static const ECICommandType  eci_NTPClockSynch =            'N';
    static const ECICommandType  eci_NTPReturnClockSynch =      'S';
    static const ECICommandType  eci_EventData =                'D';
    static const ECICommandType  eci_OK =                       'Z';
    static const ECICommandType  eci_Failure =                  'F';
    static const ECICommandType  eci_NoRecordingDeviceFailure = 'R';
    static const ECICommandType  eci_Identify =                 'I';
    
    // ECI machine types.
    static const ECIMachineType  eci_unknown =      'u';
    static const ECIMachineType  eci_i386 =         'i';
    static const ECIMachineType  eci_x86_64 =       'x';
    static const ECIMachineType  eci_ppc =          'p';
    
    // ECI version number.
    static const uint8_t eci_version = 1;
    
    /**
	 *  EGI key types.
     *
     *  Notes:
     *
     *  1) eciTypeShortInteger and eciTypeLongInteger originate in AEDataModel.h from the CoreServices
     *  framework. They are not used directy here as this is more portable.
     *
     *  2) Given that all clients are distributing these fourcc types as simple char strings,
     *  is is probably better to move these to char strings in the future.
	 */
    typedef enum {
        
        eciKeyUnknownType       = 'unkn',
        eciKeyEGISPackedType    = 'egis',
        eciTypeBoolean          = 'bool',
        eciTypeChar             = 'TEXT',
        eciTypeShortInteger     = 'shor',
        eciTypeLongInteger      = 'long',
        eciTypeShortFloat       = 'sing',
        eciTypeLongFloat        = 'doub',
        eciTypeString           = 'strn'
        
    } EGIKeyType;
    
    /**
	 *  Legacy ECI machine types.
     *
     *  Notes:
     *
     *  1) Given that all clients are distributing these fourcc types as simple char strings,
     *  is is probably better to move these to char strings in the future.
	 */
    typedef enum {
        
        eciMachineType_Mac		= 'MAC-',	// Big-endian
        eciMachineType_Unix		= 'UNIX',	// Big-endian
        eciMachineType_Intel	= 'NTEL'	// Little-endian
        
    } LegacyECIMachineType;
    
    /**
	 *  Another legacy ECI type for packed EGIS.
     *
     *  Notes:
     *
     *  1) Some explanation of what this type is would be nice.
     *
	 */
    typedef struct {
        
        short	cellNumber;
        short	observationNumber;
        short	positionNumber;
        short	keyValue;
        
    } PackedEGISInfo;
    
#pragma pack(1)
    
	/**
	 *  ECI Communication Packet.
     *
     *  Note: This is pragma-ed to 1, but this structure is not actually sent, rather
     *  it is assembled from the connection as a convenience.
	 */
	typedef struct{
		
		/**
		 *  The command associated with this data packet.
		 */
		ECICommandType command;
        
        /**
		 *  The architecture associated with this data packet.
		 */
		ArchType architectureType;
        
        /**
         * Whether this platform needs to swap bytes.
         */
        bool swapBytes;
		
		/**
		 *  Specifies the length of the data field. This can be zero if there is no
         *  associated data.
		 */
		uint64_t dataLength;
        
        /**
         *  Data.
         */
        char *data;
		
	} ECICommunicationPacket;
    
#pragma pack()
	
	//####################################
	//Constructor(s).
	//#################################### 	
	
	/**
	 *  Default contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Thread safety is off.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Types();
	
	/**
	 *  Contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; threadSafe: true = thread safe; false = not thread safe<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Types(bool threadSafe);
	
	//####################################
	//End - Constructor(s).
	//####################################
	
	//####################################
	//Destructor.
	//####################################
	
	/**
	 *  Destructor
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual ~AS_Network_Types();
	
	//####################################
	//End - Destructor.
	//####################################
	
	/**
	 *  Gets the class ID for this class.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); This method should always be overridden
	 *  in derived classes, and instances should return CLASS_NAME::classID. This allows
	 *  for identification of objects in the runtime environment.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; ClassID: The class ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual EGIBase::ClassID getClassID(){return AS_Network_Types::classID;}
	
	/**
	 *  The toString method.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; std::string: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual std::string toString(){return EGIBase::EGIObject::toString() + "::AS_Network_Types";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Command Size.
	 *  The size of an amplifier command.
	 */
    static const uint64_t COMMAND_SIZE = 1048576;
    
    /**
	 *  Command Return Size.
	 *  The size of an amplifier return command.
	 */
    static const uint64_t COMMAND_RETURN_SIZE = 4096;
	
	/**
	 *  Notification Size.
	 *  The size of a notification.
	 */
	static const uint64_t NOTIFICATION_SIZE = 4096;
	
	/**
	 *  NA300 Sample Size.
	 *  The size of an NA300 sample.<br>
	 */
	static const uint64_t NA300_SAMPLE_SIZE = 1152;
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ANTY';
	
	//####################################
	//End - Class variables.
	//####################################
	
	//####################################
	//Class methods.
	//####################################
	
	/**
	 *  Creates a DetPrefs with default values.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Callee owned allocation.<br>
	 *  &nbsp; 2) Address is a string literal.<br>
	 *  &nbsp; 3) See definition for defaults.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::DetPrefsRef: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::DetPrefsRef createDetPrefs();
	
	/**
	 *  Creates a ConnPrefs with default values.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Callee owned allocation.<br>
	 *  &nbsp; 2) Address is a string literal.<br>
	 *  &nbsp; 3) See definition for defaults.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::ConnPrefsRef: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::ConnPrefsRef createConnPrefs();
	
	/**
	 *  @name Command Convenience Functions.
	 *  A collection of functions to help handle AS_Network_Types::Command.
	 */
	//@{
	
	/**
	 *  Creates a Command.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Callee owned allocation.<br>
	 *  &nbsp; 2) Command is of size AS_Network_Types::COMMAND_SIZE.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command type.<br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Command: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::Command createCommand(AS_Network_Types::CommandType command, int64_t ampID, void *userRef);
	
	/**
	 *  Sets the command ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  &nbsp; commandID: The command ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setCommandID(AS_Network_Types::Command command, int64_t commandID);
	
	/**
	 *  Gets the command ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The command ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static int64_t getCommandID(AS_Network_Types::Command command);
	
	/**
	 *  Sets the command type.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  &nbsp; commandType: The command type.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setCommandType(AS_Network_Types::Command command, AS_Network_Types::CommandType commandType);
	
	/**
	 *  Gets the command type.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Command: The command type.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::CommandType getCommandType(AS_Network_Types::Command command);
	
	/**
	 *  Sets the command amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  &nbsp; ampID: The command amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setCommandAmpID(AS_Network_Types::Command command, int64_t ampID);
	
	/**
	 *  Gets the command amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; command: The command.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The command amplifier ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static int64_t getCommandAmpID(AS_Network_Types::Command command);
	
	//@}
	
	/**
	 *  @name Notification Convenience Functions.
	 *  A collection of functions to help handle AS_Network_Types::Notification.
	 */
	//@{
	
	/**
	 *  Creates a Notification.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Callee owned allocation.<br>
	 *  &nbsp; 2) Notification is of size AS_Network_Types::NOTIFICATION_SIZE.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification type.<br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Notification: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::Notification createNotification(AS_Network_Types::NotificationType notification, int64_t ampID, void *userRef);
	
	/**
	 *  Creates a Notification with a return value.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Callee owned allocation.<br>
	 *  &nbsp; 2) Notification is of size AS_Network_Types::NOTIFICATION_SIZE.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification type.<br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  &nbsp; value: Notification value.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Notification: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
    static AS_Network_Types::Notification createNotification(AS_Network_Types::NotificationType notificationType, int64_t ampID, const char *value, void *userRef);
    
	/**
	 *  Sets the notification ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  &nbsp; notificationID: The notification ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setNotificationID(AS_Network_Types::Notification notification, int64_t notificationID);
	
	/**
	 *  Gets the notification ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The notification ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static int64_t getNotificationID(AS_Network_Types::Notification notification);
	
	/**
	 *  Sets the notification type.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  &nbsp; notificationType: The notification type.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setNotificationType(AS_Network_Types::Notification notification, AS_Network_Types::NotificationType notificationType);
	
	/**
	 *  Gets the notification type.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Notification: The notification type.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::NotificationType getNotificationType(AS_Network_Types::Notification notification);
    
	/**
	 *  Gets the notification data/value.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  &nbsp; result: char array (size = 4047) to store the notification data/value in.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
    static void getNotificationData(AS_Network_Types::Notification notification, char *result);
    
	/**
	 *  Sets the notification data/value.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  &nbsp; data: The notification data/value to set.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
    static void setNotificationData(AS_Network_Types::Notification notification, const char *data);
    
	/**
	 *  Determines if the notification has a meaningful value.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; bool: true if the notification includes a meaningful value.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
    static bool notificationHasData(AS_Network_Types::Notification notification);
	
	/**
	 *  Sets the notification amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  &nbsp; ampID: The notification amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setNotificationAmpID(AS_Network_Types::Notification notification, int64_t ampID);
	
	/**
	 *  Gets the notification amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; notification: The notification.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The notification amplifier ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static int64_t getNotificationAmpID(AS_Network_Types::Notification notification);
	
	//@}
	
    /**
	 *  @name AmpDataPacket Convenience Functions.
	 *  A collection of functions to help handle AS_Network_Types::AmpDataPacket.
	 */
	//@{
	
	/**
	 *  Creates an AmpDataPacket.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Callee owned allocation.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  &nbsp; length: Length of the data in bytes.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::AmpDataPacket: Callee owned<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static AS_Network_Types::AmpDataPacket createAmpDataPacket(int64_t ampID, uint64_t length, void *userRef);
	
	/**
	 *  Sets the amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampDataPacket: The amplifier data packet.<br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setAmpDataPacketAmpID(AS_Network_Types::AmpDataPacket ampDataPacket, int64_t ampID);
	
	/**
	 *  Gets the amplifier ID.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampDataPacket: The amplifier data packet.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static int64_t getAmpDataPacketAmpID(AS_Network_Types::AmpDataPacket ampDataPacket);
	
	/**
	 *  Sets the amplifier data packet length.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampDataPacket: The amplifier data packet.<br>
	 *  &nbsp; length: The length.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static void setAmpDataPacketLength(AS_Network_Types::AmpDataPacket ampDataPacket, uint64_t length);
	
	/**
	 *  Gets the amplifier data packet length.
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampDataPacket: The amplifier data packet.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; uint64_t: The amplifier data packet length.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static uint64_t getAmpDataPacketLength(AS_Network_Types::AmpDataPacket ampDataPacket);
	
	//@}
	
	//####################################
	//End - Class methods.
	//####################################
	
	
protected:
	
	//####################################
	//Inheritence tree variables.
	//####################################
	//####################################
	//End - Inheritence tree variables.
	//####################################
	
private:
	
	/**
	 *  Copy constructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Types(const AS_Network_Types& source);
	
	/**
	 *  Assignment.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types&: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Types& operator=(const AS_Network_Types& source);
	
	//####################################
	//Non-Inheritence tree variables.
	//####################################
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_Network_Types_DEFINED
