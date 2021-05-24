#include <iostream>
#include <enet.h>

int main() {
	
	if (enet_initialize() != 0) {
		std::cerr << "Error initializing ENet";
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize());
	
	ENetAddress address;	
	ENetHost* server;
	ENetEvent event;

	address.host = ENET_HOST_ANY;
	address.port = 7777;
	
	server = enet_host_create(&address, 32, 1, 0, 0);

	if (server == NULL)
	{
		std::cerr << "Failed creating ENet server host";
		return EXIT_FAILURE;
	}

	//GAME LOOP
	while (true)
	{
		while (enet_host_service(server, &event, 1000) > 0) 
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("New client connected from %x:%u.\n",
					event.peer->address.host,
					event.peer->address.port);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->address.host,
					event.peer->address.port,
					event.channelID);
				break;


			}
		}
	}

	//END GAME LOOP


	return 0;
}