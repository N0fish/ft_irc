#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class UserCommand : public Command {
	public:
		UserCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif