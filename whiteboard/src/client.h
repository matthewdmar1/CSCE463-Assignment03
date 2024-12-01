#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#pragma comment(lib, "ws2_32.lib") // Automatically link the Winsock library

struct packet {
	uint_8 type; //0x01 for connect, 0x02 for disconnect, 0x03 for client update, 0x04 for whiteboard command, 0x05 for whiteboard mask, 0x06 for whiteboard color
	char[] payload;
};


Class client{
	public:
		client();
		~client();
		void send();
		void receive();
		void signalHandler(int signal);
		void buildPacket(uint_8 type);
		void handlePacket();
		void updateWhiteboard();

	protected:
		WSADATA wsaData;
		SOCKET sock;

		const bool server;

		char* readBuff;
		char* sendBuff;

		std::vector<sockaddr_in> clientIPs; //list of each clients IP for transmission to clients
		//Whiteboard whiteboard; //instance of whiteboard sent to new members
};