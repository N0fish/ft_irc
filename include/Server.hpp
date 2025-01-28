#ifndef SERVER_HPP
# define SERVER_HPP

# include "libraries.hpp"

class Client;
class Command;
class NickCommand;
class PassCommand;

class Server {
	private:
		int								serverSocket;
		int								port;
		std::string						password;
		struct sockaddr_in				serverAddr;
		std::vector<struct pollfd>		clients;
		std::vector<Client*>			clientObjects;
		std::map<std::string, Command*>	commands;

		void	initSocket();
		void	acceptConnection();
		void	handleClient(int clientFd);
		Client*	findClientByFd(int fd);
		void	handleCommand(Client* client, const std::string& command);
		void	initializeCommands();
		bool	isNicknameTaken(const std::string& nickname) const;
		void	disconnectClient(Client* client);

		friend class PassCommand;
		friend class NickCommand;

	public:
		Server(int port, const std::string &password);
		~Server();

		void		run();

		std::string	getPassword() const;
};

#endif