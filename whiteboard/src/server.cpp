#include "server.h"

server::server() {
	createInviteCode();
}

server::~server() {
}

void server::createInviteCode() {
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
}

