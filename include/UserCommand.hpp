#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

// Я реализовала команды USER и NICK через систему классов, 
// используя абстрактный базовый класс Command, от которого наследуются конкретные команды.

class UserCommand : public Command {
	public:
		UserCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif