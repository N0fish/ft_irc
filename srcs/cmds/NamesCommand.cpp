#include "NamesCommand.hpp"
#include "Channel.hpp"

NamesCommand::NamesCommand(Server* server) : Command(server) {}

void	NamesCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client == NULL)
		return ;
	std::vector<std::string> channels;
	
	if (args.empty()) {
		channels = _server->getChannelsName();
	} else {
		channels = split(args[0], ',');
	}

	size_t chs = channels.size();
	for (size_t i = 0; i < chs; i++) {
		std::string resp = "";
		Channel *channel = _server->getChannel(channels[i]);
		resp += ":server 353 " +client->getNickname() + " "+ channel->getName() + " :";

		std::set<Client*> clients = channel->getClients();
		for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
			Client *currClient = *it;
			if (it != clients.begin()) 
				resp += " ";
			resp += (channel->isOperator(currClient) ? "+" : "") + currClient->getNickname();
		}
		client->reply(resp);
		if (!args.empty())
			client->reply(":server 366 " +client->getNickname() + " " + channel->getName() + " :End of NAMES list");
	}
	if (args.empty())
			client->reply(":server 366 " +client->getNickname() + " * :End of NAMES list");
}
