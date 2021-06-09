
//SERVER

#include <iostream>
#include "Server.h"

int main(int argc, char* args[]) {

	std::cout << "-== Server ON ==-\n";

	Server NewServer;
	NewServer.ServerInit();
	NewServer.CreateServer();
	NewServer.ServerListen();

	return EXIT_SUCCESS;
}