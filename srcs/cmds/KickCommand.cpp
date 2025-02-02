#include "KickCommand.hpp"

KickCommand::KickCommand(Server* server) : Command(server) {}

void	KickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) {
		client->reply(":server 461 KICK :Not enough parameters");
		return ;
	}

	std::string channelName = args[0];
	std::string targetNick = args[1];
	std::string reason = (args.size() > 2) ? args[2] : "Kicked";

	if (channelName[0] != '#') {
		client->reply(":server 476 " + channelName + " :Invalid channel name");
		return ;
	}

	Channel* channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(":server 403 " + channelName + " :No such channel");
		return ;
	}

	if (!client->isInChannel(channelName)) {
		client->reply(":server 442 " + channelName + " :You're not on that channel");
		return ;
	}

	if (!channel->isOperator(client)) {
		client->reply(":server 482 " + channelName + " :You're not channel operator");
		return ;
	}

	Client* targetClient = _server->findClientByNickname(targetNick);
	if (!targetClient || !channel->getClients().count(targetClient)) {
		client->reply(":server 441 " + targetNick + " " + channelName + " :They aren't on that channel");
		return ;
	}

	// Проверяем, был ли целевой клиент оператором и удаляем его из операторов
	if (channel->isOperator(targetClient)) {
		channel->removeOperator(targetClient);
	}

	// Отправляем сообщение о кике
	std::string kickMsg = ":" + client->getPrefix() + " KICK " + channelName + " " + targetNick + " :" + reason;
	channel->broadcast(kickMsg, NULL);

	// Удаляем пользователя из канала
	channel->removeClient(targetClient);
	if (channel->isEmpty()) {
		_server->deleteChannel(channelName);
	}
}
