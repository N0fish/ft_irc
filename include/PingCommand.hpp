#ifndef PING_COMMAND_HPP
# define PING_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class PingCommand : public Command {
	public:
		PingCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif