#pragma once
#include "Database.h"
#include "ServerNetwork.h"

class Server {
	Database database;
	ServerNetwork server_network;
public:
	Server();
	void Start();
	bool CheckUser(const std::string &, const std::string &);
	bool AddUser(const std::string &, const std::string &);
	void ProcessPacket(sf::TcpSocket *, sf::Packet);

	void SendNotification(const std::string &);
};