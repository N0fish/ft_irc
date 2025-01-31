#ifndef MODE_COMMAND_HPP
# define MODE_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class ModeCommand : public Command {
	public:
		ModeCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif