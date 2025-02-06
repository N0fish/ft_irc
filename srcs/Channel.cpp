#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& pass, int lim)
								: name(name), password(pass), limit(lim),
								inviteOnly(false), topicRestricted(false),
								topic(""), topicSetter(""), topicSetTime(0) {}

Channel::~Channel() {}

const	std::string& Channel::getName() const {
	return (name);
}

const	std::string& Channel::getPassword() const {
	return (password);
}

void	Channel::setPassword(const std::string& pass) {
	password = pass;
}

int	Channel::getLimit() const {
	return (limit);
}

void	Channel::setLimit(int lim) {
	limit = lim;
}

int	Channel::getUserCount() const {
	return (clients.size());
}

void	Channel::addClient(Client* client) {
	clients.insert(client);
}

void	Channel::removeClient(Client* client) {
	clients.erase(client);
}

bool	Channel::isBanned(Client* client) const {
	return (bannedClients.count(client));
}

void	Channel::banClient(Client* client) {
	bannedClients.insert(client);
}

void	Channel::unbanClient(Client* client) {
	bannedClients.erase(client);
}

bool	Channel::isInvited(Client* client) const {
	return (invitedClients.count(client));
}

void	Channel::addInvite(Client* client) {
	invitedClients.insert(client);
}

void	Channel::removeInvite(Client* client) {
	invitedClients.erase(client);
}

void	Channel::addOperator(Client* client) {
	operators.insert(client);
}

void	Channel::removeOperator(Client* client) {
	operators.erase(client);
}

bool	Channel::isEmpty() const {
	return (clients.empty());
}

bool	Channel::isOperator(Client* client) const {
	return (operators.find(client) != operators.end());
}

bool	Channel::isInviteOnly() const {
	return (inviteOnly);
}

void	Channel::setInviteOnly(bool value) {
	inviteOnly = value;
}

bool	Channel::isTopicRestricted() const {
	return (topicRestricted);
}

void	Channel::setTopicRestricted(bool value) {
	topicRestricted = value;
}

const std::string&	Channel::getTopic() const {
	return (topic);
}

void	Channel::setTopic(const std::string& newTopic, Client* setter) {
	topic = newTopic;
	topicSetter = setter->getNickname();
	topicSetTime = time(NULL);
}

bool	Channel::hasTopic() const {
	return (!topic.empty());
}

std::string	Channel::getTopicSetter() const {
	return (topicSetter);
}

time_t	Channel::getTopicSetTime() const {
	return (topicSetTime);
}

bool	Channel::supportsTopic() const {
	return (!topicRestricted);
}

void	Channel::broadcast(const std::string& message, Client* sender) {
	for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (*it != sender)
			(*it)->reply(message);
	}
}

const std::set<Client*>&	Channel::getClients() const {
	return (clients);
}

bool	Channel::isClientInChannel(Client* client) const {
	for (std::set<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		if ((*it)->getNickname() == client->getNickname()) {
			return (true);
		}
	}
	return (false);
}
