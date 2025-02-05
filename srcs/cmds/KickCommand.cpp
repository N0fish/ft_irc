#include "KickCommand.hpp"
/*
KICK command.
Allows a channel operator to forcibly remove users from a channel.
The server checks:
- If the channel exists and the client is a member.
- If the client has operator privileges.
- If the target users are in the channel.
If valid, the target users are removed, a KICK message is sent,
and if the channel becomes empty, it is deleted.

Команда KICK.
Позволяет оператору насильно удалить пользователей из канала.
Сервер проверяет:
- Существует ли канал и является ли клиент его участником.
- Есть ли у клиента права оператора.
- Находятся ли целевые пользователи в канале.
Если всё верно, пользователи удаляются, отправляется сообщение KICK,
а пустой канал удаляется.
*/
KickCommand::KickCommand(Server* server) : Command(server) {}

void	KickCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "KICK"));
		return ;
	}

	std::string					channelName = args[0];
	std::vector<std::string>	targetNicks = split(args[1], ','); 
	std::string					reason = (args.size() > 2) ? joinArgs(args, 2) : nick;
	if (reason.empty()) {
		reason = nick;
	}

	if (channelName.empty() || std::string("#&+!").find(channelName[0]) == std::string::npos) {
		client->reply(ERR_BADCHANMASK(host, nick, channelName));
		return ;
	}

	Channel* channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
		return ;
	}
	if (!client->isInChannel(channelName)) {
		client->reply(ERR_NOTONCHANNEL(host, nick, channelName));
		return ;
	}
	if (!channel->isOperator(client)) {
		client->reply(ERR_CHANOPRIVSNEEDED(host, nick, channelName));
		return ;
	}

	for (size_t i = 0; i < targetNicks.size(); i++) {
		std::string	targetNick = targetNicks[i];
		Client*		targetClient = _server->findClientByNickname(targetNick);
		if (!targetClient || !channel->getClients().count(targetClient)) {
			client->reply(ERR_USERNOTINCHANNEL(host, nick, targetNick, channelName));
			continue ;
		}
		if (channel->isOperator(targetClient)) {
			channel->removeOperator(targetClient);
		}

		channel->broadcast(RPL_KICK(client->getPrefix(), channelName, targetNick, reason), NULL);
		channel->removeClient(targetClient);
		targetClient->leaveChannel(channel->getName());
	}

	if (channel->isEmpty()) {
		_server->deleteChannel(channelName);
	}
}
