
/**@file
 *  DataStreamObserver Header File
 *  @author Robert Bell
 *  @date 2015/09/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// Other includes.
#include <iostream>

// Forward defines.
class PhysioDetection;

/**
 *  DataStreamObserver Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class demonstrates how to extract data from AmpDataObjects that are distributed
 *  by the SDK when using the high-level C++ API.<br>
 *
 *  <b> Important Notes:</b><br>
 *  
 *  1) The class implements the update method, the method called to pass (in this case) instances of the class an AmpDataObject.
 *  DataStreamObserver:update(...) is called from a separate thread, and as such, you should take appropriate precautions.<br>
 *
 *  2) Data is distributed in two packet format types, Packet Format 1 and Packet Format 2. You can find details of
 *  this format in the Amp Server Pro SDK 2.0 Network Protocols Programmers reference as well as in the header file
 *  AS_Network_Types.h. The update method implementation in this class demontrates decoding both packet type formats.<br>
 *
 *  3) Both packet formats distribute data in analog to digital units. Scaling factors specific to each amplifer type
 *  are using to convert the values to microvolts.<br>
 *
 *  4) As noted above, in addition to normal thread precautions (locks etc.), you should avoid blocking in the
 *  update thread. This is because the update thread is the same thread that services the streaming data port and
 *  thus if you block, you will block this action. It is preferred to simply use the update method to move the received
 *  data to a buffer (of your choice), from which you can pull data on a separate thread. In this example, we do not
 *  show this activity since computation is low (just converstions), and it's only an example.
 *
 *  ------<br>
 *  Update (001): 2015-09-01: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2015-09-07: Re-wrote to in .h/.cpp format. Fixed errors, updated comments.<br>
 *  ------<br>
 */
class DataStreamObserver : public EGIBase::ObserverPattern::Observer{
  
 public:
  
  /**
   *  Contructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) ampInfo: Amplifer information. This class needs, in particular, the packet type and the
   *                     the amplifier type.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  DataStreamObserver(const AS_Network_Types::AmpInfo ampInfo);

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
  virtual ~DataStreamObserver();
  
  /**
   *  This class's implementation of update.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) This method is called when the object being observed calls its notify method.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) observable: The observable object calling this method.<br>
   *  &nbsp; 2) eObject: The optional user reference passed to the observable object.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; void: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  virtual void update(EGIBase::ObserverPattern::Observable *o, EGIObject *eObject);

  /**
   *  Sets the state of the sample statistics debugging output.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) sampleStatisticsDebuggingOutput: true- on, false- off.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; void: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  virtual void setSampleStatisticsDebuggingOutput(bool sampleStatisticsDebuggingOutput);

  /**
   *  Sets the state of the physio sample debugging output.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) physioDebuggingOutput: true- on, false- off.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; void: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  virtual void setPhysioDebuggingOutput(bool physioDebuggingOutput);

 protected:

  /**
   *  Copy Constructor.
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
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  DataStreamObserver(const DataStreamObserver& source);
  
  /**
   *  Assignment.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; DataStreamObserver& : N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  DataStreamObserver& operator=(const DataStreamObserver& source);

 private:

  // Various information to help the class's update method decode
  // data passed to the update method.
  AS_Network_Types::AmpInfo ampInfo_;
  uint64_t lastPacketCounter_;
  uint64_t sampleCount_;
  float scalingFactor_;
  float batteryScaleTemp_;

  // Timing information.
  uint64_t lastSystemTime_;

  // Physio Units.
  PhysioDetection *physioDetection_;

  bool outputSampleStatisticsDebug_;
  bool outputPhysioDebug_;

};
