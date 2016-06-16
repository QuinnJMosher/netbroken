//#include <string>;
#include <iostream>

#pragma comment (lib, "wininet"   )
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "NetBroken.h"

int main(int cargs, char* vargs[]) {

	//activate libs decribe features requested
	//WSAData data;
	//if (WSAStartup(MAKEWORD(2, 2), &data) != NO_ERROR) {
	//	exit(1);//failed to start
	//}
	ntbrk::initNetworking();

	//create handle SOCKET is a int typdef
	/*SOCKET socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socketHandle <= 0) {
		WSACleanup();
		exit(2);
	}*/

	//DWORD param = 1;
	//ioctlsocket(socketHandle, FIONBIO, &param); //prevents the socket from blocking the tread while trying to read;

	////internet address for sockets
	//sockaddr_in address;

	////address.sin_family           = AF_INET;//the type same as first param in socket
	////address.sin_addr.S_un.S_addr = INADDR_ANY;//accepts info from all adresses
	////address.sin_port             = htons(50000); //the port we're listening to, SHOULD ALWAYS BE A SHORT, htons fixes deferences between network standards and compy standards

	//address = ntbrk::stoa("0.0.0.0:50000");

	////attach handle to socket
	//bind(socketHandle, (sockaddr*)&address, sizeof(sockaddr_in));//retuns if less than zero then it has failed

	ntbrk::Socket mySocket = ntbrk::Socket();

	mySocket.Open("0.0.0.0:50000");

	//TCP
		//connect()
		//send()
		//receive()
	//UDP
	sockaddr_in outAddress;
	sockaddr_in inAddress;
	//int inLen = sizeof(sockaddr_in);
	char outBuffer[256] = "this isn't an interesting sentence - Quinn";
	char inBuffer[256] = "this is a default string";
	//the place to send to
	//esme's ipv4 10.15.22.54:50000

	std::cin.getline(outBuffer, 255);

	char targetAddress[40];
	std::cin >> targetAddress;
	outAddress = ntbrk::stoa(targetAddress);

	//sendto(  socketHandle, outBuffer, 40, 0, (sockaddr*)&outAddress, sizeof(sockaddr_in));//both return # of bytes
	//recvfrom(socketHandle, inBuffer,  40, 0, (sockaddr*)&inAddress,  &inLen);

	std::cout << mySocket.Send(outBuffer, 256, &outAddress) << std::endl;
	Sleep(2000);
	std::cout << mySocket.Recv(inBuffer, 256, &inAddress) << std::endl;

	std::cout << inBuffer << std::endl;
	system("Pause");

	//kill socket
	//closesocket(socketHandle);
	mySocket.Close();
	//close libs
	/*WSACleanup();*/
	ntbrk::exitNetworking();
	return 0;//exit
}