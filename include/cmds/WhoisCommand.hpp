#ifndef WHOIS_COMMAND_HPP
# define WHOIS_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class WhoisCommand : public Command {
	public:
		WhoisCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif