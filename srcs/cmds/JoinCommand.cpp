#include "JoinCommand.hpp"
#include "NamesCommand.hpp"
/*
JOIN command.
Allows a client to join one or multiple channels.
Checks if the channel exists, if the correct password is provided (if required),
whether the client is banned, has an invitation (if the channel is invite-only),
and whether the channel user limit is exceeded.
If the channel does not exist, a new one is created, and the first participant becomes an operator.
After a successful join, if the channel had an invite-only mode (+i),
the client’s invitation is removed from the invite list.
Also sends messages about the join event and channel information (topic, user list).

Команда JOIN.
Позволяет клиенту присоединиться к одному или нескольким каналам.
Проверяет, существует ли канал, введён ли правильный пароль (если требуется),
не заблокирован ли клиент, есть ли у него приглашение (если канал invite-only),
а также не превышен ли лимит пользователей в канале.
Если канал не существует, создаётся новый, и первый участник становится оператором.
После успешного входа, если канал имел режим "только по приглашению" (+i),
приглашение клиента удаляется из списка приглашённых.
Также отправляются сообщения о присоединении и информация о канале (тема, список пользователей).
*/
JoinCommand::JoinCommand(Server* server) : Command(server) {}

void	JoinCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 JOIN :Not enough parameters");
		return ;
	}
	if (args.size() > 2) {
		client->reply(":server 461 JOIN :Too many parameters");
		return ;
	}

	// if (args[0].find(", ") != std::string::npos) {
	// 	client->reply(":server 461 JOIN :Invalid format, do not use spaces after commas");
	// 	return ;
	// }

	std::vector<std::string>	channels = split(args[0], ',');
	std::vector<std::string>	keys;
	if (args.size() > 1) {
		keys = split(args[1], ',');
	}

	for (size_t i = 0; i < channels.size(); i++) {
		std::string	channelName = channels[i];

		if (channelName == "0") {
			while (!client->getChannels().empty()) {
				std::string	currentChannelName = client->getChannels().back();
				Channel*	channel = _server->getChannel(currentChannelName);
				if (channel) {
					channel->removeClient(client);
					channel->broadcast(client->getPrefix() + " PART " + channel->getName(), NULL);
					client->leaveChannel(channel->getName());

					if (channel->isEmpty()) {
						_server->deleteChannel(channel->getName());
					}
				}
			}
			continue ;
		}

		std::string	pass = (i < keys.size()) ? keys[i] : "";

		char	prefix = channelName[0];
		if (channelName.empty() || std::string("#&+!").find(prefix) == std::string::npos || channelName.size() > 50) {
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			continue ;
		}
		std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
		if (channelName.find_first_not_of(allowedChars, 1) != std::string::npos) {
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			continue ;
		}

		if (channelName.find(' ') != std::string::npos || channelName.find(',') != std::string::npos ||
			channelName.find('\x07') != std::string::npos) { 
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			continue ;
		}

		if (prefix == '+' && _server->getChannel(channelName)) {
			client->reply(":server 403 " + channelName + " :Cannot create local channel with duplicate name");
			continue ;
		}

		if (channelName[0] == '!' && _server->isChannelNameTaken(channelName)) {
			client->reply(":server 476 " + channelName + " :Channel name must be unique");
			continue ;
		}

		const int	MAXCHANNELS = 10;
		if (client->getChannels().size() >= MAXCHANNELS) {
			client->reply(":server 405 " + channelName + " :You have joined too many channels");
			continue ;
		}

		Channel*	channel = _server->getChannel(channelName);
		bool		isNewChannel = false;
		if (!channel) {
			channel = _server->createChannel(channelName, pass, client);
			if (!channel) {
				client->reply(":server 403 " + channelName + " :Could not create channel");
				continue ;
			}
			isNewChannel = true;
		}

		if (client->isInChannel(channelName)) {
			continue ;
		}
		if (channel->getPassword() != pass && !channel->getPassword().empty()) {
			client->reply(":server 475 " + channelName + " :Cannot join channel (+k)");
			continue ;
		}
		if (channel->isBanned(client)) {
			client->reply(":server 474 " + channelName + " :Cannot join channel (+b)");
			continue ;
		}
		if (channel->isInviteOnly() && !channel->isInvited(client)) {
			client->reply(":server 473 " + channelName + " :Cannot join channel (+i)");
			continue ;
		}
		if (channel->getLimit() > 0 && channel->getUserCount() >= channel->getLimit()) {
			client->reply(":server 471 " + channelName + " :Channel is full");
			continue ;
		}

		channel->addClient(client);
		client->joinChannel(channelName);
		channel->removeInvite(client);

		if (isNewChannel) {
			channel->addOperator(client);
		}

		std::string	joinMsg = client->getPrefix() + " JOIN " + channelName;
		channel->broadcast(joinMsg, NULL);

		if (!channel->getTopic().empty()) {
			client->reply(":server 332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic());
		}
		std::vector<std::string>	channels(1, channelName);
		(NamesCommand (_server)).execute(client, channels);
	}
}
