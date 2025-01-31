#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class PartCommand : public Command {
	public:
		PartCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif