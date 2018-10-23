
/*
 *  ECICommandDelegate.cpp
 *  @author Robert Bell
 *  @date 27/07/2012
 *  @remarks
 *  Copyright 2012 EGI. All rights reserved.
 */

#include "ECICommandDelegate.h"

// MFF.
#include "Event.h"
#include "Key.h"
#include "ByteBuffer.h"
#include "MFFUtils.h"

// EGIBase.
#include "EGIObject.h"
#include "EGIExceptions.h"
#include "EGIXStringWrap.h"
#include "UtilityFunctions.h"

// Amp Server Pro SDK.
#include "AS_Network_Types.h"
#include "ConnectionObject.h"

// Application support.
#include "ECIEvent.h"

#include <iostream>

using namespace EGIBase;
using namespace com::egi::services::mff::api;
using namespace com::egi::services::mff::util;
using namespace com::egi::applicationsupport::eci;

// Safely wraps std::string pointers to values.
static std::string localStringWrap(const std::string *theString){
    
    std::string rVal = "not set";
    
    if ( theString != NULL) {
        
        rVal = *theString;
        
    }
    
    return rVal;
    
}

//####################################
//Public section.
//####################################

//##################
//Constructor(s).
//##################

ECICommandDelegate::ECICommandDelegate() : AS_TCP_PortHandlerDelegate(){}

ECICommandDelegate::ECICommandDelegate(const ECICommandDelegate& source) : AS_TCP_PortHandlerDelegate(source){}

//##################
//End - Constructor(s).
//##################

//##################
//Destructor.
//##################

ECICommandDelegate::~ECICommandDelegate(){}

//##################
//End - Destructor.
//##################

ECICommandDelegate& ECICommandDelegate::operator=(const ECICommandDelegate& source){
	
    if(this != &source){
        
        AS_TCP_PortHandlerDelegate::operator=(source);
        
    }
    
	return *this;
    
}

ECICommandDelegate *ECICommandDelegate::clone() const{
    
	ECICommandDelegate *rVal = NULL;
	
	try{
        
		rVal = new ECICommandDelegate(*this);
        
	}
	catch(EGIBase::MethodNotSupported_EGIException){
        
		throw;
        
	}
	
	return rVal;
}

ECICommandDelegate *ECICommandDelegate::create() const{
    
	ECICommandDelegate *rVal = NULL;
	
	try{
        
		rVal = new ECICommandDelegate();
        
	}
	catch(std::bad_alloc){
        
		std::cout << this->toString() << ": fatal error: out of memory" << std::endl;
        
	}
	
	return rVal;
}

ECICommandDelegate *ECICommandDelegate::init(EGIObject *eObject){
    
	return this;
    
}

void *ECICommandDelegate::receive(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef){
	
    // Notes about write-backs.
    // Many commands have an AS_Network_Types::ECICommandType write-back. Typical commands to write back are:
    //
    // 1) AS_Network_Types::eci_OK.
    // 2) AS_Network_Types::eci_Failure.
    // 3) AS_Network_Types::eci_NoRecordingDeviceFailure.
    //
    //
    // In this delegate example, AS_Network_Types::eci_OK is demonstrated, but this will depend on the
    // delegate in question.
    //
    // When a command requires an AS_Network_Types::ECICommandType write-back, it will be noted as such. Other
    // commands will be noted as to the required write-backs, if any.
    
	// This layer can respond to an exit message.
	bool exitFlag = false;
	
	if(trans!=NULL){
        
        // Obtain the connection object.
        ConnectionObject *connectionObject = NULL;
        if( userRef != NULL ){
            
			connectionObject = static_cast<ConnectionObject *>(userRef);
            
		}
		
		// Some commands will be handled directly by the bridge itself. For example, requests for channel
		// information. Others will passed on through to the Amp Server itself.
		
		// We understand transaction packets of type AS_TCP_PortHandlerDelegate::TransactionPacket::ECI.
		if(trans->transType == AS_TCP_PortHandlerDelegate::TransactionPacket::ECI){
			
			bool parseError = false;
            AS_Network_Types::ECICommandType eciCommand = AS_Network_Types::eci_OK;
			
			AS_Network_Types::ECICommunicationPacket *eciCommunicationPacket = reinterpret_cast<AS_Network_Types::ECICommunicationPacket *>(trans->transData);
            
            if ( eciCommunicationPacket != NULL ) {
                
                switch (eciCommunicationPacket->command) {
                        
                    case AS_Network_Types::eci_Query:
                        
                        {
                            
                            std::cout << this->toString() << ": eci_Query" << std::endl;
                            
                            // All work is handled in the port handler, which does the following:
                            //
                            // 1) Obtain architecture types and whether to swap bytes.
                            // 2) Respond to the client with the ECI version number (defined in AS_Network_Types).
                            //
                            // All that remain is to do what ever is needed in this delegate (which is up to the delegate).
                            
                        }
                        
                        break;
                        
                    case AS_Network_Types::eci_Exit:
                        
                        std::cout << this->toString() << ": eci_Exit" << std::endl;
                        
                        // Do whatever the delegate needs to do to respond to an ECI exit command.
                        
                        // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                        eciCommand = AS_Network_Types::eci_OK;
                        connectionObject->fwrite(&(eciCommand), 1, 1);
                        
                        break;
                        
                    case AS_Network_Types::eci_BeginRecording:
                        
                        std::cout << this->toString() << ": eci_BeginRecording" << std::endl;
                        
                        // Do whatever the delegate needs to do to respond to an ECI begin recording command.
                        
                        // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                        eciCommand = AS_Network_Types::eci_OK;
                        connectionObject->fwrite(&(eciCommand), 1, 1);
                        
                        break;
                        
                    case AS_Network_Types::eci_EndRecording:
                        
                        std::cout << this->toString() << ": eci_EndRecording" << std::endl;
                        
                        // Do whatever the delegate needs to do to respond to an ECI end recording command.
                        
                        // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                        eciCommand = AS_Network_Types::eci_OK;
                        connectionObject->fwrite(&(eciCommand), 1, 1);
                        
                        break;
                        
                    case AS_Network_Types::eci_Attention:
                        
                        std::cout << this->toString() << ": eci_Attention" << std::endl;
                        
                        // Do whatever the delegate needs to do to respond to an ECI in attention command.
                        
                        // Nothing gets written back to the client for this command.
                        
                        break;
                        
                    case AS_Network_Types::eci_ClockSynch:
                        
                        std::cout << this->toString() << ": eci_ClockSynch" << std::endl;
                        
                        {
                            
                            // Do whatever the delegate needs to do to respond to an ECI in attention command.
                            //
                            // The data portion of the ECI communication packet will be a 4-byte value.
                            //
                            int32_t clockSynch = 0;
                            
                            if ( (eciCommunicationPacket->data != NULL) && (eciCommunicationPacket->dataLength == 4) ) {
                                
                                clockSynch = *(reinterpret_cast<int32_t *>(eciCommunicationPacket->data));
                                
                                if ( eciCommunicationPacket->swapBytes == true ) {
                                    
                                    UtilityFunctions::swapUINT32_t(reinterpret_cast<uint32_t *>(&clockSynch));
                                    
                                }
                                
                            }
                            
                            // Output the clock synch. value obtained.
                            std::cout << this->toString() << ": clock synch. value: " << clockSynch << std::endl;
                            
                            // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                            eciCommand = AS_Network_Types::eci_OK;
                            connectionObject->fwrite(&(eciCommand), 1, 1);
                            
                        }
                        
                        break;
                        
                    case AS_Network_Types::eci_NTPClockSynch:
                        
                        std::cout << this->toString() << ": eci_NTPClockSynch" << std::endl;
                        
                        {
                            
                            // Do whatever the delegate needs to do to respond to an ECI in attention command.
                            //
                            // The data portion of the ECI communication packet will be a 8-byte value in two parts,
                            // the first is the seconds part, the second is the parts of a second part.
                            //
                            uint32_t seconds = 0;
                            uint32_t partsOfASecond = 0;
                            if ( (eciCommunicationPacket->data != NULL) && (eciCommunicationPacket->dataLength == 8) ) {
                                
                                seconds = *(reinterpret_cast<uint32_t *>(eciCommunicationPacket->data));
                                partsOfASecond = *(reinterpret_cast<uint32_t *>((eciCommunicationPacket->data) + 4));
                                
                                if ( eciCommunicationPacket->swapBytes == true ) {
                                    
                                    UtilityFunctions::swapUINT32_t(&seconds);
                                    UtilityFunctions::swapUINT32_t(&partsOfASecond);
                                    
                                }
                                
                            }
                            
                            // Output the clock synch. value obtained.
                            std::cout << this->toString() << ": ntp clock synch. value (seconds, parts of seconds): "
                            << seconds << ", " << partsOfASecond << std::endl;
                            
                            // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                            eciCommand = AS_Network_Types::eci_OK;
                            connectionObject->fwrite(&(eciCommand), 1, 1);
                            
                        }
                        
                        break;
                        
                    case AS_Network_Types::eci_NTPReturnClockSynch:
                        
                        std::cout << this->toString() << ": eci_NTPReturnClockSynch" << std::endl;
                        
                        {
                            
                            // Do whatever the delegate needs to do to respond to an ECI in attention command.
                            //
                            // The data portion of the ECI communication packet will be a 8-byte value in two parts,
                            // the first is the seconds part, the second is the parts of a second part.
                            //
                            uint32_t seconds = 0;
                            uint32_t partsOfASecond = 0;
                            if ( (eciCommunicationPacket->data != NULL) && (eciCommunicationPacket->dataLength == 8) ) {
                                
                                seconds = *(reinterpret_cast<uint32_t *>(eciCommunicationPacket->data));
                                partsOfASecond = *(reinterpret_cast<uint32_t *>((eciCommunicationPacket->data) + 4));
                                
                                if ( eciCommunicationPacket->swapBytes == true ) {
                                    
                                    UtilityFunctions::swapUINT32_t(&seconds);
                                    UtilityFunctions::swapUINT32_t(&partsOfASecond);
                                    
                                }
                                
                            }
                            
                            // Output the clock synch. value obtained.
                            std::cout << this->toString() << ": ntp clock synch. value (seconds, parts of seconds): "
                            << seconds << ", " << partsOfASecond << std::endl;
                            
                            // This command excepts a return. We will just send back the time we got.
                            uint8_t eci_NTPReturnClockSynch = AS_Network_Types::eci_NTPReturnClockSynch;
                            connectionObject->fwrite(&(eci_NTPReturnClockSynch), 1, 1);
                            
                            connectionObject->fwrite(eciCommunicationPacket->data, 8, 1);
                            
                        }
                        
                        break;
                        
                    case AS_Network_Types::eci_EventData:
                        
                    {
                        
                        std::cout << this->toString() << ": eci_EventData" << std::endl;
                        
                        // This command receives ECI event data. EGI's application support layer has functionality for
                        // encoding and decoding ECI event data.
                        if ( eciCommunicationPacket->data != NULL ) {
                            
                            ECIEvent::EncodedEvent *encodedEvent = new ECIEvent::EncodedEvent();
                            encodedEvent->data = eciCommunicationPacket->data;
                            encodedEvent->dataLength = eciCommunicationPacket->dataLength;
                            
                            Event *event = ECIEvent::decodeEvent(encodedEvent,
                                                                 eciCommunicationPacket->swapBytes,
                                                                 0,
                                                                 0);
                            
                            // Debug.
                            //
                            // Output some basic event data.
                            if ( event != NULL ) {
                                
                                std::cout << this->toString() << ": ------" << std::endl;
                                std::cout << this->toString() << ": event:" << std::endl;
                                std::cout << this->toString() << "    begin time: " << localStringWrap(event->getBeginTime()) << std::endl;
                                std::cout << this->toString() << "    duration: " << event->getDuration() << std::endl;
                                std::cout << this->toString() << "    code: " << localStringWrap(event->getCode()) << std::endl;
                                std::cout << this->toString() << "    label: " << localStringWrap(event->getLabel()) << std::endl;
                                std::cout << this->toString() << "    description: " << localStringWrap(event->getDescription()) << std::endl;
                                std::cout << this->toString() << "    source device: " << localStringWrap(event->getSourceDevice()) << std::endl;
                                
                                std::cout << this->toString() << ": ------" << std::endl;
                                std::cout << this->toString() << ":    keys:" << std::endl;
                                
                                std::vector<Key *> *keys = event->getKeys();
                                if ( keys != NULL ) {
                                    
                                    for(std::vector<Key *>::iterator itr = keys->begin();
                                        itr != keys->end();
                                        ++itr){
                                        
                                        Key *key = *itr;
                                        
                                        if ( key != NULL ) {
                                            
                                            std::cout << this->toString() << ": ------" << std::endl;
                                            std::cout << this->toString() << ":    key:" << std::endl;
                                            std::cout << this->toString() << "       key code: " << localStringWrap(key->getKeyCode()) << std::endl;
                                            std::cout << this->toString() << "       description: " << localStringWrap(key->getDescription()) << std::endl;
                                            std::cout << this->toString() << "       data: " << localStringWrap(key->getData()) << std::endl;
                                            std::cout << this->toString() << "       dataType: " << localStringWrap(key->getDataType()) << std::endl;
                                            
                                        }
                                        
                                    }
                                    
                                }
                                std::cout << this->toString() << ": ------" << std::endl;
                                
                            }
                            
                            // Cleanup.
                            RELEASE(event);
                            
                            // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                            eciCommand = AS_Network_Types::eci_OK;
                            connectionObject->fwrite(&(eciCommand), 1, 1);
                            
                        }
                        
                        // This command has an AS_Network_Types::ECICommandType write-back (see note above).
                        eciCommand = AS_Network_Types::eci_Failure;
                        connectionObject->fwrite(&(eciCommand), 1, 1);

                        break;
                        
                    }
                        
                        break;
                    default:
                        
                        // This will be seen by the delegate too.
                        
                        std::cout << this->toString() << "error: eci command not recognized" << std::endl;
                        break;
                        
                }
                
            } else {
                
                parseError = true;
                
            }
			
			
			// Check for a parse error.
			if(parseError == true){
				std::cout << this->toString() << ": eci command parse error" << std::endl;
			}
			
		}
		
		// Check for exit request.
		if(exitFlag == true){
			
            
		}
		
		trans->release();
	}
	
	return NULL;
}

void *ECICommandDelegate::send(AS_TCP_PortHandlerDelegate::TransactionPacketRef trans, void *userRef){return NULL;}

void ECICommandDelegate::connnectionError(AS_TCP_PortHandler::ConnectionError error){}

//####################################
//Class methods.
//####################################
//####################################
//End - Class methods.
//####################################

//####################################
//End - Public section.
//####################################

//####################################
//Protected section.
//####################################
//####################################
//End - Protected section.
//####################################

//####################################
//Private section.
//####################################
//####################################
//End - Private section.
//####################################
