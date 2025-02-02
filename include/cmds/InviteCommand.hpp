#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class InviteCommand : public Command {
	public:
		InviteCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif