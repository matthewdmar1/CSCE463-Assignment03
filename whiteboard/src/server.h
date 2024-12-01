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


	private:
		std::string inviteCode;
		std::vector<socket> clientSocks;
		std::vector<sockaddr> clientIPs;

		void createInviteCode();
};