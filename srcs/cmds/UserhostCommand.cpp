#include "UserhostCommand.hpp"

UserhostCommand::UserhostCommand(Server* server) : Command(server) {}

void	UserhostCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "USERHOST"));
		return ;
	}

	std::string	info = "";
	size_t		count = args.size() > 5 ? 5 : args.size();

	for (size_t i = 0; i < count; i++) {
		Client*	c = _server->findClientByNickname(args[i]);
		if (c == NULL) {
			continue ;
		}
		if (!info.empty()) {
			info += " ";
		}
		std::string	username = c->getUsername().empty() ? "unknown" : c->getUsername();
		std::string	host = c->getIpAddr().empty() ? "unknown" : c->getIpAddr(); 
		info += c->getNickname() + "=" + username + "@" + host;
	}
	client->reply(":server 302 " + client->getNickname() + " :" + info);
}
