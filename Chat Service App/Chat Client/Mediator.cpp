#include <iostream>
#include "Mediator.h"

Mediator::Mediator() {
	login_interface = new LoginInterface(this);
	chat_interface = new ChatInterface(this);
}

void Mediator::Login(){
	std::cout << "Login Callback\n";
	chat_interface->show();
}

void Mediator::Send(const std::string & message) {
	std::cout << "Send Callback\n";
}