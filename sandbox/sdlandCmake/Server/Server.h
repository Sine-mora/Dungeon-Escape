#ifndef SERVER_H
#define SERVER_H

#include "enet/enet.h"

class Server {
	private:
		ENetAddress m_address; // The address of the server
		ENetHost* m_server; // Creates a host(server) for communicating to peers. 
		ENetEvent m_event;
	public:

		struct points {
			int x;
			int y;
		}pointData;

		Server();
		~Server();
		bool ServerInit();
		bool CreateServer();
		void ServerListen();
		void ParseData();
		void ServerShutdown();
};
#endif // !SERVER_H