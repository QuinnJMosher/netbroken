#pragma once

#pragma comment (lib, "wininet"   )
#pragma comment (lib, "wsock32.lib")
#pragma comment (lib, "ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <sstream>

namespace ntbrk {
	
	bool initNetworking() {
		WSAData data;
		return WSAStartup(MAKEWORD(2, 2), &data) != NOERROR;
	}

	bool exitNetworking() {
		return WSACleanup() == 0;
	}

	//format: 127.0.0.1:50000
	sockaddr_in stoa(const char* src, size_t len = 0) {

		sockaddr_in output;

		std::stringstream parser = std::stringstream();
		
		parser.str(src);
		std::string ssOut = "";

		std::getline(parser, ssOut, '.');
		output.sin_addr.S_un.S_un_b.s_b1 = std::stoi(ssOut);

		std::getline(parser, ssOut, '.');
		output.sin_addr.S_un.S_un_b.s_b2 = std::stoi(ssOut);

		std::getline(parser, ssOut, '.');
		output.sin_addr.S_un.S_un_b.s_b3 = std::stoi(ssOut);

		std::getline(parser, ssOut, ':');
		output.sin_addr.S_un.S_un_b.s_b4 = std::stoi(ssOut);

		std::getline(parser, ssOut);
		output.sin_port = htons(std::stoi(ssOut));

		output.sin_family = AF_INET;

		parser.flush();
		parser.clear();

		return output;
	}

	class Socket {
		int handle = 0;
	public:
		~Socket() { if (isOpen()) Close(); }

		bool isOpen() const { return handle >= 0; }
		bool Open(const char* listeningAdress,  bool blockesExicuion = true) {
			handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			if (isOpen()) {
				
				bind(handle, (sockaddr*)&stoa(listeningAdress), sizeof(sockaddr_in));

				if (!blockesExicuion) {
					DWORD param = 1;
					ioctlsocket(handle, FIONBIO, &param);
				}

			}

			return isOpen();
		}
		void Close() { closesocket(handle); }

		int Send(char* outBuffer, int bufferLength, sockaddr_in* target) {

			return sendto(handle, outBuffer, bufferLength, 0, (sockaddr*)target, sizeof(sockaddr_in));
		}
		int Recv(char* outBuffer, int bufferLength, sockaddr_in* source) {
			int inLen = sizeof(sockaddr_in);
			return recvfrom(handle, outBuffer, bufferLength, 0, (sockaddr*)source, &inLen);
		}

	};
}