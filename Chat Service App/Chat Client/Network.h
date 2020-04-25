#pragma once
#include <thread>

#undef Status
#undef None
#undef BadRequest
#include <SFML/Network.hpp>

enum TYPE {
     OK, ERROR,
	LOGIN,
	REGISTER,
	MESSAGE
};

class Network {
	sf::TcpSocket local_socket;
	std::thread receiver_thread;
public:
	bool isConnected = false;
	std::string username;

     Network(void *);
	void Connect(const char *, unsigned short);
	void Disconnect();

	bool Send(sf::Int8, const std::string &);
	bool Receive(sf::Packet &);

	void ReceivePackets(sf::TcpSocket *);
	void StartReceiving();
};
