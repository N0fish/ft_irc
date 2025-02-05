#ifndef NAMES_COMMAND_HPP
# define NAMES_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class NamesCommand : public Command {
	public:
		NamesCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif