#include "InviteCommand.hpp"
/*
INVITE command.  
Allows inviting a user to a channel.
Checks if the channel exists and whether the sender has permission to invite.
If all conditions are met, the user receives an invitation and can join.

Команда INVITE.
Позволяет пригласить пользователя в канал.
Проверяет, существует ли канал и имеет ли отправитель право приглашать.
Если всё в порядке, пользователь получает приглашение и может присоединиться.
*/
InviteCommand::InviteCommand(Server* server) : Command(server) {}

void InviteCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) {
		client->reply(":server 461 INVITE :Not enough parameters");
		return ;
	}

	std::string	targetNickname = args[0];
	std::string	channelName = args[1];

	Channel*	channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(":server 403 " + channelName + " :No such channel");
		return ;
	}
	if (!channel->getClients().count(client)) {
		client->reply(":server 442 " + channelName + " :You're not on that channel");
		return ;
	}
	if (channel->isInviteOnly() && !channel->isOperator(client)) {
		client->reply(":server 482 " + channelName + " :You're not channel operator");
		return ;
	}

	Client*	targetClient = _server->findClientByNickname(targetNickname);
	if (!targetClient) {
		client->reply(":server 401 " + targetNickname + " :No such nick");
		return ;
	}
	if (channel->isClientInChannel(targetClient)) {
		client->reply(":server 443 " + targetNickname + " " + channelName + " :is already on channel");
		return ;
	}
	if (channel->isInvited(targetClient)) {
		client->reply(":server 443 " + targetNickname + " " + channelName + " :User already invited");
		return ;
	}

	channel->addInvite(targetClient);
	client->reply(":server 341 " + client->getNickname() + " " + targetNickname + " " + channelName);
	targetClient->reply(client->getPrefix() + " INVITE " + targetNickname + " :" + channelName);
}
