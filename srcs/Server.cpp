#include "Server.hpp"
#include "PassCommand.hpp"
#include "NickCommand.hpp"

Server::Server(int port, const std::string &password):	port(port),
														password(password) {
	initSocket();
	initializeCommands();
}

Server::~Server() {
	close(serverSocket);
	for (size_t i = 0; i < clients.size(); ++i) {
		close(clients[i].fd);
	}
	for (size_t i = 0; i < clientObjects.size(); ++i) {
		delete clientObjects[i];
	}
    for (std::map<std::string, Command*>::iterator it = commands.begin(); it != commands.end(); ++it) {
        delete it->second;
    }
}

void Server::initSocket() {
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

void Server::acceptConnection() {
    int clientFd = accept(serverSocket, NULL, NULL);
    if (clientFd < 0) {
        if (errno != EWOULDBLOCK) { // Используем errno и EWOULDBLOCK
            std::cerr << "Accept error" << std::endl;
        }
        return;
    }

    // Add client to poll list
    struct pollfd clientPoll;
    clientPoll.fd = clientFd;
    clientPoll.events = POLLIN;
    clients.push_back(clientPoll);

    clientObjects.push_back(new Client(clientFd));
    std::cout << "New client connected: " << clientFd << std::endl;
}

void Server::handleClient(int clientFd) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead <= 0) {
        if (bytesRead < 0 && errno != EWOULDBLOCK) { // Используем errno и EWOULDBLOCK
            std::cerr << "Recv error for client " << clientFd << std::endl;
        }
        close(clientFd);

        for (std::vector<pollfd>::iterator it = clients.begin(); it != clients.end(); ++it) {
            if (it->fd == clientFd) {
                clients.erase(it);
                break ;
            }
        }

        return;
    }

    std::string message(buffer);
    std::cout << "Received from client " << clientFd << ": " << message << std::endl;

    Client* client = findClientByFd(clientFd);
    if (!client)
		return ;

    client->setPartialMessage(client->getPartialMessage() + message);

    size_t	pos;
    while ((pos = client->getPartialMessage().find('\n')) != std::string::npos) {
        std::string command = client->getPartialMessage().substr(0, pos);
        client->setPartialMessage(client->getPartialMessage().substr(pos + 1));

        if (command.empty())
			continue ;

        handleCommand(client, command);
    }

    if (client->getPartialMessage() == "\n") {
        client->setPartialMessage("");
    }
}

void	Server::initializeCommands() {
	commands["PASS"] = new PassCommand(this);
	commands["NICK"] = new NickCommand(this);
}

void	Server::handleCommand(Client* client, const std::string& command) {
	if (command.empty())
		return ;

	std::istringstream	iss(command);
	std::string			cmd;
	iss >> cmd;

	if (commands.find(cmd) != commands.end()) {
		std::vector<std::string>	args;
		std::string					arg;
		while (iss >> arg) {
			args.push_back(arg);
		}
		commands[cmd]->execute(client, args);
	} else {
		std::cerr	<< "Unknown command: "
					<< cmd
					<< std::endl;
	}
}

Client*	Server::findClientByFd(int fd) {
	for (size_t i = 0; i < clientObjects.size(); ++i) {
		if (clientObjects[i]->getFd() == fd) {
			return clientObjects[i];
		}
	}
	return (nullptr);
}

void Server::run() {
    struct pollfd serverPoll;
    serverPoll.fd = serverSocket;
    serverPoll.events = POLLIN;

    clients.push_back(serverPoll);

    while (true) {
        int pollCount = poll(clients.data(), clients.size(), -1);
        if (pollCount < 0) {
            if (errno == EINTR)
                continue ; // Сигнал, повторяем poll
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

        // Завершаем сервер, если остался только серверный сокет
        if (clients.size() == 1) { // Только серверный сокет
            std::cout	<< "No clients left. Shutting down server."
                        << std::endl;
            break ;
        }
    }
}

std::string	Server::getPassword() const { 
	return (password); 
}
