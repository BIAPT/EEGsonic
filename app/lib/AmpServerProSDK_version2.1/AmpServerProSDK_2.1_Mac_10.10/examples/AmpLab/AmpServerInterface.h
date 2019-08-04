
/**@file
 *  AmpServerInterface Header File
 *  @author Robert Bell
 *  @date 2011/09/14
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

#include <iostream>
#include <fstream>

#include <string.h>
#include "AS_Network_Client_Base.h"

// Some forward declarations.
class NotificationObserver;
class DataStreamObserver;

/**
 *  Amp Server Interface Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class provides an example of how to manage the C++ interface to the SDK for the MATLAB environment.<br>
 *
 *  <b> Important Notes:</b><br>
 *  
 *  1) This class is intended to be used from the C/C++ layer interacting with MATLAB. It is not heavily optimized
 *  and is intended to serve primarily as an example..<br>
 *
 *  ------<br>
 *  Update (001): 2011-09-14: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2015-08-03: Fixed bugs. Brought up to date with current release of Amp Server Pro SDK (and NA400 amplifiers).
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2015-10-05: Re-wrote since most of the functionality has been moved to other classes for clarity.
 *  ------<br>
 */
class AmpServerInterface {
  
 public:

  /**
   *  Contructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */ 
  AmpServerInterface();

  /**
   *  Destructor.
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
  virtual ~AmpServerInterface();
  
  static AmpServerInterface* GetAmpServer();
  
  /**
   *  Connects the Amp Server at the given IP address.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) ipAddress: The IP address to which to connect.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=0, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int connect( char* ipAddress );

  /**
   *  Disconnects from the Amp Server.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This should be called prior to exiting the MATLAB environment to allow for resources
   *  to be cleaned correctly. Note that in this example, "finish.m" is also present which will attemp
   *  a disconnect regardless of whether it was manually called.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=0, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int disconnect();

  /**
   *  Turns the amplifier on.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This call will fail if you are not connected.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=true, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int turnOnAmp();

  /**
   *  Starts the amplifier.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This call will fail if you are not connected.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=true, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int startAmp();

  /**
   *  Stops the amplifier.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This call will fail if you are not connected.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=true, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int stopAmp();

  /**
   *  Turns the amplifier off.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This call will fail if you are not connected.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=true, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int turnOffAmp();

  /**
   *  Send command wrapper.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This call wraps the client's send command with appropriate checks.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; int: success=true, failure=1.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  int sendCommand(const char *command, int16_t channel, int64_t value);

  /**
   *  Acquires the requested number of samples into the data buffer.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) The data buffer is expected to be initialized by the caller and be able
   *  to handle the appropriate number of samples. In this example, and for simplicity,
   *  we preallocate for 256 channels is the following manner:
   *  mxCreateDoubleMatrix(numsamples, 256, mxREAL), in the file ampsrv.c.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  void acquire(double* data, long numberOfSamples);

  /**
   *  Sets the amplifier ID.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) In almost all situations with the NA300, the amplifier ID will be zero, and
   *  for the NA400, it is always zero.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) ampID: The amplifier ID.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  void setAmpID(long ampID);

  /**
   *  Gets the amplifier ID.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) In almost all situations with the NA300, the amplifier ID will be zero, and
   *  for the NA400, it is always zero.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; The amplifier ID.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  long getAmpID();

  /**
   *  Sets whether or not to apply the scaling factor.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) Typically you'll always want to have the data stream object do it, but in
   *  case this is not the desired behaviour, the option to turn it off is given.
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) applyScalingFactor: true- scaling factor applied, false- scaling factor not applied.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  void setApplyScalingFactor(bool applyScalingFactor);

  /**
   *  Gets whether or not to apply the scaling factor.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) See notes in DataStreamObserver::setApplyScalingFactor(...).<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; bool: true- scaling factor applied, false- scaling factor not applied.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  bool getApplyScalingFactor();

 private:
  
  // Various items for keeping track of SDK related connections.
  int64_t ampID_;
  AS_Network_Client *client_;
  bool connected_;
  NotificationObserver *notificationObserver_;
  DataStreamObserver *dataStreamObserver_;
  bool applyScalingFactor_;

  // There is one global refernce to this, and it should be accessed via the
  // GetAmpServer method.
  static AmpServerInterface* theAmpServer;

};
