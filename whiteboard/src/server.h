#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

#include "client.h"

#pragma comment(lib, "ws2_32.lib") // Automatically link the Winsock library

/*Author: Lance Hinton
* Intended functionality: 
* server sits in infinite loop receiving packets
* case 1: packet is a new client:
* add client IP to vector, send current whiteboard state to new client
* update clients by sending client list
* case 2: packet indicates client disconnect:
* remove client IP from vector, update clients by sending client list
* case 3: whiteboard update packet:
* make the necessary changes to the whiteboard
* this ensures the whiteboard is up to date for new clients joining the session
*/

Class server : public client{
	public:
		server();
		~server();
		void send() override;
		void receive() override;
		void addClient(sockaddr_in ip);
		void handleDisconnect(sockaddr_in ip);
		void endSession();

	private:
		//std::string inviteCode;
		
		//void createInviteCode();
		void updateClients(); //sends a copy of the clientIP vector
};