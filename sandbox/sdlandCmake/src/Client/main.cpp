
//Client

#include <iostream>
#include "enet/enet.h"
#include "Client.h"

int main() {

	Client NewClient;
	NewClient.Init();
	NewClient.CreateClient();
	NewClient.SetHost();
	NewClient.ConnectPeer();
	NewClient.ConnectServer();
	NewClient.ReceiveComms(); //GAME LOOP
	NewClient.Disconnect(); //END GAME LOOP
	
	return EXIT_SUCCESS;
}