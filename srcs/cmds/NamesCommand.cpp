#include "NamesCommand.hpp"
/*
NAMES command.
Lists all visible nicknames in the specified channels or all channels if none are given.
Returns `353` for each channel and `366` at the end of each list.

Команда NAMES.
Выводит список всех видимых никнеймов в указанных каналах или во всех каналах, если они не заданы.
Отправляет `353` для каждого канала и `366` в конце списка.
*/
NamesCommand::NamesCommand(Server* server) : Command(server) {}

void	NamesCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client == NULL)
		return ;

	std::string					host = _server->getHostname();
	std::string					nick = client->getNickname();
	std::vector<std::string>	channels;
	if (args.empty()) {
		channels = _server->getChannelsName();
	} else {
		channels = split(args[0], ',');
	}

	size_t chs = channels.size();
	for (size_t i = 0; i < chs; i++) {
		std::string	channelName = channels[i];
		Channel		*channel = _server->getChannel(channels[i]);
		if (!channel) {
			continue ;
		}

		std::string			nickList = "";
		std::set<Client*>	clients = channel->getClients();
		for (std::set<Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
			Client	*currClient = *it;
			if (it != clients.begin())
				nickList += " ";
			nickList += (channel->isOperator(currClient) ? "+" : "") + currClient->getNickname();
		}
		client->reply(RPL_NAMREPLY(host, nick, "=", channelName, nickList));
		if (!args.empty())
			client->reply(RPL_ENDOFNAMES(host, nick, channelName));
	}
	if (args.empty())
			client->reply(RPL_ENDOFNAMES(host, nick, "*"));
}
