#include "Client.hpp"

Client::Client(int fd) : fd(fd), authenticated(false) {}

Client::~Client() {
	if (fd >= 0)
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

std::string	Client::getUsername() const {
	return (username);
}

void	Client::setUsername(const std::string& user) {
	username = user;
}

bool	Client::isNicknameSet() const {
	return (nicknameSet);
}

void	Client::setNicknameSet(bool set) {
	nicknameSet = set;
}

bool	Client::isUsernameSet() const {
	return (usernameSet);
}

void	Client::setUsernameSet(bool set) {
	usernameSet = set;
}

void Client::joinChannel(const std::string& channel) {
	if (std::find(channels.begin(), channels.end(), channel) == channels.end()) {
		channels.push_back(channel);
	}
}

void Client::leaveChannel(const std::string& channel) {
	channels.erase(std::remove(channels.begin(), channels.end(), channel), channels.end());
}

bool Client::isInChannel(const std::string& channel) {
	return std::find(channels.begin(), channels.end(), channel) != channels.end();
}

const std::vector<std::string>& Client::getChannels() const{
	return channels;
}
