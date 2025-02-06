/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:23:23 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:23:23 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartCommand.hpp"
/*
PART command.
Removes a user from one or more channels.
If a reason is provided, it is included in the departure message.
Channels are deleted if they become empty.

Команда PART.
Удаляет пользователя из одного или нескольких каналов.
Если передана причина выхода, она добавляется в сообщение.
Если канал становится пустым, он удаляется.
*/
PartCommand::PartCommand(Server* server) : Command(server) {}

void	PartCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "PART"));
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
			client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
			continue ;
		}

		if (!client->isInChannel(channelName)) {
			client->reply(ERR_NOTONCHANNEL(host, nick, channelName));
			continue ;
		}

		std::string	partMsg = RPL_PART(client->getPrefix(), channelName, reason);
		channel->broadcast(partMsg, NULL);

		channel->removeClient(client);
		client->leaveChannel(channelName);
		if (channel->isEmpty()) {
			_server->deleteChannel(channelName);
		}
	}
}
