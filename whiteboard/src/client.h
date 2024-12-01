#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#pragma comment(lib, "ws2_32.lib") // Automatically link the Winsock library


Class client{
	public:
		client();
		~client();

	protected:
		WSADATA wsaData;
		SOCKET sock;

		char* readBuff;
		char* sendBuff;

		std::vector<sockaddr_in> clientIPs; //list of each clients IP for transmission to clients
		//Whiteboard whiteboard; //instance of whiteboard sent to new members
};