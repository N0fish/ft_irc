#include "JoinCommand.hpp"
#include "NamesCommand.hpp"
/*
JOIN command.
Allows a client to join one or multiple channels.
If the channel does not exist, a new one is created, and the first participant becomes an operator.
The command also supports a special argument `"0"`,
which makes the user leave all currently joined channels.
Access restrictions:
- If the channel requires a key (+k) and an incorrect key is provided, the user is rejected (ERR_BADCHANNELKEY).
- If the channel is invite-only (+i) and the user is not invited, they are rejected (ERR_INVITEONLYCHAN).
- If the user is banned (+b), they are rejected (ERR_BANNEDFROMCHAN).
- If the channel has reached its user limit (+l), the user is rejected (ERR_CHANNELISFULL).

Команда JOIN.
Позволяет клиенту присоединиться к одному или нескольким каналам.
Если канал не существует, создаётся новый, и первый участник становится оператором.
Команда также поддерживает специальный аргумент `"0"`,
который заставляет пользователя покинуть все текущие каналы.
Ограничения доступа:
- Если канал требует ключ (+k) и передан неверный ключ, пользователь отклоняется (ERR_BADCHANNELKEY).
- Если канал работает в режиме "только по приглашению" (+i) и пользователь не приглашён, он отклоняется (ERR_INVITEONLYCHAN).
- Если пользователь заблокирован (+b), он отклоняется (ERR_BANNEDFROMCHAN).
- Если канал достиг предела пользователей (+l), вход отклоняется (ERR_CHANNELISFULL).
*/
JoinCommand::JoinCommand(Server* server) : Command(server) {}

void	JoinCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();

	if (args.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "JOIN"));
		return ;
	}

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
			client->reply(ERR_BADCHANMASK(host, nick, channelName));
			continue ;
		}
		std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
		if (channelName.find_first_not_of(allowedChars, 1) != std::string::npos) {
			client->reply(ERR_BADCHANMASK(host, nick, channelName));
			continue ;
		}

		if (channelName.find(' ') != std::string::npos || channelName.find(',') != std::string::npos ||
			channelName.find('\x07') != std::string::npos) { 
			client->reply(ERR_BADCHANMASK(host, nick, channelName));
			continue ;
		}

		if (prefix == '+' && _server->getChannel(channelName)) {
			client->reply(ERR_DUPLICATELOCALCHANNEL(host, nick, channelName));
			continue ;
		}

		if (channelName[0] == '!' && _server->isChannelNameTaken(channelName)) {
			client->reply(ERR_CHANNELNAMENOTUNIQUE(host, nick, channelName));
			continue ;
		}

		const int	MAXCHANNELS = 10;
		if (client->getChannels().size() >= MAXCHANNELS) {
			client->reply(ERR_TOOMANYCHANNELS(host, nick, channelName));
			continue ;
		}

		Channel*	channel = _server->getChannel(channelName);
		bool		isNewChannel = false;
		if (!channel) {
			if (prefix == '+') {
				client->reply(ERR_CANNOTCREATECHANNEL(host, nick, channelName));
				continue ;
			}
			channel = _server->createChannel(channelName, pass, client);
			if (!channel) {
				client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
				continue ;
			}
			isNewChannel = true;
		}

		if (client->isInChannel(channelName)) {
			continue ;
		}
		if (channel->getPassword() != pass && !channel->getPassword().empty()) {
			client->reply(ERR_BADCHANNELKEY(host, nick, channelName));
			continue ;
		}
		if (channel->isBanned(client)) {
			client->reply(ERR_BANNEDFROMCHAN(host, nick, channelName));
			continue ;
		}
		if (channel->isInviteOnly() && !channel->isInvited(client)) {
			client->reply(ERR_INVITEONLYCHAN(host, nick, channelName));
			continue ;
		}
		if (channel->getLimit() > 0 && channel->getUserCount() >= channel->getLimit()) {
			client->reply(ERR_CHANNELISFULL(host, nick, channelName));
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
			client->reply(RPL_TOPIC(host, nick, channelName, channel->getTopic()));
		}
		std::vector<std::string>	channels(1, channelName);
		(NamesCommand (_server)).execute(client, channels);
	}
}
