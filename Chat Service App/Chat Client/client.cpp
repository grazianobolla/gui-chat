#include "Client.h"
#include <FL/fl_ask.H>

Client::Client() { }

void Client::Run() {
	network = new Network(this);
	login_interface = new LoginInterface(this);
	chat_interface = new ChatInterface(this);
	Fl::lock();
}

void Client::Login(const char * address, const std::string & username, const std::string & password) {
	logl("Login Callback with parameters " << username << " " << password);
	network->username = username;
	network->Connect(address, 2525);

	if (network->isConnected) {
		network->Send(LOGIN | REQUEST, password);

		sf::Packet packet; sf::Int8 server_response;
		network->Receive(packet);
		packet >> server_response;

		if (server_response == (LOGIN | OK)) StartChat();
		else fl_alert("Invalid credentials. (Are you registered?)");
	}
	else fl_alert("Could not connect to the server.");
}

void Client::Register() {
	std::cout << "Register Callback\n";
}

void Client::Send(const std::string & message) {
	logl("Send Callback with parameters " << message);
	if (!network->Send(MESSAGE | REQUEST, message)) fl_alert("Could not send the message.");
}

void Client::ProcessPacket(sf::Packet & packet) {
	sf::Int8 type; std::string sender_username, message;
	packet >> type >> sender_username >> message;

	logl("Received from " << sender_username << ": '" << message << "'");
	if (type == (MESSAGE | OK)) chat_interface->PrintMessage(sender_username + ": " + message, 'A');
}

void Client::StartChat() {
	logl("Starting chat..");
	login_interface->hide();
	chat_interface->show();
	network->StartReceiving();
}

void Client::StopChat() {
	logl("Stopping chat..");
	chat_interface->hide();
	login_interface->show();
	network->Disconnect();
}