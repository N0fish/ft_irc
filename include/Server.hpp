#ifndef SERVER_HPP
# define SERVER_HPP

# include "libraries.hpp"

class Client;
class Command;
class NickCommand;
class PassCommand;
class JoinCommand;
class PartCommand;
class PrivmsgCommand;
class PingCommand;
class Channel;

class Server {
	private:
		int								serverSocket;
		int								port;
		std::string						password;
		struct sockaddr_in				serverAddr;
		std::vector<struct pollfd>		clients;
		std::vector<Client*>			clientObjects;
		std::map<std::string, Command*>	commands;
		std::map<std::string, Channel*>	channels;

		void	initSocket();
		void	acceptConnection();
		void	handleClient(int clientFd);
		Client*	findClientByFd(int fd);
		void	handleCommand(Client* client, const std::string& command);
		void	initializeCommands();
		bool	isNicknameTaken(const std::string& nickname) const;
		void	removeClientFromChannels(Client* client);
		void	disconnectClient(Client* client);

        void    handleJOIN(Client* client, const std::vector<std::string>& args) ;
        void    handlePART(int clientFd, const std::string& channelName);
        void    handlePRIVMSG(Client* client, const std::vector<std::string>& args);
        Client* findClientByNickname(const std::string& nickname) const;
        void    handlePING(Client* client, const std::vector<std::string>& args);

		friend class PassCommand;
		friend class NickCommand;
		friend class JoinCommand;
		friend class PartCommand;
		friend class PrivmsgCommand;
		friend class PingCommand;

	public:
		Server(int port, const std::string &password);
		~Server();

		void		run();

		std::string	getPassword() const;
};

#endif