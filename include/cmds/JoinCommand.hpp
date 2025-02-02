#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class JoinCommand : public Command {
	public:
		JoinCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif