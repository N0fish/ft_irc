#include "WhoisCommand.hpp"

WhoisCommand::WhoisCommand(Server* server) : Command(server) {}

void WhoisCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":" + _server->getHostname() + " 431 :No nickname given");
		return ;
	}
	
	std::string targetNick = args[0];
	Client* target = _server->findClientByNickname(args[0]);
	if (!target) {
		client->reply(":" + _server->getHostname() + " 401 " + targetNick + " :No such nick");
		return ;
	}
	
	std::string whoisInfo = ":" + _server->getHostname() + " 311 " + client->getNickname() +
							" " + target->getNickname() + " " + target->getUsername() + " " +
							target->getIpAddr() + " * :" + target->getNickname();
	client->reply(whoisInfo);
}
