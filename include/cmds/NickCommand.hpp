#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class NickCommand : public Command {
	public:
		NickCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif