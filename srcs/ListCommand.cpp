#include "ListCommand.hpp"

ListCommand::ListCommand(Server* server) : Command(server) {}

void	ListCommand::execute(Client* client, const std::vector<std::string>& args) {
	client->reply(":server 321 " + args[0] + " Channel :Users  Topic");
	std::map<std::string, Channel*> channels = _server->getChannels();
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		Channel *channel = it->second;
		std::stringstream ss;
		ss << channel->getUserCount();

		client->reply(":server 322 " + args[0] + " " + channel->getName() + " " + ss.str() + " :Bienvenue sur #general");
	}
	client->reply(":server 323 " + args[0] + " :End of LIST");
}
