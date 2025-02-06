#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "libcmds.hpp"

Server::Server(int port, const std::string &password) : port(port),
                                                        password(password) {
	creationTime = time(NULL);
	initSocket();
	initializeCommands();
}

Server::~Server() {
	cleanup();
}

void	Server::cleanup()	{
	std::cout << "\n🧹 Server cleanup in progress..." << std::endl;
	close(serverSocket);

	for (size_t i = 0; i < clients.size(); ++i) {
		close(clients[i].fd);
	}
	clients.clear();
	std::vector<pollfd>().swap(clients);

	for (size_t i = 0; i < clientObjects.size(); ++i) {
		delete clientObjects[i];
	}
	clientObjects.clear();
	std::vector<Client *>().swap(clientObjects);

	for (std::map<std::string, Command *>::iterator it = commands.begin(); it != commands.end(); ++it) {
		delete it->second;
	}
	commands.clear();

	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end();) {
		delete it->second;
		std::map<std::string, Channel *>::iterator next = it;
		++next;
		channels.erase(it);
		it = next;
	}
	usedNicknames.clear();
	uniqueChannels.clear();
	std::cout << "\n👌 Server cleanup complete." << std::endl;
}

void	Server::initSocket() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		throw std::runtime_error("Failed to create socket");
	}

	int	opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw std::runtime_error("Failed to set socket options");
	}

	int	flags = fcntl(serverSocket, F_GETFL, 0);
	if (flags < 0 || fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) < 0) {
		throw std::runtime_error("Failed to set non-blocking mode");
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		throw std::runtime_error("Bind failed");
	}

	if (listen(serverSocket, 10) < 0) {
		throw std::runtime_error("Listen failed");
	}
	std::cout << "🏁 Server started on port " << port << std::endl;
}

void	Server::acceptConnection() {
	struct sockaddr_in	clientAddr;
	socklen_t			addrLen = sizeof(clientAddr);
	memset(&clientAddr, 0, sizeof(clientAddr));

	int	clientFd = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
	if (clientFd < 0) {
		if (errno != EWOULDBLOCK) {
			std::cerr << "Accept error" << std::endl;
		}
		return ;
	}

	char	clientIP[INET_ADDRSTRLEN];
	if (!inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN)) {
		std::cerr << "Failed to get client IP" << std::endl;
		return ;
	}

	struct pollfd	clientPoll;
	memset(&clientPoll, 0, sizeof(clientPoll));
	clientPoll.fd = clientFd;
	clientPoll.events = POLLIN;
	clients.push_back(clientPoll);

	uint16_t	ClientPort = ntohs(clientAddr.sin_port);
	clientObjects.push_back(new Client(clientFd, std::string(clientIP), ntohs(clientAddr.sin_port)));
	Client*		newClient = clientObjects.back();
	Channel*	general = getChannel("&system");
	if (!general) {
		general = createChannel("&system", "", NULL);
	}
	general->addClient(newClient);
	newClient->joinChannel("&system");
	std::cout	<< "New client connected: " << clientFd
				<< " (IP: " << clientIP << ", Port: " << ClientPort << ")"
				<< std::endl;
}

void	Server::handleClient(int clientFd) {
	char	buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	ssize_t	bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead <= 0) {
		if (bytesRead < 0 && errno != EWOULDBLOCK) {
			std::cerr << "Recv error for client " << clientFd << std::endl;
		}
		Client	*client = findClientByFd(clientFd);
		if (client)
			disconnectClient(client);
		return ;
	}

	Client	*client = findClientByFd(clientFd);
	if (!client) {
		return ;
	}

	std::string	message(buffer);
	client->setPartialMessage(client->getPartialMessage() + message);

	size_t	pos;
	while ((pos = client->getPartialMessage().find('\n')) != std::string::npos) {
		std::string	command = client->getPartialMessage().substr(0, pos);
		client->setPartialMessage(client->getPartialMessage().substr(pos + 1));

		if (command.empty())
			continue ;

		handleCommand(client, command);
		if (findClientByFd(clientFd) == NULL)
			return ;
	}
}

void	Server::initializeCommands() {
    commands["PASS"] = new PassCommand(this);
    commands["NICK"] = new NickCommand(this);
    commands["USER"] = new UserCommand(this);

    commands["JOIN"] = new JoinCommand(this);
    commands["PART"] = new PartCommand(this);
    commands["PRIVMSG"] = new PrivmsgCommand(this);
    commands["PING"] = new PingCommand(this);
    commands["PONG"] = new PongCommand(this);

    commands["KICK"] = new KickCommand(this);
    commands["INVITE"] = new InviteCommand(this);
    commands["TOPIC"] = new TopicCommand(this);
    commands["MODE"] = new ModeCommand(this);

    commands["USERHOST"] = new UserhostCommand(this);
    commands["LIST"] = new ListCommand(this);
    commands["QUIT"] = new QuitCommand(this);
    commands["WHOIS"] = new WhoisCommand(this);
    commands["INFO"] = new InfoCommand(this);
    commands["NAMES"] = new NamesCommand(this);
}

void	Server::removeClientFromChannels(Client *client) {
    if (client == NULL)
        return ;

    std::vector<std::string>	emptyChannels;
    for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
        it->second->removeClient(client);
        if (it->second->isEmpty()) {
            emptyChannels.push_back(it->first);
        }
    }

    for (size_t i = 0; i < emptyChannels.size(); ++i) {
        std::map<std::string, Channel *>::iterator it = channels.find(emptyChannels[i]);
        if (it != channels.end()) {
            delete it->second;
            channels.erase(it);
        }
    }
}

void	Server::disconnectClient(Client *client)
{
	if (!client)
		return ;

	int	fd = client->getFd();
	removeClientFromChannels(client);
	removeNickname(client->getNickname());
	for (std::vector<pollfd>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (it->fd == fd) {
			clients.erase(it);
			break ;
		}
	}

	for (std::vector<Client *>::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it) {
		if (*it == client) {
			delete client;
			*it = NULL;
			clientObjects.erase(it);
			break ;
		}
	}
	if (fd > 0)
		close(fd);
	std::cout	<< "Client(" << fd << ") disconnected"
				<< std::endl;
}

void	Server::handleCommand(Client *client, const std::string &command) {
	if (command.empty())
		return ;

	std::istringstream	iss(command);
	std::string			cmd;
	iss >> cmd;

	std::cout << "Client(" << client->getFd() << ") >> " << command << std::endl;
	if (!client->isRegistered() && cmd != "PASS" && cmd != "NICK" && cmd != "USER") {
		client->reply(ERR_NOTREGISTERED(this->getHostname(), client->getNickname()));
		return ;
	}

	if (commands.find(cmd) != commands.end()) {
		std::vector<std::string>	args;
		std::string					arg;
		while (iss >> arg) {
			args.push_back(arg);
		}
		commands[cmd]->execute(client, args);
	}
	else
		client->reply(ERR_UNKNOWNCOMMAND(this->getHostname(), cmd));
}

void Server::run() {
	struct pollfd	serverPoll;
	memset(&serverPoll, 0, sizeof(serverPoll));
	serverPoll.fd = serverSocket;
	serverPoll.events = POLLIN;

	clients.push_back(serverPoll);
	while (true) {
		int pollCount = poll(clients.data(), clients.size(), -1);
		if (pollCount < 0) {
			if (errno == EINTR)
				continue ;
			throw std::runtime_error("Poll failed");
		}

		for (size_t i = 0; i < clients.size(); ++i) {
			if (clients[i].revents & POLLIN) {
				if (clients[i].fd == serverSocket) {
					acceptConnection();
				} else {
					handleClient(clients[i].fd);
				}
			}
		}
	}
}

void	Server::removeNickname(const std::string &nickname) {
	if (!nickname.empty()) {
		usedNicknames.erase(nickname);
	}
}

void	Server::addNickname(const std::string &nickname) {
	if (!nickname.empty()) {
		usedNicknames.insert(nickname);
	}
}

bool	Server::isNicknameTaken(const std::string &nickname) const {
	return (usedNicknames.find(nickname) != usedNicknames.end());
}

const std::map<std::string, Channel *>	&Server::getChannels() const {
	return (channels);
}

const std::vector<std::string>	Server::getChannelsName() {
	std::vector<std::string>	resp;

	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++) {
		resp.push_back(it->second->getName());
	}
	return (resp);
}

bool	Server::isChannelNameTaken(const std::string &name) {
	return (uniqueChannels.find(name) != uniqueChannels.end());
}

std::string	Server::getPassword() const {
	return (password);
}

std::string	Server::getHostname() const {
	char	hostname[256];
	memset(hostname, 0, sizeof(hostname));

	if (gethostname(hostname, sizeof(hostname) - 1) != 0) {
		std::cerr << "Error: gethostname() failed, using 'localhost'" << std::endl;
		return ("localhost");
	}
	return (std::string(hostname));
}

Client	*Server::findClientByFd(int fd) {
	for (size_t i = 0; i < clientObjects.size(); ++i) {
		if (clientObjects[i]->getFd() == fd) {
			return (clientObjects[i]);
		}
	}
	return (NULL);
}

Channel	*Server::getChannel(const std::string &name) {
	if (channels.find(name) != channels.end()) {
		return (channels[name]);
	}
	return (NULL);
}

Channel	*Server::createChannel(const std::string &name, const std::string &pass, Client *creator) {
	if (channels.find(name) != channels.end())
		return (channels[name]);
	if (name[0] == '+')
		return (NULL);
	if (name[0] == '!' && uniqueChannels.find(name) != uniqueChannels.end())
		return (NULL);

	Channel	*newChannel = new Channel(name, pass);
	if (!newChannel)
		return (NULL);
	channels[name] = newChannel;
	if (name[0] == '!')
	{
		uniqueChannels.insert(name);
	}
	if (creator != NULL)
	{
		newChannel->addClient(creator);
		newChannel->addOperator(creator);
	}
	return (newChannel);
}

void	Server::deleteChannel(const std::string &channelName)	{
	if (channels.find(channelName) == channels.end())	{
		std::cerr << "Warning: Attempt to delete a non-existing channel: " << channelName << std::endl;
		return ;
	}

	std::map<std::string, Channel *>::iterator it = channels.find(channelName);
	if (it != channels.end()) {
		delete it->second;
		channels.erase(it);
	}
}

Client	*Server::findClientByNickname(const std::string &nickname) const {
	for (std::vector<Client *>::const_iterator it = clientObjects.begin(); it != clientObjects.end(); ++it) {
		Client *client = *it;
		if (client->getNickname() == nickname) {
			return (client);
		}
		if (client->getNickname() == nickname) {
			return (client);
		}
	}
	return (NULL);
}

time_t	Server::getCreationTime() const {
	return (creationTime);
}

std::string	Server::getVersion() const {
	return ("IRC Server v1.0");
}

std::string	Server::getOSInfo() const {
	return ("Running on Linux");
}

std::string	Server::getUptime() const {
	time_t	currentTime = time(NULL);
	time_t	uptime = currentTime - creationTime;
	int		days = uptime / (60 * 60 * 24);
	int		hours = (uptime % (60 * 60 * 24)) / (60 * 60);
	int		minutes = (uptime % (60 * 60)) / 60;

	char	uptimeStr[50];
	snprintf(uptimeStr, sizeof(uptimeStr), "%d days, %d hours, %d minutes", days, hours, minutes);
	return (std::string(uptimeStr));
}

void	Server::broadcast(const std::string &message, Client *sender) {
	for (size_t i = 0; i < clientObjects.size(); i++) {
		Client	*target = clientObjects[i];
		if (target != sender) {
			target->reply(message);
		}
	}
}
