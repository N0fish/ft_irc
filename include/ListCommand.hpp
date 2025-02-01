#ifndef LIST_COMMAND_HPP
# define LIST_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class ListCommand : public Command {
	public:
		ListCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif