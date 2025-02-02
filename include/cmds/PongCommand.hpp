#ifndef PONG_COMMAND_HPP
# define PONG_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class PongCommand : public Command {
	public:
		PongCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif