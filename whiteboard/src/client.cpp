#include "client.h"
#include <thread>

client::client() {
	//initiate winsock, error handling
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Winsock initialization failed. Error: " << WSAGetLastError() << std::endl;
		return;
	}
	//open socket and bind
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Socket initialization failed. Error: " << WSAGetLastError() << std::endl;
		return;
	}

	server = false;
}

client::~client() {
	//cleanup
	closesocket(sock);
	WSACleanup();
}

client::send() {
	while (true) {
		//on 
	}
}

client::receive() {
	while (true) {
		sockaddr_in from;
		int fromSize = sizeof(from);
		int bytesReceived = recvfrom(sock, readBuff, sizeof(readBuff), 0, (sockaddr*)&from, &fromSize);
		if (bytesReceived > 0) {
			handlePacket();
		}
	}
}

client::signalHandler(int signal) {
	buildPacket(2/*placeholder to build disconnect packet and send */);
	exit(0);
}

client::buildPacket() {

}

client::handlePacket() {

}

client::updateWhiteboard() {

}


int main() {
	client c;
	signal(SIGINT, [](int signal) { c.signalHandler(signal); });
	std::thread sendThread(&client::send, &c);
	std::thread receiveThread(&client::receive, &c);

	sendThread.join();
	receiveThread.join();

}