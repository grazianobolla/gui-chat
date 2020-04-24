#pragma once
#include <string>
#include "LoginInterface.h"
#include "ChatInterface.h"

class Mediator {
	LoginInterface * login_interface;
	ChatInterface * chat_interface;

public:
	Mediator();
	
	void Login();
	void Register();
	void Send(const std::string &);
};