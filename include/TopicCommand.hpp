#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "Command.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class TopicCommand : public Command {
	public:
		TopicCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif