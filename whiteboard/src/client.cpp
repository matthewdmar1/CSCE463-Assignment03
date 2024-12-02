#include "client.h"
#include <thread>

client::client() : running(true), readBuff(1024, 0) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed. Error: " << WSAGetLastError() << std::endl;
        running = false;
        return;
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket initialization failed. Error: " << WSAGetLastError() << std::endl;
        running = false;
    }
}

client::~client() {
    running = false; // Stop threads
    closesocket(sock);
    WSACleanup();
}

void client::send() {
    while (running) {
        // Handle GUI input and send corresponding packets
    }
}

void client::receive() {
    while (running) {
        std::fill(readBuff.begin(), readBuff.end(), 0); // Clear the buffer
        sockaddr_in from;
        int fromSize = sizeof(from);
        int bytesReceived = recvfrom(sock, readBuff.data(), readBuff.size(), 0, (sockaddr*)&from, &fromSize);
        if (bytesReceived > 0) {
            uint8_t type = readBuff[0];
            handlePacket(type);
        }
    }
}

void client::handlePacket(uint8_t type) {
    switch (type) {
    case 0x03: // Disconnect
        running = false; // Stop threads
        break;
    case 0x04: { // Update client list
        clientIPs.clear();
        const char* data = readBuff.data() + 1; // Skip packet type
        while (*data) {
            sockaddr_in addr = {};
            if (inet_pton(AF_INET, data, &addr.sin_addr) > 0) {
                clientIPs.push_back(addr);
            }
            data += strlen(data) + 1; // Move to the next string
        }
        break;
    }
    case 0x05: // Update whiteboard
        // To be implemented
        break;
    }
}

void client::sendPacket(unsigned int type, const std::vector<char>& payload, const sockaddr_in& client) {
	std::vector<char> packet;
	packet.push_back(type);
	packet.insert(packet.end(), payload.begin(), payload.end());

	if (sendto(sock, packet.data(), packet.size(), 0, (sockaddr*)&client, sizeof(client)) == SOCKET_ERROR) {
		std::cerr << "Failed to send packet to " << inet_ntoa(client.sin_addr) << ". Error: " << WSAGetLastError() << std::endl;
	}

}


int main() {
	client c;
	std::thread sendThread(&client::send, &c);
	std::thread receiveThread(&client::receive, &c);

	sendThread.join();
	receiveThread.join();

    delete c;
}