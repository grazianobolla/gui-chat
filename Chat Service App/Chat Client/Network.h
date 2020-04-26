#pragma once
#include <thread>

#undef Status
#undef None
#undef BadRequest
#include <SFML/Network.hpp>

class Network {
	std::string address;
	sf::TcpSocket local_socket;
	std::thread receiver_thread;
public:
	bool isConnected = false;
	std::string username;

	Network(void *);
	void Connect(const char *, unsigned short);
	void Disconnect();
	void DisconnectThread();

	bool Send(sf::Int8, const std::string &);
	bool Receive(sf::Packet &);

	void ReceivePackets(sf::TcpSocket *);
	void StartReceiving();
};
