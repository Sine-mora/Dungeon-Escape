#include <iostream>
#include <string>
#include "Server.h"

/// <summary>
/// Create a server object with default values. Filled in later functions
/// </summary>
Server::Server() : m_server{ nullptr }, m_address{}, m_event{} {

}

Server::~Server() {
	ServerShutdown();
}

/// <summary>
/// Atexit - When terminating the program. 
/// Host_destroy - Server is of type pointer; Must be destroyed.
/// </summary>
void Server::ServerShutdown() {
	atexit(enet_deinitialize);
	enet_host_destroy(m_server);
}

/// <summary>
/// Initialize ENet.
/// </summary>
/// <returns>Returns 1 on failure or 0 on success </returns>
bool Server::ServerInit() {
	
	if (enet_initialize() != 0) {
		std::cerr << "Error initializing ENet";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/// <summary>
/// Create the Server with address of HOST_ANY
/// </summary>
/// <returns>Returns 1 on failure or 0 on success</returns>
bool Server::CreateServer() {

	m_address.host = ENET_HOST_ANY;
	m_address.port = 7777;

	m_server = enet_host_create(&m_address, 32, 1, 0, 0);

	if (m_server == NULL)
	{
		std::cerr << "Failed creating ENet server host";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Server::ParseData() {
	
}

/// <summary>
/// Main loop, where it listens for connections every second.
/// </summary>
void Server::ServerListen() {
	while (true)
	{ 
		while (enet_host_service(m_server, &m_event, 1000) > 0)
		{
			enet_uint8* receivedData;
			uint8_t* SerializedData;
			std::vector<uint8_t> buff;

			switch (m_event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("New client connected from %x:%u.\n",
					m_event.peer->address.host,
					m_event.peer->address.port);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
			{
				std::cout << "\nA packet of length " << m_event.packet->dataLength << " containing \"" << m_event.packet->data << "\" was received from " <<
					m_event.peer->address.host << " : " << m_event.peer->address.port << " on channel " << static_cast<int>(m_event.channelID) << std::endl;

				receivedData = m_event.packet->data;
				SerializedData = reinterpret_cast<uint8_t*>(receivedData);

				buff.reserve(m_event.packet->dataLength);
				buff = std::vector<uint8_t>(SerializedData, SerializedData + m_event.packet->dataLength);
				data.Deserialize(SerializedData);

				std::cout << "\n Deserialized data size: " << data.GetPointX() << " " << data.GetPointY() << std::endl;		
				data.Print();
				//std::cout << " print out buffer: ";
				//SerializablePOD<uint8_t>::PrintVector(buff);
				break;

			}
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%x:%u disconnected.\n",
					m_event.peer->address.host,
					m_event.peer->address.port);
				break;
			}
		}
	}
}

//END GAME LOOP