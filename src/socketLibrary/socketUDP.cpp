//**** Socket Library ******//
#include "socketUDP.hpp" 


//********	Declare some variables *******//
using namespace std;
uint8_t initUDPSocket(socketUDP * socket, int port)
{
	//********	Initialize variables *********//
	memset((char *) &socket->si_me, 0, sizeof(socket->si_me));
	socket->si_me.sin_family = AF_INET;
	socket->si_me.sin_port = htons(port);
	socket->si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	return connnectUDPSocket(socket); 
}


uint8_t connnectUDPSocket(socketUDP * socketVar)
{
	//********	Create the UDP Socket ************//
	if ((socketVar->s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		return 0u;
	}
	//********	Bind the UDP Socket ************//
	if( bind(socketVar->s , (struct sockaddr*)&socketVar->si_me, sizeof(socketVar->si_me) ) == -1)
	{
		return 0u;
	}

	printf("%s\n","UDP binded");
	return 1;
}


void readDataThroughUDP(socketUDP * socket, char * buff_out)
{
	//********	Declare and Initialize variables *********//
	char buf[BUFLEN];
	struct sockaddr_in si_other;
	socklen_t len = sizeof(si_other);
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT_READ_DATA);
	si_other.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	fflush(stdout);

	if (recvfrom(socket->s, buff_out, BUFLEN, 0, (struct sockaddr *) &si_other, &len) == -1)
	{
		buff_out = "fail";
		return;
	}
	
	//printf("Data: %s\n" , buf);
	//return buf;
}


std::string sendDataThroughUDP(socketUDP * socket, char * data, int size)
{
	//********	Declare and Initialize variables *********//
	char buf[BUFLEN];
	struct sockaddr_in si_other;
	socklen_t len = sizeof(si_other);
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT_SEND_DATA);
	si_other.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	if (sendto(socket->s, data, size, 0, (struct sockaddr*) &si_other, sizeof(sockaddr_in)) == -1)
	{
		return "fail";
	}
	fflush(stdout);
	if (recvfrom(socket->s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &len) == -1)
	{
		return "fail";
	}
	printf("Response: %s\n" , buf);
	return buf;
}


