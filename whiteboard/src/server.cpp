#include "server.h"


server::server() {
	server = true;
}

server::~server() {
}

/*void server::createInviteCode() {
	srand(clock(0));
	inviteCode = "";
	int rng;
	bool case; //true = uppercase, false = lowercase
	int letter; //standard alpabet range
	for (int i = 0; i < 6; i++) {
		rng = rand();
		case = rng % 2;
		letter = rng % 26;
		if (case) {
			inviteCode += static_cast<char>(letter + 65); //ascii offset for uppercase characters
		}
		else {
			inviteCode += static_cast<char>(letter + 97); //ascii offset for lowercase characters
		}
	}
}*/

void server::send() override {

}

void server::receive() override {

}

void server::addClient(sockaddr_in ip) {
	if (std::find(clientIPs.begin(), clientIPs.end(), ip)) {
		std::cerr << "Client is already connected" << std::endl;
		return;
	}

	clientIPs.push_back(ip);

	updateClients();

}

void server::handleDisconnect(sockaddr ip) {
	auto it = std::find(clientIPs.begin(), clientIPs.end(), ip);
	if (it != clientIPs.end()) {
		clientIPs.erase(it);
	} else {
		std::cerr << "IP not found in client list" << std::endl;
	}

}

void endSession() {
	
}

int main() {

}

