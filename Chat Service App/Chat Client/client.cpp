#include "Client.h"
#include <FL/fl_ask.H>

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
	network->isConnected = false;
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

		while (true) {
			sf::Packet packet; sf::Int8 server_response;
			network->Receive(packet);
			packet >> server_response;

			if (server_response == (LOGIN | OK)) {
				ChatWindow();
				break;
			}
			else if (server_response == (LOGIN | FAIL)) {
				fl_alert("Invalid credentials. (Are you registered?)");
				break;
			}
		}
	}
	else fl_alert("Lost connection with the server.");
}

void Client::Register(std::string username, std::string password) {
	logl("Register Callback with parameters " << username << " " << password);
	network->username = username;

	if (network->isConnected) {
		network->Send(REGISTER | REQUEST, password);

		while (true) {
			sf::Packet packet; sf::Int8 server_response;
			network->Receive(packet);
			packet >> server_response;

			if (server_response == (REGISTER | OK)) {
				ChatWindow();
				break;
			}
			else if (server_response == (REGISTER | FAIL)) {
				fl_alert("Server database error, the user may already be registered.");
				break;
			}
		}
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
	else if(type == (NOTIFICATION | OK)) chat_interface->PrintMessage(message, 'C');
}

void Client::ChatWindow() {
	address_interface->hide();
	register_interface->hide();
	login_interface->hide();
	chat_interface->show();
	network->StartReceiving();
}

void Client::StopChat() {
	register_interface->hide();
	chat_interface->hide();
	login_interface->hide();
	address_interface->show();
	network->DisconnectThread();
	logl("Closed and Disconnected");
}

void Client::LoginWindow() {
	address_interface->hide();
	chat_interface->hide();
	register_interface->hide();
	login_interface->show();
	logl("Opening Login Window");
}

void Client::RegisterWindow() {
	address_interface->hide();
	login_interface->hide();
	chat_interface->hide();
	register_interface->show();
	logl("Opening Register Window");
}

void Client::AddressWindow() {
	network->Disconnect();
	login_interface->hide();
	chat_interface->hide();
	register_interface->hide();
	address_interface->show();
	logl("Opening Address Window");
}