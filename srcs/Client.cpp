#include "Client.hpp"
#include "ListCommand.hpp"

Client::Client(int fd, std::string ip, uint16_t port) :	fd(fd), ip(ip), port(port),
							state(UNAUTHENTICATED),
							nicknameSet(false),
							usernameSet(false),
							lastActivity(time(NULL)),
							signonTime(time(NULL)) {
}

Client::~Client() {
	if (fd >= 0)
		close(fd);
}

int	Client::getFd() const {
	return (fd);
}

void	Client::reply(const std::string& message) {
	std::string formattedMessage = message;
	if (formattedMessage.size() < 2 
		|| formattedMessage.substr(formattedMessage.size() - 2) != "\r\n") {
		formattedMessage += "\r\n";
	}
	send(fd, formattedMessage.c_str(), formattedMessage.size(), 0);
	std::cout << "Client(" << fd << ") << " << formattedMessage << std::endl;
}

ClientState	Client::getState() const {
	return (state);
}

void	Client::setState(ClientState newState) {
	state = newState;
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

std::string	Client::getRealName() const {
	return (realname);
}

void	Client::setRealName(const std::string& name) {
	realname = name;
}
uint16_t	Client::getPort() const {
    return (port);
}

std::string	Client::getPrefix() const {
	return (nickname + "!" + username + "@server");
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

void	Client::joinChannel(const std::string& channel) {
	if (std::find(channels.begin(), channels.end(), channel) == channels.end()) {
		channels.push_back(channel);
	}
}

void	Client::leaveChannel(const std::string& channel) {
	channels.erase(std::remove(channels.begin(), channels.end(), channel), channels.end());
}

bool	Client::isInChannel(const std::string& channel) {
	return (std::find(channels.begin(), channels.end(), channel) != channels.end());
}

void	Client::addInvite(const std::string& channel) {
	invitedChannels.insert(channel);
}

bool	Client::isInvited(const std::string& channel) const {
	return (invitedChannels.count(channel) > 0);
}

const std::vector<std::string>& Client::getChannels() const{
	return (channels);
}

bool	Client::isRegistered() const {
	return (state == REGISTERED);
}

std::string	Client::getIpAddr() const {
	return (ip);
}

std::string	Client::getUserSymbol() const {
	return ("+");
}

void		Client::registerAction(Server *server) {
	(void)server;
	setState(REGISTERED);
	reply(":server 001 " + getNickname() + " :Welcome to the IRC network "+ getNickname() + "!!!");
	// client->reply(":" + _server->getHostname() + " 001 " + client->getNickname() +
	// 			" :Welcome to the IRC Network " + client->getNickname() + "!" +
	// 			client->getUsername() + "@" + _server->getHostname());

	// client->reply(":" + _server->getHostname() + " 002 " + client->getNickname() +
	// 			" :Your host is " + _server->getHostname() + ", running version 1.0");

	// std::stringstream	ss;
	// ss << _server->getCreationTime();
	// client->reply(":" + _server->getHostname() + " 003 " + client->getNickname() +
	// 			" :This server was created " + ss.str());

	// client->reply(":" + _server->getHostname() + " 004 " + client->getNickname() +
	// 			" " + _server->getHostname() + " 1.0 o i k l b t");
	reply("PING :server");
	// Command *listCmd = new ListCommand(server);
	// listCmd->execute(this, std::vector<std::string>());
	// delete listCmd;
}

std::string Client::getServer() const {
	return "irc.example.com"; // Здесь можно вернуть `server->getHostname()`, если передавать сервер в клиент
}

// время бездействия 
time_t	Client::getIdleTime() const {
	return time(NULL) - lastActivity;
}

time_t	Client::getSignonTime() const {
    return (signonTime);
}

std::string Client::getFormattedSignonTime() const {
	char buffer[30];
	struct tm *timeinfo = std::localtime(&signonTime);
	if (timeinfo) {
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
		return std::string(buffer);
	}
	return "Unknown";
}

time_t	Client::getLastActivity() const {
	return (lastActivity);
}

void	Client::updateActivity() {
	lastActivity = time(NULL);
}
