/**@file
 *  Low level api example.
 *  @author Robert Bell
 *  @date 10/04/2008
 *  @remarks
 *  Copyright 2008 EGI. All rights reserved.<br>
 *
 *
 *  This example code does the following:
 *  1) Example of command port interaction.
 *  2) Example of stream port interaction.
 *
 *  I'll post a notification port interaction shortly.
 *
 *  Caution: I have not tested this extensively yet (wrote it as a quick example in about 30min).
 */

#include <iostream>

//Network includes.
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_COMMAND_PORT 9877
#define SERVER_NOTIFICATION_PORT 9878
#define SERVER_STREAM_PORT 9879



#define COMMAND_SIZE 4096
#define NA300_SAMPLE_SIZE 1152
#pragma pack(1)
typedef struct{
  int64_t ampID;
  uint64_t length;
}AmpDataPacketHeader;
#pragma pack()


int main(int argc, char **args){

  struct sockaddr_in cservaddr, sservaddr;
  int csocket = -1;
  int ssocket = -1;
  FILE *cfin = NULL;
  FILE *cfout = NULL;
  FILE *sfin = NULL;
  FILE *sfout = NULL;

  csocket = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&cservaddr, sizeof(struct sockaddr_in));
  cservaddr.sin_family = AF_INET;
  cservaddr.sin_port = htons(SERVER_COMMAND_PORT);
  inet_pton(AF_INET, "127.0.0.1", &(cservaddr.sin_addr));
  
  if(::connect(csocket, (const struct sockaddr *)&cservaddr, sizeof(struct sockaddr_in)) == 0){
    cfin = fdopen(csocket, "r");
    cfout = fdopen(csocket, "w");

    // This is an example of sending the power on command.
    char *power_on = "(sendCommand cmd_SetPower 0 0 1)\n";
    if((cfin != NULL) && (cfout != NULL)){
      if((fwrite(power_on,strlen(power_on),1,cfout)!=1)||(fflush(cfout)!=0)){ //Don't send the null terminator!!
	std::cerr << "err: command connection most likely terminated" << std::endl;
	close(csocket);
      }
      else{
	//Now, wait for a return.

	//Look at: char command[AS_Network_Types::COMMAND_SIZE];
	char command_response[COMMAND_SIZE];
	size_t nObj = 1;

	if(fgets((char *)command_response,COMMAND_SIZE,cfin) != NULL){
	  std::cout << "command response: " << command_response;
	}
	else{
	  std::cerr << "err: command connection most likely terminated" << std::endl;
	  close(csocket);
	}
      }
    }
    else{
      std::cerr << "err: null command read or write handle" << std::endl;
    }
  }
  else{
    std::cout << "error: failed to connect to command port" << std::endl;
  }

  //######
  // Now try the stream port.
  //######
  // Important Note:
  // The command to the stream port goes over in binary.

  ssocket = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&sservaddr, sizeof(struct sockaddr_in));
  sservaddr.sin_family = AF_INET;
  sservaddr.sin_port = htons(SERVER_STREAM_PORT);
  inet_pton(AF_INET, "127.0.0.1", &(sservaddr.sin_addr));
  
  if(::connect(ssocket, (const struct sockaddr *)&sservaddr, sizeof(struct sockaddr_in)) == 0){
    sfin = fdopen(ssocket, "r");
    sfout = fdopen(ssocket, "w");

    if((sfin != NULL) && (sfout != NULL)){

      // Register to listen to amp id 0;
      char *register_command = new char [COMMAND_SIZE];
      (reinterpret_cast<int64_t *>(register_command))[0] = 0; // This field is not really used yet.
      (reinterpret_cast<int64_t *>(register_command))[1] = 101; // Use: AS_Network_Types::cmd_ListenToAmp
      (reinterpret_cast<int64_t *>(register_command))[2] = 0;

      //Adjust for platform.                                                                                                                                                 
#ifdef __i386__
      int32_t *tmpData = reinterpret_cast<int32_t *>(register_command);
      for(int i=0;i<3;i++){
	int location = i*2;
	int32_t tmpValue = -1;
	tmpData[location] =htonl(tmpData[location]);
	tmpData[location+1] =htonl(tmpData[location+1]);
	tmpValue = tmpData[location];
	tmpData[location] = tmpData[location+1];
	tmpData[location+1] = tmpValue;
      }
#endif

      if((fwrite(register_command,COMMAND_SIZE,1,sfout)!=1)||(fflush(sfout)!=0)){
	std::cerr << "-connection most likely terrminated-" << std::endl;
	close(ssocket);
      }
      else{
	// Ok, now read any incoming data.
	
	char *data = NULL;
	AmpDataPacketHeader ampDataPacketHeader;
	size_t nObj = 1;

	while(fread(&ampDataPacketHeader,sizeof(AmpDataPacketHeader),nObj,sfin) == nObj){
	
	  //Adjust for platform.                                                                                                                                                 
#ifdef __i386__
	  int32_t *tmpData = reinterpret_cast<int32_t *>(&ampDataPacketHeader);
	  for(int i=0;i<2;i++){
	    int location = i*2;
	    int32_t tmpValue = -1;
	    tmpData[location] =ntohl(tmpData[location]);
	    tmpData[location+1] =ntohl(tmpData[location+1]);
	    tmpValue = tmpData[location];
	    tmpData[location] = tmpData[location+1];
	    tmpData[location+1] = tmpValue;
	  }
#endif
	  int64_t ampID = ampDataPacketHeader.ampID;
	  uint64_t size = ampDataPacketHeader.length;
	  if(size>0){
	    data = new char[size];
	    if(fread(data,size,nObj,sfin) == nObj){
	      std::cout << "got data ... details: " << size << " bytes " << size / NA300_SAMPLE_SIZE << " samples" << std::endl;
	      delete[] data;
	    }
	    else{
	      delete[] data;
	      break;
	    }
	  }
	}
      }
    }
    else{
      std::cerr << "err: null stream read or write handle" << std::endl;
    }
  }
  else{
    std::cout << "error: failed to connect to stream port" << std::endl;
  }

  if(csocket != -1)
    close(csocket);
  if(ssocket != -1)
    close(ssocket);

  exit(0);
}
