#include <iostream>
#include "Client.h"
/*
Client::Client() : m_client{ nullptr }, m_address{}, m_event{}, m_peer{ nullptr } {

}

bool Client::Init() {

	if (enet_initialize() != 0) {
		std::cerr << "Error initializing ENet\n";
		return EXIT_FAILURE;
	}
}

bool Client::CreateClient() {

	m_client = enet_host_create(NULL, 1, 1, 0, 0);
	if (m_client == NULL)
	{
		std::cerr << "Failed creating ENet client\n";
		return false;
	}
	return true;
}

bool Client::SetHost(ENetAddress address) {

	enet_address_set_host(&address, "127.0.0.1");
	address.port = 7777;
}

bool Client::ConnectPeer() {
	
	m_peer = enet_host_connect(m_client, &m_address, 1, 0);
	if (m_peer == NULL) {
		std::cerr << "Failed connecting to peer\n";
		return EXIT_FAILURE;
	}
}

bool Client::ConnectServer() {

	if (enet_host_service(m_client, &m_event, 5000) > 0 && m_event.type == ENET_EVENT_TYPE_CONNECT)
	{
		puts("Connection to 127.0.0.1:7777 succeeded\n");
	}
	else {
		enet_peer_reset(m_peer);
		puts("Connection to 127.0.0.1:7777 failed\n");
		return EXIT_SUCCESS;
	}
}

void Client::ReceiveComms() {

	//GAME LOOP

	while (enet_host_service(m_client, &m_event, 1000) > 0)
	{
		switch (m_event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
				m_event.packet->dataLength,
				m_event.packet->data,
				m_event.peer->address.host,
				m_event.peer->address.port,
				m_event.channelID);
			break;
		}
	}

	//END GAME LOOP
}

bool Client::Shutdown() {

	return (atexit(enet_deinitialize));
}

bool Client::Disconnect() {
	
	enet_peer_disconnect(m_peer, 0);

	while (enet_host_service(m_client, &m_event, 3000) > 0)
	{
		switch (m_event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(m_event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			puts("Disconnected.\n");
			break;
		}
	}
}



*/