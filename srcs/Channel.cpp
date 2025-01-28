#include "Channel.hpp"

Channel::Channel(const std::string& name) : name(name) {}

Channel::~Channel() {}

const	std::string& Channel::getName() const {
	return (name);
}

void	Channel::addClient(Client* client) {
	clients.insert(client);
}

void	Channel::removeClient(Client* client) {
	clients.erase(client);
}

bool	Channel::isEmpty() const {
	return clients.empty();
}

void	Channel::broadcast(const std::string& message, Client* sender) {
	for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != sender) {
			send((*it)->getFd(), message.c_str(), message.size(), 0);
		}
	}
}
