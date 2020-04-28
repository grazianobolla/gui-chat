#include "Client.h"
#include <FL/fl_ask.H>

Client::Client() { }

void Client::Run() {
	network = new Network(this);
	interface_manager = new InterfaceManager(this);
	interface_manager->ShowAddressWindow();
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

//Sends "Login" request to the server, and waits for a proper answer
void Client::Login(const std::string & username, const std::string & password) {
	logl("Login Callback with parameters " << username << " " << password);
	network->username = username;

	if (network->isConnected) {
		network->Send(LOGIN | REQUEST, password);

		while (network->isConnected) {
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

//Sends "Register" request to the server, and waits for a proper answer
void Client::Register(std::string username, std::string password) {
	logl("Register Callback with parameters " << username << " " << password);
	network->username = username;

	if (network->isConnected) {
		network->Send(REGISTER | REQUEST, password);

		while (network->isConnected) {
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

//Sends "Message" request to the server
void Client::Send(const std::string & message) {
	logl("Send Callback with parameters " << message);
	if (!network->Send(MESSAGE | REQUEST, message)) fl_alert("Could not send the message.");
}

//Receives a packet from the server, and decides what to do with it
void Client::ProcessPacket(sf::Packet & packet) {
	sf::Int8 type; std::string sender_username, message;
	packet >> type >> sender_username >> message;

	logl("Received from " << sender_username << ": '" << message << "'");
	if (type == (MESSAGE | OK)) {
		interface_manager->chat_interface->PrintMessage(sender_username + ": " + message, 'A');
	}
	else if (type == (NOTIFICATION | OK)) {
		interface_manager->chat_interface->PrintMessage(message, 'C');
	}
}

//Starts the chat window and the thread
void Client::ChatWindow() {
	interface_manager->ShowChatWindow();
	network->StartReceiving();
}

//Stops the thread and closes the chat window
void Client::StopChat() {
	interface_manager->ShowAddressWindow();
	network->DisconnectThread();
}
