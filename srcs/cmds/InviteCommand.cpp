#include "InviteCommand.hpp"

InviteCommand::InviteCommand(Server* server) : Command(server) {}

void	InviteCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) { // Недостаточно аргументов
		client->reply(":server 461 INVITE :Not enough parameters");
		return ;
	}

	std::string targetNickname = args[0];
	std::string channelName = args[1];

	// Проверяем, существует ли канал
	Channel* channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(":server 403 " + channelName + " :No such channel");
		return ;
	}

	// Проверяем, состоит ли клиент в канале
	if (!channel->getClients().count(client)) {
		client->reply(":server 442 " + channelName + " :You're not on that channel");
		return ;
	}

	// Проверяем, является ли клиент оператором, если канал invite-only
	if (channel->isInviteOnly() && !channel->isOperator(client)) {
		client->reply(":server 482 " + channelName + " :You're not channel operator");
		return ;
	}

	// Проверяем, существует ли целевой клиент
	Client* targetClient = _server->findClientByNickname(targetNickname);
	if (!targetClient) {
		client->reply(":server 401 " + targetNickname + " :No such nick");
		return ;
	}

	// Проверяем, находится ли уже пользователь в канале
	if (channel->getClients().count(targetClient)) {
		client->reply(":server 443 " + targetNickname + " " + channelName + " :is already on channel");
		return ;
	}

	// Добавляем пользователя в список приглашённых
	targetClient->reply(":server 341 " + client->getNickname() + " " + targetNickname + " " + channelName);
	targetClient->reply(":" + client->getNickname() + " INVITE " + targetNickname + " " + channelName);

	// Можно добавить список приглашённых пользователей в `Channel` (если он нужен)
	// Добавляем пользователя в список приглашённых
	channel->addInvite(targetClient);
	targetClient->reply(":server 341 " + client->getNickname() + " " + targetNickname + " " + channelName);
	targetClient->reply(":" + client->getNickname() + " INVITE " + targetNickname + " " + channelName);
}
