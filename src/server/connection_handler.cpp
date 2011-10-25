#include "connection_handler.h"

ConnectionHandler::ConnectionHandler(Server* server) {
	this->server = server;
};

void ConnectionHandler::addClient(Client* client) {
	client_list->push_back(client);
}

int ConnectionHandler::countClients(void) {
	return client_list.size();
}

void ConnectionHandler::removeClient(int id) {
	client_list->erase(client_list.begin()+id);
}

void interact(int id, char const* buffer) {
	// TODO
}

