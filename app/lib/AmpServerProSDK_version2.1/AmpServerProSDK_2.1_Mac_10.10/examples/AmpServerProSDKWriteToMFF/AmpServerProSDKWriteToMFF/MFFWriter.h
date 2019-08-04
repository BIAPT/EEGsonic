
/**@file
 *  MFFWriter Header File
 *  @author Robert Bell
 *  @date 2015/12/01
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// Other EGI Base includes.
#include "EGITask.h"
#include "EGIBuffer.h"

// Other includes.
#include <iostream>

// Forward declarations.
namespace EGIBase {
    class EGICircularBuffer;
}

@class AppController;

/**
 *  MFFWriter Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class demonstrates how to write data collected from an EGI amplifer to an MFF file. It relies heavily on
 *  the supporting class, MFFWriterUtilities, to do most of its work.<br>
 *
 *  <b> Important Notes:</b><br>
 *
 *  1) The class implements the perform task method of an EGI task. Most of the work is done in this method.<br>
 *
 *  2) Although this is wrapped in an EGITask, it is not required that it be implemented in this manner. The goal is
 *  to demonstrate how to write an MFF file given data collected from the amplifer.<br>
 *
 *  ------<br>
 *  Update (001): 2015-12-01: Class creation.<br>
 *  ------<br>
 */
class MFFWriter : public EGIBase::EGITask{
    
public:
    
    /**
     *  Contructor.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) ampInfo: Amplifer information. This class needs, in particular, the packet type and the
     *  the amplifier type.<br>
     *  &nbsp; 2) ampBuffer: The buffer from which to pull data.<br>
     *  &nbsp; 3) mffFileURI: The intended file URI for the MFF file.<br>
     *  &nbsp; 4) appcontroller: The application controller.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    MFFWriter(AS_Network_Types::AmpInfo ampInfo,
              EGIBase::EGICircularBuffer *ampBuffer,
              std::string mffFileURI,
              int samplingRate,
              AppController *appController);
    
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
    virtual ~MFFWriter();
    
    /**
     *  The perform task method.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) This method is called by the task scheduler.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; 1) taskScheduler: The task scheduler object calling this method.<br>
     *  &nbsp; 2) eObject: Optional user reference.<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual void performTask(EGIObject *taskScheduler, EGIObject *eObject);
    
    /**
     *  Stops the recording.
     *  <b>Notes:</b><br>
     *  &nbsp; 1) When an MFF writer is created, it assumes it must open and continue writing to file until
     *  it is instructed to stop recording via this method call. Once this method is called, the task
     *  will close up its file to create a fully formed MFF file.<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; void: N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; N/A<br>
     */
    virtual void stopRecording();
    
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
    MFFWriter(const MFFWriter& source);
    
    /**
     *  Assignment.
     *  <b>Notes:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Arguments:</b><br>
     *  &nbsp; N/A<br>
     *  ------<br>
     *  <b>Return:</b><br>
     *  &nbsp; MFFWriter& : N/A<br>
     *  ------<br>
     *  <b>Throws:</b><br>
     *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
     */
    MFFWriter& operator=(const MFFWriter& source);
    
private:
    
    bool stopRecording_;
    AS_Network_Types::AmpInfo ampInfo_;
    int samplingRate_;
    AS_Network_Types::NetCode netCode_;
    EGIBase::EGICircularBuffer *ampBuffer_;
    EGIBase::EGIBuffer::Opts *ampBufferOpts_;
    
    char *srcData_;
    int64_t srcDataSize_;
    int64_t sampleCounter_;
    int64_t dataBlockCounter_;
    
    std::string mffFileURI_;
    AppController *appController_;
    
};
