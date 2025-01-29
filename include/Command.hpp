#ifndef COMMAND_HPP
#define COMMAND_HPP

# include "libraries.hpp"

class Server;
class Client;

// Этот класс задаёт общий интерфейс для всех команд.
// Каждая команда переопределяет метод execute(),
// который обрабатывает соответствующий ввод от клиента.

class Command {
	protected:
		Server*	_server; // Указатель на сервер(имеет доступ к Server* _server) 
		// для взаимодействия с ним в унаследованных классах.

	public:
		Command(Server* server) : _server(server) {}
		virtual ~Command() {}

		// Чисто виртуальный метод, который переопределяется в дочерних классах
		virtual void	execute(Client* client, const std::vector<std::string>& args) = 0;
};

#endif