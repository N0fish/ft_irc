#include "WhoisCommand.hpp"

WhoisCommand::WhoisCommand(Server* server) : Command(server) {}

void WhoisCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 431 WHOIS :No nickname given");
		return ;
	}
	
	Client* target = _server->findClientByNickname(args[0]);
	if (!target) {
		client->reply(":server 401 " + args[0] + " :No such nick");
		return ;
	}
	
	client->reply(":server 311 " + client->getNickname() + " " + target->getNickname() 
					+ " " + target->getUsername() + " " + target->getIpAddr() + " * :Real Name");
	client->reply(":server 318 " + client->getNickname() + " " + target->getNickname() + " :End of WHOIS list");
}
