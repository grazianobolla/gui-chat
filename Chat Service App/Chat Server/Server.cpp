#include "Server.h"
#include "../Standard.h"

Server::Server() {}

void Server::Start() {
	database.OpenDatabase("user_database.db");
	database.ExecuteQuery("CREATE TABLE IF NOT EXISTS users (username VARCHAR(16), password VARCHAR(32))");

	server_network.Initialize(this);
	server_network.Listen(2525);
	server_network.Run();

	database.CloseDatabase();
}

//Checks in the database for an entry containing "username" and "password" (Checks if the user is registered)
bool Server::CheckUser(const std::string & username, const std::string & password) {
	Data results;

	if (database.GetQueryResult("SELECT * FROM users WHERE username = '" + username + "' LIMIT 1", results)) {
		if (results.rows > 0 && results.vector[0] == username && results.vector[1] == password) return true;
	}
	return false;
}


bool Server::AddUser(const std::string & username, const std::string & password) {
	std::string query = "INSERT INTO users (username, password) VALUES (" + username + ", " + password + ")";
	if (database.ExecuteQuery(query.c_str())) return true;
	else return false;
}

//Receives a packet from any client and decides what to do with it
void Server::ProcessPacket(sf::TcpSocket * client, sf::Packet packet) {
	sf::Int8 type; std::string username, data;
	packet >> type >> username >> data;
	packet.clear();

	switch (type)
	{
		case (MESSAGE | REQUEST): {
			packet << (sf::Int8)(MESSAGE | OK) << username << data;
			server_network.BroadcastPacket(packet, client->getRemoteAddress(), client->getRemotePort());
			logl("User " << username << " sending: '" << data << "'");
			break;
		}

		case (LOGIN | REQUEST): {
			logl("Login request from " << username << " and password " << data << " request type " << std::to_string(type));
			if (CheckUser(username, data)) {
				server_network.SendPacket(client, LOGIN | OK);
				SendNotification("User " + username + " has logged in!", false);
			}
			else server_network.SendPacket(client, LOGIN | FAIL);
			break;
		}

		case (REGISTER | REQUEST): {
			logl("Register request from " << username << " and password " << data << " request type " << std::to_string(type));
			Data result;
			if (!database.GetQueryResult("SELECT username FROM users WHERE username = '" + username + "' LIMIT 1", result)) logl("aqui!");
			if (result.rows == 0 && database.ExecuteQuery("INSERT INTO users (username, password) VALUES ('" + username + "', '" + data + "')")) {
				server_network.SendPacket(client, REGISTER | OK);
				SendNotification("User " + username + " has registered for the first time!", false);
			}
			else server_network.SendPacket(client, REGISTER | FAIL);
			break;
		}

		default:
			break;
	}
}

//Sends a message with the NOTIFICATION flag
void Server::SendNotification(const std::string & message, bool to_all, sf::IpAddress exclude_address, unsigned short port) {
	sf::Packet packet;
	packet << (sf::Int8)(NOTIFICATION | OK) << "SERVER" << message;
	if(!to_all) server_network.BroadcastPacket(packet);
	else server_network.BroadcastPacket(packet, exclude_address, port);
	logl("Sended from SERVER sending: '" << message << "'");
}