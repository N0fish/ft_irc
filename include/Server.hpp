#ifndef SERVER_HPP
# define SERVER_HPP

# include "libraries.hpp"

class Client;
class Channel;
class Command;

class PassCommand;
class NickCommand;
class UserCommand;
class JoinCommand;
class PartCommand;
class PrivmsgCommand;
class PingCommand;
class KickCommand;
class ModeCommand;
class InviteCommand;
class TopicCommand;
class UserhostCommand;
class ListCommand;
// class QuitCommand;
// class WhoisCommand;

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
		void	initializeCommands();
		Client*	findClientByFd(int fd);
		void	handleCommand(Client* client, const std::string& command);
		bool	isNicknameTaken(const std::string& nickname) const;
		void	removeClientFromChannels(Client* client);
		void	disconnectClient(Client* client);
		void	deleteChannel(const std::string& channelName);
		void	serverLayout();

		friend class PassCommand;
		friend class UserCommand;
		friend class NickCommand;
		friend class JoinCommand;

		friend class PartCommand;
		friend class PrivmsgCommand;
		friend class PingCommand;

		friend class KickCommand;
		friend class InviteCommand;
		friend class TopicCommand;
		friend class ModeCommand;

		friend class UserhostCommand;
		// friend class ListCommand;
		friend class QuitCommand;
		// friend class WhoisCommand;


	public:
		Server(int port, const std::string &password);
		~Server();

		void		run();

		std::string	getPassword() const;

		Client*							findClientByNickname(const std::string& nickname) const;
		Channel*						getChannel(const std::string& name);
		std::map<std::string, Channel*>	getChannels();
		Channel*						createChannel(const std::string& name, const std::string& pass, Client* creator);
};

#endif