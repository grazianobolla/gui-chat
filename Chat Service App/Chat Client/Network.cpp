#include "Network.h"
#include "Client.h"

namespace net {
	Client * client;
}

Network::Network(void * data) {
	net::client = (Client *)data;
}

void Network::Connect(const char * address, unsigned short port) {
	this->address = address;
	if (!isConnected) {
		if (local_socket.connect(address, port) == sf::Socket::Done) isConnected = true;
		else isConnected = false;
	}
}

void Network::DisconnectThread() {
	isConnected = false;
	local_socket.disconnect();
	receiver_thread.join();
	receiver_thread.~thread();
	logl("Disconnected and stopped the thread!");
}

void Network::Disconnect() {
	isConnected = false;
	local_socket.disconnect();
	logl("Disconnected!");
}


bool Network::Send(sf::Int8 type, const std::string & data) {
	sf::Packet packet;
	packet << type << username << data;

	if (packet.getDataSize() > 0) {
		if (local_socket.send(packet) == sf::Socket::Done) return true;
		else {
			isConnected = false;
			return false;
		}
	}
	return false;
}

bool Network::Receive(sf::Packet & packet) {
	if (local_socket.receive(packet) == sf::Socket::Done) return true;
	else {
		isConnected = false;
		return false;
	}
}

void Network::ReceivePackets(sf::TcpSocket * socket) {
	while (isConnected) {
		sf::Packet packet;
		if (socket->receive(packet) == sf::Socket::Disconnected) isConnected = false;
		else net::client->ProcessPacket(packet);
	}
}

void Network::StartReceiving() {
	receiver_thread = std::thread(&Network::ReceivePackets, this, &local_socket);
}