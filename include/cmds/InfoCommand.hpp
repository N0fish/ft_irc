#ifndef INFO_COMMAND_HPP
# define INFO_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)
# define COMPILE_DATE __DATE__
# define COMPILE_TIME __TIME__

class InfoCommand : public Command {
	public:
		InfoCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif