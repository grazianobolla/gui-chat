#pragma once
#include <thread>
#include <SFML/Network.hpp>
#include <iostream>

enum TYPE {
	LOGIN, LOGIN_OK,
	MESSAGE
};

class Network {
	sf::TcpSocket local_socket;
	std::thread receiver_thread;
public:
	bool isConnected = false;
	std::string username;

	void Connect(const char *, unsigned short);
	void Disconnect();

	bool Send(sf::Int8, const std::string &);
	bool Receive(sf::Packet &);

	void ReceivePackets(sf::TcpSocket *);
	void StartReceiving();
};