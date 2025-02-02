#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"
#include "libcmds.hpp"

Server::Server(int port, const std::string &password):	port(port),
														password(password) {
	creationTime = time(NULL);
	initSocket();
	initializeCommands();
	serverLayout();
}

Server::~Server() {
	cleanup();
}

void	Server::cleanup() {
	close(serverSocket);
	
	for (size_t i = 0; i < clients.size(); ++i) {
		close(clients[i].fd);
	}
	clients.clear();

	std::cout << "clients " << clients[0].fd << std::endl;

	for (size_t i = 0; i < clientObjects.size(); ++i) {
		delete clientObjects[i];
	}
	clientObjects.clear();

	for (std::map<std::string, Command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
		delete it->second;
	}
	commands.clear();

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ) {
		delete it->second;
		std::map<std::string, Channel*>::iterator next = it;
		++next;
		channels.erase(it);
		it = next;
	}

	// std::cout << "Server cleanup complete." << std::endl;
}

void	Server::initSocket() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		throw std::runtime_error("Failed to create socket");
	}

	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw std::runtime_error("Failed to set socket options");
	}

	int flags = fcntl(serverSocket, F_GETFL, 0);
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

	std::cout << "Server started on port " << port << std::endl;
}

// сервер создаёт клиента (Client) при подключении

// - сервр принимает новое соединение
// - добавляет клиента в poll() для обработки событий
// - создает новый объект Client и сохраняет его
void	Server::acceptConnection() {
	int clientFd = accept(serverSocket, NULL, NULL);
	if (clientFd < 0) {
		if (errno != EWOULDBLOCK) {
			std::cerr << "Accept error" << std::endl;
		}
		return ;
	}

	// Add client to poll list
	struct pollfd clientPoll;
	clientPoll.fd = clientFd;
	clientPoll.events = POLLIN;
	clients.push_back(clientPoll);

	clientObjects.push_back(new Client(clientFd));
	std::cout << "New client connected: " << clientFd << std::endl;
}

void	Server::handleClient(int clientFd) {
	char	buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	ssize_t	bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead <= 0) {
		if (bytesRead < 0 && errno != EWOULDBLOCK) {
			std::cerr << "Recv error for client " << clientFd << std::endl;
		}
		Client*	client = findClientByFd(clientFd);
		if (client)
			disconnectClient(client);
		return ;
	}

	Client* client = findClientByFd(clientFd);
	if (!client) {
		// std::cerr << "Error: Client not found for fd " << clientFd << std::endl;
		return ;
	}

	std::string	message(buffer);
	client->setPartialMessage(client->getPartialMessage() + message);

	size_t	pos;
	while ((pos = client->getPartialMessage().find('\n')) != std::string::npos)
	{
		std::string	command = client->getPartialMessage().substr(0, pos);
		client->setPartialMessage(client->getPartialMessage().substr(pos + 1));

		if (command.empty())
			continue ;

		handleCommand(client, command);

		if (findClientByFd(clientFd) == NULL)
			return ;
	}
}


// Команды добавляются в std::map<std::string, Command*> 
// commands в методе initializeCommands().
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
	// commands["VERSION"] = new VersionCommand(this);
	// commands["ADMIN"] = new AdminCommand(this);
}

void	Server::removeClientFromChannels(Client* client) {
	if (client == NULL)
		return ;
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ) {
		it->second->removeClient(client);
		if (!it->second->isEmpty()) {
			delete it->second;
			std::map<std::string, Channel*>::iterator next = it;
			++next;
			delete it->second;
			channels.erase(it);
			it = next;
		} else
			++it;
	}
}

void	Server::disconnectClient(Client* client) {
	if (!client)
		return;

	int	fd = client->getFd();
	removeClientFromChannels(client);

	for (std::vector<pollfd>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (it->fd == fd) {
			clients.erase(it);
			break ;
		}
	}

	for (std::vector<Client*>::iterator it = clientObjects.begin(); it != clientObjects.end(); ++it) {
		if (*it == client) {
			delete client;
			*it = NULL;
			clientObjects.erase(it);
			break ;
		}
	}

	close(fd);
	std::cout	<< "Client(" << fd << ") disconnected"
				<< std::endl;
}


bool	Server::isNicknameTaken(const std::string& nickname) const {
	for (size_t i = 0; i < clientObjects.size(); ++i) {
		if (clientObjects[i]->getNickname() == nickname) {
			return (true);
		}
	}
	return (false);
}

// сервер обрабатывает команды, которые вводит клиент
void	Server::handleCommand(Client* client, const std::string& command) {
	if (command.empty())
		return ;

	std::istringstream	iss(command);
	std::string			cmd;
	iss >> cmd;

	if (!client->isRegistered() 
		&& cmd != "PASS" && cmd != "NICK" && cmd != "USER") {
		client->reply(":server 451 " + cmd + " :You have not registered");
		return ;
	}

	if (commands.find(cmd) != commands.end()) {
		std::vector<std::string>	args;
		std::string					arg;
		while (iss >> arg) {
			args.push_back(arg);
		}
		commands[cmd]->execute(client, args);
	} else
		client->reply(":server 421 " + cmd + " :Unknown command");
}

void	Server::serverLayout() {
	createChannel("#general", "", NULL);
}

void	Server::run() {
	struct pollfd serverPoll;
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

const std::map<std::string, Channel*>&	Server::getChannels() const {
	return (channels);
}

std::string	Server::getPassword() const { 
	return (password); 
}

std::string	Server::getHostname() const {
	char hostname[256];
	memset(hostname, 0, sizeof(hostname));

	if (gethostname(hostname, sizeof(hostname) - 1) != 0) {
		std::cerr << "Error: gethostname() failed, using 'localhost'" << std::endl;
		return ("localhost");
	}
	return (std::string(hostname));
}

Client*	Server::findClientByFd(int fd) {
	for (size_t i = 0; i < clientObjects.size(); ++i) {
		if (clientObjects[i]->getFd() == fd) {
			return (clientObjects[i]);
		}
	}
	return (NULL);
}

Channel*	Server::getChannel(const std::string& name) {
	if (channels.find(name) != channels.end()) {
		return (channels[name]);
	}
	return (NULL);
}

Channel*	Server::createChannel(const std::string& name, const std::string& pass, Client* creator) {
	if (channels.find(name) == channels.end()) {
		Channel* newChannel = new Channel(name, pass);
		channels[name] = newChannel;
		if (creator != NULL)
			newChannel->addClient(creator);
		return (newChannel);
	}
	return (NULL);
}

void	Server::deleteChannel(const std::string& channelName) {
	if (channels.find(channelName) == channels.end()) {
		std::cerr << "Warning: Attempt to delete a non-existing channel: " << channelName << std::endl;
		return ;
	} // надо проверить на вальграйне !!!!!!!!!

	std::map<std::string, Channel*>::iterator it = channels.find(channelName);
	if (it != channels.end()) {
		delete it->second;
		channels.erase(it);
	}
}

Client*	Server::findClientByNickname(const std::string& nickname) const {
	for (std::vector<Client*>::const_iterator it = clientObjects.begin(); it != clientObjects.end(); ++it) {
		Client* client = *it;
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
