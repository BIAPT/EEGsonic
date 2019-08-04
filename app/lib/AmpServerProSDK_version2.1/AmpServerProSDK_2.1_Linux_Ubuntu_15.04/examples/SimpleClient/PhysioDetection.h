
/**@file
 *  PhysioDetection Header File
 *  @author Robert Bell
 *  @date 2015/10/27
 *  @remarks
 *  Copyright 2015 EGI. All rights reserved.<br>
 */

// This include will pull in most of the header support you need from the SDK.
#include "AS_Network_Client_Base.h"

// Other includes.
#include <iostream>
#include <vector>

// Forward defines.
struct PhysioState;

/**
 *  A typed enum representing physio status.
 */
typedef enum{

  pys_Unknown,           /**< Status is unknown. */
  pys_NotConnected,      /**< Physio not connected. */
  pys_Connected,         /**< Physio connected. */
  pys_NewlyDisconnected, /**< Physio has gone from connected to disconnected. */
  pys_NewlyConnected     /**< Physio has gone from disconnected to connected. */

} PhysioStatus;

/**
 *  PhysioDetection Class.
 *  @author Robert Bell.
 *  @remarks
 *  This class is a simple class intended to keep track of the presence or physio units attached to the
 *  NA400 amplifier..<br>
 *
 *  <b> Important Notes:</b><br>
 *
 *  1) This class is ONLY applicable for the NA400 amplifier series.
 *  
 *  2) There is no flag indicating whether physio is present or not. Instead, one has to keep track of
 *  the digital inputs (digitalInputs field) within the "PacketFormat2_PIB_AUX" section of packet format 2.
 *  Specifically, the presence of a physio unit is detected when the values of the physio inputs are changing
 *  from sample to sample (decrementing by one until zero then resetting).
 *
 *  It should be noted that if you selected a sampling rate of less than 1000 samples per second,
 *  the NA400 will "up-sample" the data back to 1000sps by sample replication. It does this for historical
 *  reasons (see the Amp Server Pro SDK documentation). Since the NA400 supports rates of 250 and 500
 *  below 1000sps, it is possible for the digital input fields to be constant (for up to 4 samples),
 *  and yet the physio unit is still present. Similarly, since the physio data is only sampled at
 *  1000sps and no higher, if you set a sampling rate higher than 1000sps, you will also get data replication. With
 *  these two things in mind, care needs to be taken to ensure that you monitor enough samples such that duplicate
 *  samples are not interpreted as the lack of a physio unit. This class takes all these factors into account.<br>
 *  
 *
 *  3) The NA400 currently supports two physio units only.<br>
 *
 *  ------<br>
 *  Update (001): 2015-10-27: Class creation.<br>
 *  ------<br>
 */
class PhysioDetection : public EGIBase::EGIObject{
  
 public:
  
  /**
   *  Contructor.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) numberOfPhysioUnits: The number of physio amplifers supported (usually two).<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; N/A<br>
   */
  PhysioDetection(unsigned int numberOfPhysioUnits);

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
  virtual ~PhysioDetection();
  
  /**
   *  Clone.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) Implements the virtual constructor idiom.<br>
   *  &nbsp; 2) Use covariant return types in descended classes.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) numberOfPhysioUnits: The number of physio amplifers supported (usually two).<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; PhysioDetection *: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  virtual PhysioDetection *clone(unsigned int numberOfPhysioUnits) const;

  /**
   *  Create (default constructor).
   *  <b>Notes:</b><br>
   *  &nbsp; 1) Implements the virtual constructor idiom.<br>
   *  &nbsp; 2) Use covariant return types in descended classes.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) numberOfPhysioUnits: The number of physio amplifers supported (usually two).<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; Create *: N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  virtual PhysioDetection *create(unsigned int numberOfPhysioUnits) const;

  /**
   *  Init.
   *  <b>Notes:</b><br>
   *  &nbsp; 1) Use covariant return types in descended classes.<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; eObject: Initialization object.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; PhysioDetection *: This object, initialized or not.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::Init_EGIException: When execptions are in use, a failure
   *  should be propagated by at the very least an EGIBase::Init_EGIException.<br>
   */
  virtual PhysioDetection *init(EGIObject *eObject);
  
  /**
   *  Determines the state of a physio unit.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) physioUnitIndex: The index of the physio unit. This is zero-based and thus should be
   *  less than the number of physio units specified in the constructor..<br>
   *  &nbsp; 2) digitalInputValue: This value is needed and is found in the packet delivered from the NA400 amplifier
   *  during acquisition. Please see the class notes above. Make sure you send in the physio digitial input value and
   *  not the NA400 amplifier one.<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; PhysioStatus: the physio unit status.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) std::out_of_range: This is thrown if the physio unit index is out of range.<br>
   */
  virtual PhysioStatus detectPhysioUnitState(unsigned int physioUnitIndex,
					     uint8_t digitalInputValue);

  /**
   *  Indicates whether a physio unit is connected.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; 1) physioUnitIndex: The index of the physio unit. This is zero-based and thus should be
   *  less than the number of physio units specified in the constructor..<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; bool: true- connected; false- not connected.<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) std::out_of_range: This is thrown if the physio unit index is out of range.<br>
   */
  virtual bool isPhysioUnitConnected(unsigned int physioUnitIndex); 

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
  PhysioDetection(const PhysioDetection& source);
  
  /**
   *  Assignment.
   *  <b>Notes:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Arguments:</b><br>
   *  &nbsp; N/A<br>
   *  ------<br>
   *  <b>Return:</b><br>
   *  &nbsp; PhysioDetection& : N/A<br>
   *  ------<br>
   *  <b>Throws:</b><br>
   *  &nbsp; 1) EGIBase::MethodNotSupported_EGIException.<br>
   */
  PhysioDetection& operator=(const PhysioDetection& source);

 private:

  uint32_t numberOfPhysioUnits_;
  std::vector<PhysioState *> *physioStates_;

};
