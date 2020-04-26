#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class ServerNetwork {
	sf::TcpListener listener;
	std::vector<sf::TcpSocket *> client_array;
public:
	ServerNetwork();
	void Initialize(void *);
	void Listen(unsigned short);
	void ConnectClients(std::vector<sf::TcpSocket *> *);
	void DisconnectClient(sf::TcpSocket *, size_t);

	bool SendPacket(sf::TcpSocket *, sf::Int8);
	void BroadcastPacket(sf::Packet &, sf::IpAddress, unsigned short);
	void ReceivePacket(sf::TcpSocket *, size_t);

	void ManagePackets();
	void Run();
};
