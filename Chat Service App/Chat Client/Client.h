#pragma once
#include <iostream>

#include <FL/fl_ask.H>

#include "Network.h"
#include "LoginInterface.h"
#include "ChatInterface.h"

#define logl(x) std::cout << x << "\n"

class Client {
public:
	Network * network;
	LoginInterface * login_interface;
	ChatInterface * chat_interface;

	Client();

	void Login(const char *, const std::string &, const std::string &);
	void Register();
	void Send(const std::string &);

	void ProcessPacket(sf::Packet &);

	void StartChat();
	void StopChat();
};
