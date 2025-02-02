#include "InfoCommand.hpp"

InfoCommand::InfoCommand(Server* server) : Command(server) {}

void	InfoCommand::execute(Client* client, const std::vector<std::string>& args) {
	(void)args;
	
	std::stringstream	ss;
	ss << _server->getCreationTime();
	
	client->reply(":server 371 " + client->getNickname() + " :Server started at " + ss.str());
	client->reply(":server 374 " + client->getNickname() + " :End of INFO");
}
