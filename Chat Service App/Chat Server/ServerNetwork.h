#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

enum TYPE {
     OK, ERROR,
	LOGIN,
	REGISTER,
	MESSAGE
};

class ServerNetwork{
     sf::TcpListener listener;
     std::vector<sf::TcpSocket *> client_array;

     unsigned short listen_port;
public:
     ServerNetwork(unsigned short);
     void ConnectClients(std::vector<sf::TcpSocket *> *);
     void DisconnectClient(sf::TcpSocket *, size_t);

     bool SendPacket(sf::TcpSocket *, sf::Int8);
     void ReceivePacket(sf::TcpSocket *, size_t);

     void BroadcastPacket(sf::Packet &, sf::IpAddress, unsigned short);

     void ManagePackets();
     void Run();
};
