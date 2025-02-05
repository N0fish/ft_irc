#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "libraries.hpp"

class Server;
class Client;

/*
Base class for all server commands.
Defines a common interface with the execute() method.

Базовый класс для всех команд сервера.
Определяет общий интерфейс с методом execute().
*/

class Command {
	protected:
		Server*	_server;

	public:
		Command(Server* server) : _server(server) {}
		virtual ~Command() {}

		virtual void	execute(Client* client, const std::vector<std::string>& args) = 0;
};

#endif