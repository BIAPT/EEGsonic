
/**@file
 *  Client Access header.
 *  @author Robert Bell
 *  @date 1/1/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  This class represents the main gateway to Amp Server. It is possible for connections
 *  to be made directly to Amp Server using the documented TCP/IP protocol, but life
 *  will be much easier if access is accomplished via this class.
 */

#ifndef AS_Network_Client_DEFINED
#define AS_Network_Client_DEFINED

#include "ObserverPattern.h"
#include "AS_Network_Types.h"
#include "AS_ReturnValue.h"

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#include <string>

/** Amp Server Pro SDK's client class.
 *  @author Robert Bell.
 *  @remarks
 *  This class represents the main gateway to Amp Server. It is possible for connections
 *  to be made directly to Amp Server using the documented TCP/IP protocol, but life
 *  will be much easier if access is accomplished via this class.
 *
 *  ------<br>
 *  Update (001): 2009-04-07: Updated the manner in which data observers are added to the system. The
 *  system now keeps track of amplifier IDs internally, and can determine when users of the API are
 *  are listening to an amplifier. When the last amplifier observer drops off the list, the system sends a request
 *  to Amp Server to stop listening to that amplifier. Note there has been a slight change to the API as
 *  a result of this; the deleteDataObserver function no longer takes an amplifier ID.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2009-10-20: Added int16_t AS_Network_Client::getNumberOfActiveAmps().<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (003): 2009-10-21: Added a timeout version of fgets.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (004): 2009-11-13: AS_Network_Client::sendCommand(...) value parameter is now int64_t.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (005): 2012-01-29: Added cmd_SetMRIPulseInfo and cmd_SetPIBChannelGain to the command
 *  environment.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (006): 2013-08-20: Added a control flag and timeout argument to the connect method.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (007): 2014-06-09: Updated code for command return size. Also cleaned up redundant code, and
 *  a number of efficiency cleanups.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Todo: YEAR-MO-DA:<br>
 *  ------<br>
 */
class AS_Network_Client : virtual public EGIBase::ObserverPattern::Observable{
	
public:
	
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
	AS_Network_Client();
	
	/**
	 *  Contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) threadSafe: true = thread safe; false = not thread safe<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Client(bool threadSafe);
	
	//####################################
	//End - Constructor(s).
	//####################################
	
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
	virtual ~AS_Network_Client();
	
	/**
	 *  @name Connection Related Functions.
	 *  All functions relating to connections with Amp Server fall into this section.
	 */
	//@{
	
	/**
	 *  Adds Amp Server detection for the specified network location.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not currently available.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  &nbsp; 3) You must have added a notification observer.<br>
	 *  &nbsp; 4) Amp Server responds to UDP query messages if it is running. Use this method to register
	 *  to an AS_Network_Client instance to receive notifications as to the availability of
	 *  Amp Server at a particular network location.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) detPrefsRef: A reference to an AS_Network_Types::DetPrefs instance.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int32_t : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status addAmpServerAvailabilityDetection(const AS_Network_Types::DetPrefsRef detPrefsRef);
	
	/**
	 *  Removes Amp Server detection for the specified network location.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not currently available.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  &nbsp; 3) Does the reverse of AS_Network_Client::addAmpServerAvailabilityDetection.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) detPrefsRef: A reference to an AS_Network_Types::DetPrefs instance.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status removeAmpServerAvailabilityDetection(const AS_Network_Types::DetPrefsRef detPrefsRef);
	
	/**
	 *  Detects the presence of Amp Server at the specified network location.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) Unlike the AS_Network_Client::addAmpServerAvailabilityDetection above, this
	 *  method simply returns whether Amp Server was detected at the given location in a synchronous
	 *  manner. It does not setup future asynchronous callbacks through the notification system.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) detPrefsRef: A reference to an AS_Network_Types::DetPrefs instance.<br>
	 *  &nbsp; 2) timeout: How long to wait before timing out (microseconds: 1*10^6 = 1 second).<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; bool : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual bool detectAmpServer(const AS_Network_Types::DetPrefsRef detPrefsRef, int64_t timeout);
	
	/**
	 *  The connect function.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) If the passed in connection preferences (connPrefsRef) are NULL, then default ones
	 *  are used matching the defaults defined AS_Network_Types::ConnPrefsRef.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) detPrefsRef: A reference to an AS_Network_Types::DetPrefs instance.<br>
     *  &nbsp; 2) returnAfterFailure: If set to true, then the method will return after any failure to
     *  connect to a port rather than continuing to try and connect to the other desired ports.<br>
	 *  &nbsp; timeout: How long to wait before timing in seconds.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status connect(const AS_Network_Types::ConnPrefsRef connPrefsRef,
                                             bool returnAfterFailure = false,
                                             int timeout = 75);
	
	/**
	 *  The disconnect function.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) Cleanly disconnnects from the server.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status disconnect();
	
	//@}
	
	/**
	 *  @name Observer Related Functions.
	 *  Since AS_Network_Client has Observable as a parent,
	 *  you can call its add/delete observer functions directly.<br>
	 *  All Observer-related functions are thread safe.<br>
	 */
	//@{
	
	/**
	 *  Adds a notification observer.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) If observer is NULL or the observer is already present, does nothing.<br>
	 *  &nbsp; 3) It is safe to have notifications active, and no observers registered.<br>
	 *  &nbsp; 4) There is no limit to the number of notification observers that can be added.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) observer: The observer.<br>
	 *  &nbsp; 2) userRef: A user reference passed back to the observer's update method.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status addNotificationObserver(EGIBase::ObserverPattern::Observer *observer, void *userRef);
	
	/**
	 *  Deletes a notification observer.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) If the observer is NULL or the observer is not present, does nothing.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) observer: The observer.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status deleteNotificationObserver(EGIBase::ObserverPattern::Observer *observer);
	
	/**
	 *  Deletes all notification observers.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status deleteAllNotificationObservers();
	
	/**
	 *  Adds a dataStream observer.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) If observer is NULL or the observer is already present, does nothing.<br>
	 *  &nbsp; 3) The observer will only be notified for data from the specified amplifier.<br>
	 *  &nbsp; 4) It is safe to have the dataStream active, and no observers registered.<br>
	 *  &nbsp; 5) There is no limit to the number of dataStream observers that can be added.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) observer: The observer.<br>
	 *  &nbsp; 2) ampID: The ID of the amplifier.<br>
	 *  &nbsp; 3) userRef: A user reference passed back to the observer's update method.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status addDataStreamObserver(EGIBase::ObserverPattern::Observer *observer, int64_t ampID, void *userRef);
	
	/**
	 *  Deletes a dataStream observer.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) If the observer is NULL or the observer is not present, does nothing.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) observer: The observer.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */	
	virtual AS_Network_Types::Status deleteDataStreamObserver(EGIBase::ObserverPattern::Observer *observer);
	
	/**
	 *  Deletes all dataStream observers.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Types::Status : See definition for states.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_Network_Types::Status deleteAllDataStreamObservers();
	
	//@}
	
	/**
	 *  @name Amp Server Related Functions.
	 *  All commands primarily connected with getting information about Amp Server, or the
	 *  amplifiers themselves fall into this area.
	 */
	//@{
    
    /**
	 *  Send Command.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) The internal "sendCommand" function can be considered as the following:<br>
	 *  <br>
	 *  (defun sendCommand (command ampID channel value) ... ).<br>
	 *  <br>
	 *  Thus, this method call translates to the string: (sendCommand command ampID channel value) being
	 *  sent to Amp Server. Indeed, if you were communicating directly, this is what you would
	 *  use.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) command: The command string.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue * : Callee owned.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *sendCommand(std::string command);
	
	/**
	 *  Send Command.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) The internal "sendCommand" function can be considered as the following:<br>
	 *  <br>
	 *  (defun sendCommand (command ampID channel value) ... ).<br>
	 *  <br>
	 *  Thus, this method call translates to the string: (sendCommand command ampID channel value) being
	 *  sent to Amp Server. Indeed, if you were communicating directly, this is what you would
	 *  use.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The ID of the amplifier.<br>
	 *  &nbsp; 2) command: The command string.<br>
	 *  &nbsp; 3) channel: The channel.<br>
	 *  &nbsp; value: The value.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue * : Callee owned.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *sendCommand(int64_t ampID, std::string command, int16_t channel, int64_t value);
	
	/**
	 *  Send Command.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) The internal "sendCommand" function can be considered as the following:<br>
	 *  <br>
	 *  (defun sendCommand (command ampID channel value) ... ).<br>
	 *  <br>
	 *  Thus, this method call translates to the string: (sendCommand command ampID channel value) being
	 *  sent to Amp Server. Indeed, if you were communicating directly, this is what you would
	 *  use.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The ID of the amplifier.<br>
	 *  &nbsp; 2) command: The command string.<br>
	 *  &nbsp; 3) channel: The channel.<br>
	 *  &nbsp; 4) value: The value.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue * : Callee owned.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *sendCommand(int64_t ampID, std::string command, int16_t channel, std::string value);
	
	/**
	 *  Send Command by type.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) The internal "sendCommand" function can be considered as the following:<br>
	 *  <br>
	 *  (defun sendCommand (command ampID channel value) ... ).<br>
	 *  <br>
	 *  Thus, this method call translates to the string: (sendCommand command ampID channel value) being
	 *  sent to Amp Server. Indeed, if you were communicating directly, this is what you would
	 *  use.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The ID of the amplifier.<br>
	 *  &nbsp; 2) command: The command string.<br>
	 *  &nbsp; 3) channel: The channel.<br>
	 *  &nbsp; 4) value: The value.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue *: Callee owned.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *sendCommandByType(int64_t ampID, AS_Network_Types::CommandType commandType, int16_t channel, int64_t value);
	
	/**
	 *  Gets the start time of the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) This value is set every time the amplifier is started, and represents the system time when the amplifier
	 *  started, measured in microseconds, that have passed since the Epoch: 00:00:00 Janurary 1.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The start time.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int64_t getAmpStartTime(int64_t ampID);
	
	/**
	 *  Gets the current time of the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) This value is simply a measure of the number of samples acquired since the amplifier started.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The current time in milliseconds.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int64_t getCurrentAmpTime(int64_t ampID);
	
	/**
	 *  Gets the current drift of the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) This value is the drift relative to the system on which the amplifier is running.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The current drift in microseconds.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int64_t getCurrentAmpDrift(int64_t ampID);
	
	/**
	 *  Gets the current dio values of the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) Only available for NA300 amps.<br>
	 *  &nbsp; 3) These are returned as a uint16_t, which corresponds to the two 8-bit wide DINs.
	 *  The arrangement is as follows:<br>
	 *  <br>
	 *  pins 8-1  (matching sticker on the NA300 amplifier : low byte (bits 7-0)<br>
	 *  pins 16-9 (matching sticker on the NA300 amplifier : low byte (bits 15-8)<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; uint16_t: The dio values.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual uint16_t getAmpDIOValues(int64_t ampID);
	
	/**
	 *  Gets the number of amps.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) the value returned represents the TOTAL number of amps ever seen by an given running
	 *  instance of Amp Server. The number returned also implies the ID of those amps. For example,
	 *  if a value of "2" is returned, then two amps have been seen by this Amp Server running instance,
	 *  of ids 0 and 1 respectively.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int16_t: The number of amps.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int16_t getNumberOfAmps();
	
	/**
	 *  Gets the number of active amps.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) Typically, this translates to the number of amps in active registration with the
	 *  Amp Server (i.e., plugged in). Note that the ids will not match up as in
	 *  the AS_Network_Client::getNumberOfAmps() case.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int16_t: The number of active amps.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int16_t getNumberOfActiveAmps();
	
	/**
	 *  Gets amplifier details for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 2) This includes information as to type of amplifier and any other relevent information.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue *: The amplifier details (callee owned).<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *getAmpDetails(int64_t ampID);
    
    /**
     *  Gets amplifer information.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This call is thread safe.<br>
     *  &nbsp; 2) This is somewhat equivalent to AS_Network_Client::getAmpDetails(), except that
     *  it conveniently parses the AS_ReturnValue for commonly needed amplifier information.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; ampID: The amplifier ID.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; AmpInfo: The amplifier information.<br>
     *  ------<br>
     *  <b>Throws</b><br>
     *  &nbsp; N/A<br>
     */
    virtual AS_Network_Types::AmpInfo getAmpInfo(int64_t ampID);
	
	/**
	 *  Gets amplifier status.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not currently available.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  &nbsp; 3) This includes information as to the current state of the amplifier.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_ReturnValue *: The amplifier status (callee owned).<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_ReturnValue *getAmpStatus(int64_t ampID);
	
	/**
	 *  Gets amplifier serial number for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int32_t: The serial number.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int32_t getSerialNumber(int64_t ampID);
	
	/**
	 *  Gets amplifier serial number string for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; std::string: The serial number string.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual std::string getSerialNumberString(int64_t ampID);
	
	/**
	 *  Gets firmware major revision for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int8_t: The firmware major revision.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int8_t getFirmwareMajorRevision(int64_t ampID);
	
	/**
	 *  Gets firmware minor revision for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int8_t: The firmware minor revision.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int8_t getFirmwareMinorRevision(int64_t ampID);
	
	/**
	 *  Gets hardware major revision for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int8_t: The hardware major revision.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int8_t getHardwareMajorRevision(int64_t ampID);
	
	/**
	 *  Gets hardware minor revision for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int8_t: The hardware minor revision.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int8_t getHardwareMinorRevision(int64_t ampID);
	
	/**
	 *  Gets amplifier revision string for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  &nbsp; 1) This contains all hardware and FireWire information.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; std::string: The revision string.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual std::string getRevisionString(int64_t ampID);
	
	/**
	 *  Gets number of EEG channels for the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) This call is thread safe.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int8_t: The number of EEG channels.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int16_t getNumberOfEEGChannels(int64_t ampID);
	
	/**
	 *  Sets the channels desired from the specified amplifier.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not currently available.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  &nbsp; 3) This method causes Amp Server to select which channels are delivered to the client.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  &nbsp; 2) channels: List of uint8_t. 0 : channel not desired, 1 : channel desired.<br>
	 *  &nbsp; 3) numberOfChannels: Number of channels.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void selectChannels(int16_t ampID, const uint8_t *channels, int16_t numberOfChannels);
	
	/**
	 *  Gets the current latency between the client and Amp Server.
	 *  <b>Notes:</b><br>
	 *  &nbsp; 1) Not currently available.<br>
	 *  &nbsp; 2) This call is thread safe.<br>
	 *  &nbsp; 3) Each client object maintains latency information between itself and Amp Server to which
	 *  it is connected. The value returned is in microseconds, and a negative return value indicates
	 *  that latency information is unavailable.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; 1) ampID: The amplifier ID.<br>
	 *  &nbsp; 2) channels: List of uint8_t. 0 : channel not desired, 1 : channel desired.<br>
	 *  &nbsp; 3) numberOfChannels: Number of channels.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The latency in microseconds.<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int64_t getLatency();
	
	//@}
	
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
	virtual std::string toString(){return EGIBase::ObserverPattern::Observable::toString() + "::AS_Network_Client";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ANCL';
	
	//####################################
	//End - Class variables.
	//####################################
	
	//####################################
	//Class methods.
	//####################################
	
	/**
	 *  A forward declaration supporting internal implementation.
	 *  For implementation reasons, this forward declaration is public.
	 */
	struct AS_Network_ClientImpl;
	
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
	AS_Network_Client(const AS_Network_Client& source);
	
	/**
	 *  Assignment.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AS_Network_Client& : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_Network_Client&  operator=(const AS_Network_Client& source);
	
	//####################################
	//Non-Inheritence tree variables.
	//####################################
	AS_Network_ClientImpl *mAS_Network_ClientImplRef;
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_Network_Client_DEFINED
