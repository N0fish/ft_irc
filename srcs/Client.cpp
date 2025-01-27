#include "Client.hpp"

Client::Client(int fd) : fd(fd), authenticated(false) {}

Client::~Client() {
	close(fd);
}

int	Client::getFd() const {
	return (fd);
}

bool	Client::isAuthenticated() const {
	return (authenticated);
}

void	Client::setAuthenticated(bool auth) {
	authenticated = auth;
}

std::string	Client::getPartialMessage() const {
	return (partialMessage);
}

void	Client::setPartialMessage(const std::string& message) {
	partialMessage = message;
}

std::string	Client::getNickname() const {
	return (nickname);
}

void	Client::setNickname(const std::string& nick) { 
	nickname = nick; 
}
