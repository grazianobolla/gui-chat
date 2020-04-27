#include "ServerNetwork.h"
#include "Server.h"

Server * server;
ServerNetwork::ServerNetwork() {}

void ServerNetwork::Initialize(void * data) {
	server = (Server *)data;
}

void ServerNetwork::Listen(unsigned short port) {
	logl("Chat Server Started");
	if (listener.listen(port) != sf::Socket::Done) logl("Could not listen");
}

void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket *> * client_array) {
	while (true) {
		sf::TcpSocket * new_client = new sf::TcpSocket();
		if (listener.accept(*new_client) == sf::Socket::Done) {
			new_client->setBlocking(false);
			client_array->push_back(new_client);
			logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size());
		}
		else {
			logl("Server listener error, restart the server");
			delete(new_client);
			break;
		}
	}
}

void ServerNetwork::DisconnectClient(sf::TcpSocket * socket_pointer, size_t position) {
	logl("Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << " disconnected, removing");
	server->SendNotification("User " + socket_pointer->getRemoteAddress().toString() + " disconnected.");
	socket_pointer->disconnect();
	delete(socket_pointer);
	client_array.erase(client_array.begin() + position);
}

bool ServerNetwork::SendPacket(sf::TcpSocket * socket, sf::Int8 type) {
	sf::Packet packet;
	packet << type;

	if (socket->send(packet) == sf::Socket::Done) return true;
	else return false;
}

void ServerNetwork::BroadcastPacket(sf::Packet & packet, sf::IpAddress exclude_address, unsigned short port) {
	if (packet.getDataSize() > 0) {
		for (size_t iterator = 0; iterator < client_array.size(); iterator++) {
			sf::TcpSocket * client = client_array[iterator];
			if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port) {
				if (client->send(packet) != sf::Socket::Done) {
					logl("Could not send packet on broadcast");
				}
			}
		}
	}
}

void ServerNetwork::BroadcastPacket(sf::Packet & packet) {
	if (packet.getDataSize() > 0) {
		for (size_t iterator = 0; iterator < client_array.size(); iterator++) {
			sf::TcpSocket * client = client_array[iterator];
			if (client->send(packet) != sf::Socket::Done) {
				logl("Could not send packet on broadcast all");
			}
		}
	}
}

void ServerNetwork::ReceivePacket(sf::TcpSocket * client, size_t iterator) {
	sf::Packet packet;

	sf::Socket::Status status = client->receive(packet);
	if (status == sf::Socket::Disconnected) DisconnectClient(client, iterator);
	else if (status == sf::Socket::Done) server->ProcessPacket(client, packet);
}

void ServerNetwork::ManagePackets() {
	while (true) {
		for (size_t iterator = 0; iterator < client_array.size(); iterator++) ReceivePacket(client_array[iterator], iterator);
		std::this_thread::sleep_for((std::chrono::milliseconds)10);
	}
}

void ServerNetwork::Run() {
	std::thread connetion_thread(&ServerNetwork::ConnectClients, this, &client_array);
	ManagePackets();
}