#include "PartCommand.hpp"

PartCommand::PartCommand(Server* server) : Command(server) {}

void	PartCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 PART :Not enough parameters");
		return ;
	}

	std::vector<std::string>	channelNames = split(args[0], ',');
	std::string					reason;
	if (args.size() > 1) {
		reason = args[1][0] == ':' ? args[1].substr(1) : args[1];
		for (size_t j = 2; j < args.size(); ++j) {
			reason += " " + args[j];
		}
	}

	for (size_t i = 0; i < channelNames.size(); ++i) {
		std::string	channelName = channelNames[i];
		Channel*	channel = _server->getChannel(channelName);
		if (!channel) {
			client->reply(":server 403 " + channelName + " :No such channel");
			continue ;
		}

		if (!client->isInChannel(channelName)) {
			client->reply(":server 442 " + channelName + " :You're not on that channel");
			continue ;
		}

		std::string	partMsg = client->getPrefix() + " PART " + channelName;
		if (!reason.empty()) {
			partMsg += " :" + reason;
		}

		channel->broadcast(partMsg, NULL);
		channel->removeClient(client);
		client->leaveChannel(channelName);

		if (channel->isEmpty()) {
			_server->deleteChannel(channelName);
		}
	}
}
