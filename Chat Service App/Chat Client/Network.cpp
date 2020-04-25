#include "Network.h"

void Network::Connect(const char * address, unsigned short port) {
	if (!isConnected) {
		if (local_socket.connect(address, port) == sf::Socket::Done) isConnected = true;
		else isConnected = false;
	}
}

void Network::Disconnect() {
	local_socket.disconnect();
	local_socket.setBlocking(false);
	receiver_thread.join();
	receiver_thread.~thread();
}

bool Network::Send(sf::Int8 type, const std::string & data) {
	sf::Packet packet;
	packet << type << username << data;

	if (packet.getDataSize() > 0) {
		if (local_socket.send(packet) == sf::Socket::Done) {
			return true;
		}
		else {
			isConnected = false;
			return false;
		}
	}
	return false;
}

bool Network::Receive(sf::Packet & packet) {
	if (local_socket.receive(packet) == sf::Socket::Done) {
		return true;
	}
	else {
		isConnected = false;
		return false;
	}
}

void Network::ReceivePackets(sf::TcpSocket * socket) {
	while (true) {
		sf::Packet packet;
		if (socket->receive(packet) == sf::Socket::Disconnected) isConnected = false;
		else {
			sf::Int8 type; std::string sender_username, message;
			packet >> type >> sender_username >> message;

			if (type == TYPE::MESSAGE) {
				//TODO: Print message to ChatClient
				std::cout << sender_username << ": " << message << std::endl; //temp
			}
		}
	}
}

void Network::StartReceiving() {
	receiver_thread = std::thread(&Network::ReceivePackets, this, &local_socket);
}
