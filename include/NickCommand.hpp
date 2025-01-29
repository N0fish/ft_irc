#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

// Я реализовала команды USER и NICK через систему классов, 
// используя абстрактный базовый класс Command, от которого наследуются конкретные команды.

class NickCommand : public Command {
	public:
		NickCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif