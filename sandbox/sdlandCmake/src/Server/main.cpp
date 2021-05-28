
//SERVER

#include <iostream>
#include "Server.h"

int main() {

	Server NewServer;
	
	NewServer.ServerInit();
	NewServer.CreateServer();
	NewServer.ServerListen();

	return EXIT_SUCCESS;
}