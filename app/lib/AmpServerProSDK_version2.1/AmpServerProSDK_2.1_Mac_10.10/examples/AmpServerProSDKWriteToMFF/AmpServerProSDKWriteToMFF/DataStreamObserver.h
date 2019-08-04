
/**@file
 *  DataStreamObserver Header File
 *  @author Robert Bell
 *  @date 2015/09/30
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// Other includes.
#include <iostream>

// Forward declarations.
struct SDKImpl;

/**
 *  DataStreamObserver Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class demonstrates how to extract data from AmpDataObjects that are distributed
 *  by the SDK when using the high-level C++ API, and deposit this data into a buffer. This data
 *  is then removed from the buffer and processed in a separate thread.<br>
 *
 *  <b> Important Notes:</b><br>
 *
 *  1) The class implements the update method, the method called to pass (in this case) instances of the class an AmpDataObject.
 *  DataStreamObserver:update(...) is called from a separate thread, and as such, you should take appropriate precautions.<br>
 *
 *  2) As noted above, in addition to normal thread precautions (locks etc.), you should avoid blocking in the
 *  update thread. This is because the update thread is the same thread that services the streaming data port and
 *  thus if you block, you will block this action. It is preferred to simply use the update method to move the received
 *  data to a buffer (of your choice), from which you can pull data on a separate thread.
 *
 *  ------<br>
 *  Update (001): 2015-09-01: Class creation.<br>
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
     *  &nbsp; 1) sdkWrapper: Various required SDK related information.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    DataStreamObserver(const SDKImpl* sdkWrapper);
    
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
     *  Sets the recording state of the data observer.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This is used to effectively start and stop the recording process. Since this class
     *  does not actually write the data to disk, it will simply either place data into the
     *  receiving buffer, or not.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) record: true- record data, false- don't record data.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual void setRecordingState(bool record);
    
    /**
     *  Gets the recording state of the data observer.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) See notes for DataStreamObserver::setRecordingState(...)<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; bool: true- record data, false- don't record data.<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual bool getRecordingState();
    
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
    
    SDKImpl* sdkWrapper_;
    bool record_;
    
    
};
