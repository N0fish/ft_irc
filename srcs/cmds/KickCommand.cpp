#include "KickCommand.hpp"
/*
KICK command.
Allows a channel operator to remove one or multiple users from a channel.
Checks if the channel exists, if the client is an operator,
and if the target users are actually in the channel.
If a target user is an operator, they are first removed from the operator list.
A kick message is broadcasted to the channel.
If the channel becomes empty after the kick, it is deleted.

Команда KICK.
Позволяет оператору канала удалить одного или нескольких пользователей из канала.
Проверяет, существует ли канал, является ли клиент оператором,
и находятся ли целевые пользователи в канале.
Если целевой пользователь был оператором, он сначала удаляется из списка операторов.
Сообщение о кике рассылается всем участникам канала.
Если после кика канал остаётся пустым, он удаляется.
*/
KickCommand::KickCommand(Server* server) : Command(server) {}

void	KickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) {
		client->reply(":server 461 KICK :Not enough parameters");
		return ;
	}

	std::string					channelName = args[0];
	std::vector<std::string>	targetNicks = split(args[1], ','); 
	std::string	reason = (args.size() > 2) ? joinArgs(args, 2) : "Kicked";
	if (reason.empty()) {
		reason = "Kicked";
	}

	// if (channelName.empty() || std::string("#&+!").find(channelName[0]) == std::string::npos) {
	// 	client->reply(":server 476 " + channelName + " :Invalid channel name");
	// 	return ;
	// }

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

	for (size_t i = 0; i < targetNicks.size(); i++) {
		std::string	targetNick = targetNicks[i];
		Client*		targetClient = _server->findClientByNickname(targetNick);
		if (!targetClient || !channel->getClients().count(targetClient)) {
			client->reply(":server 441 " + targetNick + " " + channelName + " :They aren't on that channel");
			continue ;
		}
		if (channel->isOperator(targetClient)) {
			channel->removeOperator(targetClient);
		}

		std::string kickMsg = client->getPrefix() + " KICK " + channelName + " " + targetNick + " :" + reason;
		channel->broadcast(kickMsg, NULL);
		channel->removeClient(targetClient);
		targetClient->leaveChannel(channel->getName());
	}

	if (channel->isEmpty()) {
		_server->deleteChannel(channelName);
	}
}
