#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class QuitCommand : public Command {
	public:
		QuitCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif