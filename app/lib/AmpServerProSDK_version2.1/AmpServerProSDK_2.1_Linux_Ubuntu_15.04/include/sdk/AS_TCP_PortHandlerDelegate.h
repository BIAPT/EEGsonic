
/**@file
 *  AS_TCP_PortHandlerDelegate header.
 *  @author Robert Bell
 *  @date 01/01/2007
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.<br>
 *  Put notes here.
 */

#ifndef AS_TCP_PortHandlerDelegate_DEFINED
#define AS_TCP_PortHandlerDelegate_DEFINED

#include "AS_TCP_PortHandler.h"

/** AS_TCP_PortHandlerDelegate class.
 *  @author Robert Bell.
 *  @remarks
 *  Receives data from a port handler.
 *
 *  ------<br>
 *  Update (001): 2007-01-01: Class creation.<br>
 *  ------<br>
 *
 *  ------<br>
 *  Update (002): 2012-05-07: Added ECI transaction packet type.<br>
 *  ------<br>
 */
class AS_TCP_PortHandlerDelegate : virtual public EGIBase::EGIObject{
	
public:
	
	/**
	 * Transaction Packet.
	 */
	typedef class TransactionPacket : public EGIBase::EGIObject{
		
	public:
		
		typedef int32_t TransactionType;
		
		static const TransactionType SIMPLE_S_EXPRESSIONS = 0;
		static const TransactionType EXTENDED_S_EXPRESSIONS = 1;
		static const TransactionType XML = 2;
		static const TransactionType HTTPD = 3;
		static const TransactionType PROTOCOL_BUFFERS = 4;
        static const TransactionType ECI = 5;
		static const TransactionType UNKNOWN_BINARY = 6;
		
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
		 *  ------<br>
		 *  <b>Throws</b><br>
		 *  &nbsp; N/A<br>
		 */
		TransactionPacket() : EGIBase::EGIObject(){
            
			this->transType = -1;
			this->transID = -1;
			this->transLen = 0;
			this->transData = NULL;
            
		}
		
		/**
		 *  Contructor.
		 *  <b>Notes:</b><br>
		 *  &nbsp; 1) If transData is NULL, memory is allocated of size transLen. In either case, ownership
		 *  is transferred to this object.<br>
		 *  ------<br>
		 *  <b>Arguments:</b><br>
		 *  &nbsp; transType : The transaction type.<br>
		 *  &nbsp; transID : The transaction ID.<br>
		 *  &nbsp; transLen : The transaction length. This can be 0, in which case the transaction data
         *  will be initialized to NULL.<br>
		 *  &nbsp; transData : The transaction data.<br>
		 *  ------<br>
		 *  <b>Return:</b><br>
		 *  &nbsp; N/A<br>
		 *  ------<br>
		 *  <b>Throws</b><br>
		 *  &nbsp; N/A<br>
		 */
		TransactionPacket(TransactionType transType, int32_t transID, uint32_t transLen, char *transData){
            
			this->transType = transType;
			this->transID = transID;
			this->transLen = transLen;
			
			if( transData != NULL ){
                
				this->transData = transData;
                
			} else if ( transLen != 0 ) {
                
				this->transData = new char[transLen];
                
            } else {
                
                this->transData = NULL;
                
            }
            
		}
		
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
		~TransactionPacket(){
        
            if ( this->transType == AS_TCP_PortHandlerDelegate::TransactionPacket::ECI ) {
                
                if( this->transData != NULL ) {
                    
                    AS_Network_Types::ECICommunicationPacket *eciCommunicationPacket = reinterpret_cast<AS_Network_Types::ECICommunicationPacket *>(this->transData);
                    
                    delete[] eciCommunicationPacket->data;
                    delete eciCommunicationPacket;
                    
                }
                
            } else {
                
                delete[] this->transData;
                
            }
            
		}
		
		/**
		 *  The data type. Valid types are:<br>
		 *  (0) AS_TCP_PortHandlerDelegate::TransactionPacket::SIMPLE_S_EXPRESSIONS<br>
		 *  (1) AS_TCP_PortHandlerDelegate::TransactionPacket::EXTENDED_S_EXPRESSIONS<br>
		 *  (2) AS_TCP_PortHandlerDelegate::TransactionPacket::XML<br>
         *  (3) AS_TCP_PortHandlerDelegate::TransactionPacket::HTTPD<br>
		 *  (4) AS_TCP_PortHandlerDelegate::TransactionPacket::PROTOCOL_BUFFERS<br>
         *  (5) AS_TCP_PortHandlerDelegate::TransactionPacket::ECI<br>
		 *  (6) AS_TCP_PortHandlerDelegate::TransactionPacket::UNKNOWN_BINARY<br>
		 */
		TransactionType transType;
		
		/**
		 *  Transaction ID.
		 */
		int32_t transID;
		
		/**
		 *  Transaction Data Length.
		 */
		uint32_t transLen;
		
		/**
		 *  Transaction Data Lenght.
		 */
		char *transData;
		
	}*TransactionPacketRef;
	
	//####################################
	// Constructor(s).
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
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_TCP_PortHandlerDelegate();
	
	//####################################
	// End - Constructor(s).
	//####################################
	
	//####################################
	// Destructor.
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
	virtual ~AS_TCP_PortHandlerDelegate();
	
	//####################################
	// End - Destructor.
	//####################################
	
	/**                                                                                                                                                                       
	 *  @name Memory Management.                                                                                                                                   
	 *  Memory Management.                                                                                     
	 */
	//@{
	
	/**
	 *  Retains this object.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); Throws EGIBase::Retain_EGIException on failure if exceptions are turned on,
	 *  otherwise returns NULL.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; N/A<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; AS_TCP_PortHandlerDelegate *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual AS_TCP_PortHandlerDelegate *retain();
	
	//@}
	
	/**
	 *  Data received.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); This is called when the port handler receives data..<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; trans: The transaction packet.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; void *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void *receive(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef) = 0;
	
	/**
	 *  Data send.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); This is called when the port handler sends data.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; trans: The transaction packet.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; void *: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void *send(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef) = 0;
	
	/**
	 *  Connection error.
	 *  <b>Notes:</b><br>
	 *  &nbsp 1); Called when the port handler encounters a connection error.<br>
	 *  ------<br>
	 *  <b>Arguments:</b><br>
	 *  &nbsp; trans: The transaction packet.<br>
	 *  &nbsp; userRef: User reference.<br>
	 *  ------<br>
	 *  <b>Return:</b><br>
	 *  &nbsp; void: N/A<br>
	 *  ------<br>
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	virtual void connnectionError(AS_TCP_PortHandler::ConnectionError error, void *userRef) = 0;
	
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
	virtual std::string toString() const {return EGIBase::EGIObject::toString() + "::AS_TCP_PortHandlerDelegate";}
	
	//####################################
	// Class variables.
	//####################################
	
	/**
	 *  Class ID<br>
	 *  Specifies the class ID for instances of this class.
	 */
	static const EGIBase::ClassID classID = 'ATPD';
	
	//####################################
	// End - Class variables.
	//####################################
	
	//####################################
	// Class methods.
	//####################################
	//####################################
	// End - Class methods.
	//####################################
	
protected:
	
	//##################
	//Copy constructor.
	//##################
	
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
	 *  <b>Throws</b><br>
	 *  &nbsp; N/A<br>
	 */
	AS_TCP_PortHandlerDelegate(const AS_TCP_PortHandlerDelegate& source);
	
	//##################
	// End - Copy constructor.
	//##################
	
	//##################
	// Assignment.
	//##################
	
	/**
	 *  Assignment.
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
	AS_TCP_PortHandlerDelegate&  operator=(const AS_TCP_PortHandlerDelegate& source);
	
	//##################
	// End - Assignment.
	//##################
	
	//####################################
	// Inheritence tree variables.
	//####################################
	//####################################
	// End - Inheritence tree variables.
	//####################################
	
private:
	
	//####################################
	// Non-Inheritence tree variables.
	//####################################
	//####################################
	// End - Non-Inheritence tree variables.
	//####################################
	
};

#endif // AS_TCP_PortHandlerDelegate_DEFINED


