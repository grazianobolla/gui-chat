#include <iostream>
#include "Mediator.h"

Mediator::Mediator() {
	login_interface = new LoginInterface(this);
	chat_interface = new ChatInterface(this);
}

void Mediator::Login(const char * address, const std::string & username, const std::string & password){
	std::cout << "Login Callback with parameters " << username << " " << password << "\n";
	network.username = username;
	network.Connect(address, 2525);

	if (network.isConnected) {
		network.Send(TYPE::LOGIN, password);

		sf::Packet packet; bool logged_in;
		network.Receive(packet);
		packet >> logged_in;

		if (logged_in) StartChat();
		else fl_alert("Invalid credentials. (Are you registered?)");
	}
	else fl_alert("Could not connect to the server.");
}

void Mediator::Register() {
	std::cout << "Register Callback\n";
}

void Mediator::Send(const std::string & message) {
	std::cout << "Send Callback with parameters " << message << "\n";
	if (!network.Send(TYPE::MESSAGE, message)) fl_alert("Could not send the message.");
}

void Mediator::StartChat() {
	login_interface->hide();
	chat_interface->show();
	network.StartReceiving();
}

void Mediator::StopChat() {
	chat_interface->hide();
	login_interface->show();
	network.Disconnect();
}