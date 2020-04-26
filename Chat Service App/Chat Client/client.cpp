#include "Client.h"
#include <FL/fl_ask.H>

#include "../Standard.h"

Client::Client() { }

void Client::Run() {
	network = new Network(this);
	address_interface = new AddressInterface(this);
	login_interface = new LoginInterface(this);
	register_interface = new RegisterInterface(this);
	chat_interface = new ChatInterface(this);

	address_interface->show();
	Fl::lock();
}

bool Client::Connect(const char * address) {
	network->Connect(address, 2525);
	if (network->isConnected == false) {
		fl_alert("Could not connect to the server.");
		return false;
	}
	else return true;
}

void Client::Login(const std::string & username, const std::string & password) {
	logl("Login Callback with parameters " << username << " " << password);
	network->username = username;

	if (network->isConnected) {
		network->Send(LOGIN | REQUEST, password);

		sf::Packet packet; sf::Int8 server_response;
		network->Receive(packet);
		packet >> server_response;

		if (server_response == (LOGIN | OK)) StartChat();
		else if (server_response == (LOGIN | FAIL)) fl_alert("Invalid credentials. (Are you registered?)");
	}
	else fl_alert("Lost connection with the server.");
}

void Client::Register(const std::string & username, const std::string & password) {
	logl("Register Callback with parameters " << username << " " << password);

	if (network->isConnected) {
		network->Send(REGISTER | REQUEST, password);

		sf::Packet packet; sf::Int8 server_response;
		network->Receive(packet);
		packet >> server_response;

		if (server_response == (REGISTER | OK)) {
			network->username = username;
			StartChat();
		}
		else if (server_response == (REGISTER | FAIL)) fl_alert("Server database error, the user may already be registered.");
	}
	else fl_alert("Lost connection with the server.");
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
	logl("Starting chat");
	address_interface->hide();
	register_interface->hide();
	login_interface->hide();
	chat_interface->show();
	network->StartReceiving();
}

void Client::StopChat() {
	logl("Stopping chat");
	address_interface->hide();
	register_interface->hide();
	chat_interface->hide();
	login_interface->show();
	network->DisconnectWhileThread();
}

void Client::LoginWindow() {
	logl("Opening Login Window");
	address_interface->hide();
	chat_interface->hide();
	register_interface->hide();
	login_interface->show();
}

void Client::RegisterWindow() {
	logl("Opening Register Window");
	address_interface->hide();
	login_interface->hide();
	chat_interface->hide();
	register_interface->show();
}

void Client::AddressWindow() {
	logl("Opening Register Window");
	network->Disconnect();
	login_interface->hide();
	chat_interface->hide();
	register_interface->hide();
	address_interface->show();
}