#pragma once
#include <iostream>

#include "Network.h"
#include "AddressInterface.h"
#include "LoginInterface.h"
#include "RegisterInterface.h"
#include "ChatInterface.h"

#define logl(x) std::cout << x << std::endl

class Client {
public:
	Network * network;
	AddressInterface * address_interface;
	LoginInterface * login_interface;
	RegisterInterface * register_interface;
	ChatInterface * chat_interface;

	Client();

	void Run();
	bool Connect(const char *);
	void Login(const std::string &, const std::string &);
	void Register(const std::string &, const std::string &);
	void Send(const std::string &);

	void ProcessPacket(sf::Packet &);

	void StartChat();
	void StopChat();
	void LoginWindow();
	void RegisterWindow();
	void AddressWindow();
};
