#include "InviteCommand.hpp"

InviteCommand::InviteCommand(Server* server) : Command(server) {}

void InviteCommand::execute(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 2) { // Проверяем, переданы ли аргументы
        client->reply(":server 461 INVITE :Not enough parameters");
        return;
    }

    std::string targetNickname = args[0];
    std::string channelName = args[1];

    // Проверяем существование канала
    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        client->reply(":server 403 " + channelName + " :No such channel");
        return;
    }

    // Проверяем, состоит ли отправитель в канале
    if (!channel->getClients().count(client)) {
        client->reply(":server 442 " + channelName + " :You're not on that channel");
        return;
    }

    // Проверяем, может ли отправитель приглашать
    if (channel->isInviteOnly() && !channel->isOperator(client)) {
        client->reply(":server 482 " + channelName + " :You're not channel operator");
        return;
    }

    // Проверяем, существует ли целевой пользователь
    Client* targetClient = _server->findClientByNickname(targetNickname);
    if (!targetClient) {
        client->reply(":server 401 " + targetNickname + " :No such nick");
        return;
    }

    // Проверяем, не состоит ли уже пользователь в канале
	if (channel->isClientInChannel(targetClient)) {
    	client->reply(":server 443 " + targetNickname + " " + channelName + " :is already on channel");
    	return;
	}

    // Добавляем пользователя в список приглашённых канала
    channel->addInvite(targetClient);

    // Отправляем подтверждение отправителю
    client->reply(":server 341 " + client->getNickname() + " " + targetNickname + " " + channelName);

    // 8️Отправляем приглашение пользователю
    targetClient->reply(":" + client->getNickname() + " INVITE " + targetNickname + " " + channelName);
}
