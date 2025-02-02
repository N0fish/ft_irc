#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class KickCommand : public Command {
	public:
		KickCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif