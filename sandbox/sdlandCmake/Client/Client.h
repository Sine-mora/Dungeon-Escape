#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "enet/enet.h"
#include "glm/glm.hpp"

class Client {
	private:
		ENetHost* m_client;
		ENetAddress m_address; // The address of the server to which it connects
		ENetEvent m_event;
		ENetPeer* m_peer; 



	public:

		struct points {
			int x;
			int y;
		}data;


		Client();
		~Client();
		bool Init();
		bool CreateClient();
		void SetHost();
		bool ConnectPeer();
		bool ConnectServer();
		void SendPacket(const points& data);
		void MsgLoop();
		void ReceiveComms(); //BEGIN GAME LOOP
		void Disconnect(); //END GAME LOOP
		void Shutdown();
		
};

#endif // !CLIENT_H