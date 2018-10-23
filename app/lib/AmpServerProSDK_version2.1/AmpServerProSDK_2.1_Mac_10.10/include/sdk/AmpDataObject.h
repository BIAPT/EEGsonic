
/**@file
 *  AmpDataObject Header File
 *  @author Robert Bell
 *  @date 1/1/2007
 *  @remarks
 *  Copyright 2010 EGI. All rights reserved.<br>
 *  The AmpDataObject wraps amplifier data.
 */

#ifndef AmpDataObject_DEFINED
#define AmpDataObject_DEFINED

#include "AS_Network_Types.h"

/**
 *  AmpDataObject Class.
 *  @author Robert Bell.
 *  @remarks
 *  The AmpDataObject wraps amplifier data.<br>
 *
 *  <b> Amp Data Format </b><br>
 *  Amp Server Pro SDK distributes data out in a sample contiguous manner in the
 *  following format:<br>
 *  One sample consists of:<br>
 *  | <- (32 byte header) -> | <- (280 channels of float values) -> |<br><br>
 *  As indicated in the AmpDataObject::getDataSize() description below, the size of data is indicated in bytes.
 *  Thus, to obtain the number of samples contained in a particular AmpDataObject instance, perform the
 *  following: AmpDataObject::getDataSize() / (32 + (280 * sizeof(float)))<br>
 *  On a 32-bit machine with usual representations, the denominator will be equal to 1152 bytes.<br><br>
 *  Thus, suppose an AmpDataObject was delivered and AmpDataObject::getDataSize() returned 11520. This would
 *  mean that it contained (11520 / 1152) samples = 10 samples. The layout would look like:<br><br>
 *  (sample 0) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 1) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 2) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 3) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 4) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 5) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 6) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 7) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 8) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br>
 *  (sample 9) | <- (32 byte header) -> | <- (280 channels of float values) -> |<br><br>
 *
 *  <b>Header Format</b><br>
 *  The header, as mentioned above, is 32 bytes. Important locations are:<br>
 *  Bytes 24 and 25, which contain DIO information.<br><br>
 *
 *  <b>Channel Format</b><br>
 *  Currently, regardless of the amplifier, 280 channels are ALWAYS sent. For example, when you have a 128-channel amplifier,
 *  the first 128 channels will be of interest, and the rest will not.<br>
 *  Documentation on the channels above 256 will be made available soon.
 *
 *  ------<br>
 *  Update (001): 2007-01-01: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Todo: YEAR-MO-DA:<br>
 *  ------<br>
 *
 */
class AmpDataObject : virtual public EGIBase::EGIObject{
	
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
	AmpDataObject();
	
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
	AmpDataObject(bool threadSafe);
	
	/**
	 *  Contructor.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; data: The data (see copy argument below)<br>
	 *  &nbsp; ampID: The amplifier ID from which this data came<br>
	 *  &nbsp; sizeOfData: Size of the data argument above in bytes<br>
	 *  &nbsp; copy: true = by copy; false = not by copy<br>
	 *  &nbsp; threadSafe: true = thread safe; false = not thread safe<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AmpDataObject(char *data, int64_t ampID, uint64_t sizeOfData, bool copy, bool threadSafe);
	
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
	AmpDataObject(const AmpDataObject& source);
	
	//####################################
	//End - Constructor(s).
	//####################################
	
	/**
	 *  Assignment.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; AmpDataObject& : N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AmpDataObject& operator=(const AmpDataObject& source);
	
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
	virtual ~AmpDataObject();
	
	/**
	 *  Sets the copy state of this object.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Calling this method will clear the current data state, so any
	 *  data currently known about will be lost. If this instance was previously
	 *  keeping a reference the data, the data itself is not affected.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; copy: true = by copy; false = not by copy<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setCopy(bool copy);
	
	/**
	 *  Gets the copy state of this object.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; bool: Copy state<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual bool getCopy();
	
	/**
	 *  Sets the amplifier ID.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; ampID: The amplifier ID from which this data came<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setAmpID(int64_t ampID);
	
	/**
	 *  Gets the amplifier ID.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; int64_t: The amplifier ID<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual int64_t getAmpID();
	
	/**
	 *  Sets the data.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Respects the copy status of the object.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; data: The data<br>
	 *  &nbsp; sizeOfData: The size of the data<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void setData(char *data, uint32_t sizeOfData);
	
	/**
	 *  Gets the data.
	 *  <b>Notes:</b><br>
	 *  &nbsp; Respects the copy status of the object unless the implicit argument indicates to reverse
	 *  the current copy status.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; reverse: Implicit argument to temporarily reverse the object's copy status (see notes)<br>
	 *  &nbsp; sizeOfData: The size of the data<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; char *: The data<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual char *getData(bool reverse = false);
	
	/**
	 *  Gets size of the data in bytes.
	 *  <b>Notes:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
 	 *  &nbsp; uint64_t: The size of the data in bytes<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual uint64_t getSizeOfData();
	
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
	virtual EGIBase::ClassID getClassID(){return AmpDataObject::classID;}
	
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
	virtual std::string toString(){return EGIBase::EGIObject::toString() + "::AmpDataObject";}
	
	//####################################
	//Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	static const EGIBase::ClassID classID = 'ADOB';
	
	//####################################
	//End - Class variables.
	//####################################
	
	//####################################
	//Class methods.
	//####################################
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
	
	//####################################
	//Non-Inheritence tree variables.
	//####################################
	struct AmpDataObjectImpl;
	AmpDataObjectImpl* mAmpDataObjectImplRef;
	//####################################
	//End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AmpDataObject_DEFINED


