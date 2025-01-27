#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

#include "Command.hpp"
#include "Client.hpp"

class PassCommand : public Command {
	public:
		PassCommand(Server* server);
		virtual void execute(Client* client, const std::vector<std::string>& args);
};

#endif