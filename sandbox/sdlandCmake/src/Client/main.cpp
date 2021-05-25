#include <iostream>
#include "enet/enet.h"

int main() {



	return EXIT_SUCCESS;
}

/*
if (enet_initialize() != 0) {
	std::cerr << "Error initializing ENet\n";
	return EXIT_FAILURE;
}
atexit(enet_deinitialize);

ENetHost* client;
client = enet_host_create(NULL, 1, 1, 0, 0);
if (client == NULL)
{
	std::cerr << "Failed creating ENet client\n";
	return EXIT_FAILURE;
}

ENetAddress address;
ENetEvent event;
ENetPeer* peer;

enet_address_set_host(&address, "127.0.0.1");
address.port = 7777;

peer = enet_host_connect(client, &address, 1, 0);
if (peer == NULL) {
	std::cerr << "Failed connecting to peer\n";
	return EXIT_FAILURE;
}

if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
{
	puts("Connection to 127.0.0.1:7777 succeeded\n");
}
else {
	enet_peer_reset(peer);
	puts("Connection to 127.0.0.1:7777 failed\n");
	return EXIT_SUCCESS;
}

//GAME LOOP

while (enet_host_service(client, &event, 1000) > 0)
{
	switch (event.type)
	{
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

//END GAME LOOP

enet_peer_disconnect(peer, 0);

while (enet_host_service(client, &event, 3000) > 0)
{
	switch (event.type)
	{
	case ENET_EVENT_TYPE_RECEIVE:
		enet_packet_destroy(event.packet);
		break;
	case ENET_EVENT_TYPE_DISCONNECT:
		puts("Disconnected.\n");
		break;
	}
}
*/