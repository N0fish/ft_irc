#ifndef USERHOST_COMMAND_HPP
# define USERHOST_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class UserhostCommand : public Command {
	public:
		UserhostCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif