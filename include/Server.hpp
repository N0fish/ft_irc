#ifndef SERVER_HPP
# define SERVER_HPP

# include "libraries.hpp"

/*
Class representing an IRC server.
Manages network connections, client authentication,
command processing, and channel management.
Responsible for handling connections, processing messages, and managing clients.

Класс, представляющий IRC-сервер.
Управляет сетевыми соединениями, аутентификацией клиентов,
обработкой команд и управлением каналами.
Отвечает за приём подключений, обработку сообщений и управление клиентами.
*/

class Client;
class Channel;
class Command;

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
		time_t							creationTime;
		std::set<std::string>			usedNicknames;

		void	initSocket();
		void	acceptConnection();
		void	handleClient(int clientFd);
		void	initializeCommands();
		Client*	findClientByFd(int fd);
		void	handleCommand(Client* client, const std::string& command);
		void	addNickname(const std::string& nickname);
		void	removeNickname(const std::string& nickname);
		bool	isNicknameTaken(const std::string& nickname) const;
		void	removeClientFromChannels(Client* client);
		void	disconnectClient(Client* client);
		void	deleteChannel(const std::string& channelName);
		void	serverLayout();

		friend class PassCommand;
		friend class NickCommand;
		friend class JoinCommand;

		friend class PartCommand;
		friend class KickCommand;
		friend class QuitCommand;

	public:
		Server(int port, const std::string &password);
		~Server();

		void									run();
		void									cleanup();

		std::string								getPassword() const;
		std::string								getHostname() const;

		Client*									findClientByNickname(const std::string& nickname) const;
		Channel*								getChannel(const std::string& name);
		const std::map<std::string, Channel*>&	getChannels() const;
		const std::vector<std::string>			getChannelsName();
		Channel*								createChannel(const std::string& name, const std::string& pass, Client* creator);

		time_t									getCreationTime() const;
		std::string 							getVersion() const;
		std::string 							getOSInfo() const;
		std::string 							getUptime() const;

		void									broadcast(const std::string& message, Client* sender);
};

#endif