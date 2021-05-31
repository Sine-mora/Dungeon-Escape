#include <iostream>
#include "Client.h"
#include "glm/glm.hpp"

/// <summary>
/// Create a client object with default values. Filled in later functions
/// </summary>
Client::Client() : m_client{ nullptr }, m_address{}, m_event{}, m_peer{ nullptr } {
}

Client::~Client() {
	Shutdown();
}

/// <summary>
/// Initiliaze the ENet
/// </summary>
/// <returns>Returns 1 on failure or 0 on success</returns>
bool Client::Init() {

	if (enet_initialize() != 0) {
		std::cerr << "Error initializing ENet\n";
		return EXIT_FAILURE;
	}
	std::cout << "Client Initialized successfully!\n";
	return EXIT_SUCCESS;
}

/// <summary>
/// Create a client
/// </summary>
/// <returns>Returns 1 on failure or 0 on success</returns>
bool Client::CreateClient() {

	m_client = enet_host_create(NULL, 1, 1, 0, 0);
	if (m_client == NULL)
	{
		std::cerr << "Failed creating ENet client\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/// <summary>
/// ENet function returns the address of the given hostName in address on success
/// </summary>
void Client::SetHost() {

	if (enet_address_set_host(&m_address, "127.0.0.1") == 0) {
		m_address.port = 7777;	
	}
	else {
		std::cerr << "Failed setting address.\n";
	}
}

/// <summary>
/// Initiates a connection to a foreign host. 
/// </summary>
/// <returns>Returns 1 on failure or 0 on success</returns>
bool Client::ConnectPeer() {
	
	m_peer = enet_host_connect(m_client, &m_address, 1, 0);

	if (m_peer == NULL) {
		std::cerr << "Failed connecting to peer\n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/// <summary>
/// Waits for events on the host specified and shuttles packets between the host and its peers. 
/// </summary>
/// <returns>Returns 1 on failure or 0 on success</returns>
bool Client::ConnectServer() {

	if (enet_host_service(m_client, &m_event, 5000) > 0 && m_event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection to 127.0.0.1:7777 succeeded\n";
		return EXIT_SUCCESS;
	}
	else {
		enet_peer_reset(m_peer);
		std::cout << "Connection to 127.0.0.1:7777 failed\n";
		return EXIT_FAILURE;
	}
}

//BEGIN GAME LOOP

/// <summary>
/// Main loop, where it listens for communications
/// </summary>
void Client::ReceiveComms() {

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
}

//END GAME LOOP

/// <summary>
/// Disconnect the client from the server
/// </summary>
void Client::Disconnect() {
	
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

/// <summary>
/// Atexit - Called when terminating the program
/// </summary>
void Client::Shutdown() {

	if (atexit(enet_deinitialize) == 0) {
		std::cout << "Deinitializing the client.\n";
	}
	else {
		std::cout << "Failed deinitializing the client.\n";
	}
}
