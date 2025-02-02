#include "UserhostCommand.hpp"

UserhostCommand::UserhostCommand(Server* server) : Command(server) {}

void	UserhostCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 " + client->getNickname() + " USERHOST :Not enough parameters");
		return ;
	}

	std::string info = "";
	for(size_t i = 0; i < args.size(); i++) {
		Client* c = _server->findClientByNickname(args[i]);
		if (c == NULL) {
			continue ;
		}
		if (i > 0)
			info += " ";
		info += (c->getUsername() + "=" + c->getUserSymbol() + c->getUsername() + "@" + c->getIpAddr());
	}
	client->reply(":server 302 " + client->getNickname() + " :" + info);
}