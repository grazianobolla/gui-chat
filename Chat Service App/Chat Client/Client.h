#pragma once
#include <iostream>

#include "Network.h"
#include "LoginInterface.h"
#include "ChatInterface.h"

#define logl(x) std::cout << x << std::endl

class Client {
public:
	Network * network;
	LoginInterface * login_interface;
	ChatInterface * chat_interface;

	Client();

	void Run();
	void Login(const char *, const std::string &, const std::string &);
	void Register();
	void Send(const std::string &);

	void ProcessPacket(sf::Packet &);

	void StartChat();
	void StopChat();
};
