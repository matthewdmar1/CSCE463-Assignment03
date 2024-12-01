#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>

#pragma comment(lib, "ws2_32.lib") // Automatically link the Winsock library

Class server{
	public:
		server();
		~server();
		void initiateSocket(sockaddr ip);
		void handleDisconnect(sockaddr ip);
		void updateClients(); //sends a copy of the clientIP vector
		void readPacket();

	private:
		WSADATA wsaData;

		char* readBuff;
		char* sendBuff;

		std::string inviteCode;
		std::vector<socket> clientSocks; //list of sockets to each client
		std::vector<sockaddr> clientIPs; //list of each clients IP for transmission to clients
		//Whiteboard whiteboard; //instance of whiteboard sent to new members

		void createInviteCode();
};