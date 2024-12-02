#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#pragma comment(lib, "ws2_32.lib") // Automatically link the Winsock library

/*struct packet {
	uint_8 type; //0x01 for connect, 0x02 for disconnect, 0x03 for session end, 0x04 for client update, 0x05 for whiteboard command, 0x06 for whiteboard mask, 0x07 for whiteboard color
	char[] payload;
};*/

//custom equality operator for sockaddr_in
inline bool operator==(const sockaddr_in& a, const sockaddr_in& b) {
	return a.sin_family == b.sin_family &&
		a.sin_port == b.sin_port &&
		a.sin_addr.s_addr == b.sin_addr.s_addr;
}


Class client{
	public:
		client();
		~client();
		void send();
		void receive();
		void handlePacket();
		void updateWhiteboard();

	protected:
		WSADATA wsaData;
		SOCKET sock;

		void sendPacket(unsigned int type, const std::vector<char>& payload, const sockaddr_in& client);


		std::vector<char> readBuff;

		std::vector<sockaddr_in> clientIPs; //list of each clients IP for transmission to clients
		//Whiteboard whiteboard; //instance of whiteboard sent to new members
};