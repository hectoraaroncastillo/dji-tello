#ifndef SOCKETUDP_H 
#define SOCKETUDP_H

#include<string>
#include <sstream>
#include<stdio.h>	//printf
#include<string.h> 	//memset
#include<stdlib.h> 	//exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <iostream>


/************************************ Macro definitions ********************************************/
#define BUFLEN 512				//Max length of buffer.
#define PORT 8888				//The port on which to listen for incoming data.
#define IP_ADDRESS "192.168.10.1"		//Tello IP Address.
#define PORT_SEND_DATA 8889			//Tello Port used to send data.
#define PORT_READ_DATA 8890			//Tello Port used to receive Tello state.
#define PORT_IMAGE 11111			//Tello Port used to receive Tello state.

/********************************** Structure definitions ******************************************/
typedef struct socketUDP{
	struct sockaddr_in si_me;
	int s;
}socketUDP;

/********************************** Prototype definitions ******************************************/
uint8_t initUDPSocket(socketUDP * socket, int port);
uint8_t connnectUDPSocket(socketUDP * socket);
std::string sendDataThroughUDP(socketUDP * socket, char * data, int size);
void readDataThroughUDP(socketUDP * socket, char * buff_out);




#endif /* SOCKETUDP_H */
