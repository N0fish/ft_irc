/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:23:01 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:23:04 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCommand.hpp"
/*
INVITE command.
Allows inviting a user to a channel.
Checks if the inviter is a member of the channel and has permission to invite.
If all conditions are met, the target user receives an invitation.

Команда INVITE.
Позволяет пригласить пользователя в канал.
Проверяет, является ли отправитель участником канала, имеет ли право приглашать.
Если всё в порядке, приглашение отправляется.
*/
InviteCommand::InviteCommand(Server* server) : Command(server) {}

void InviteCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "INVITE"));
		return ;
	}

	std::string	targetNickname = args[0];
	std::string	channelName = args[1];
	if (targetNickname == client->getNickname()) {
		client->reply(ERR_CHANOPRIVSNEEDED(host, nick, channelName));
		return ;
	}

	Channel*	channel = _server->getChannel(channelName);
	Client*		targetClient = _server->findClientByNickname(targetNickname);
	if (channel) {
		if (channelName[0] == '+') {
			client->reply(ERR_NOSUCHCHANNELL(host, nick, channelName));
			return ;
		}
		if (!channel->getClients().count(client)) {
			client->reply(ERR_NOTONCHANNEL(host, nick, channelName));
			return ;
		}
		if (channel->isInviteOnly() && !channel->isOperator(client)) {
			client->reply(ERR_CHANOPRIVSNEEDED(host, nick, channelName));
			return ;
		}
	}
	if (!targetClient) {
		client->reply(ERR_NOSUCHNICK(host, nick, targetNickname));
		return ;
	}
	if (channel && channel->isClientInChannel(targetClient)) {
		client->reply(ERR_USERONCHANNEL(host, nick, targetNickname, channelName));
		return ;
	}
	if (channel && channel->isInvited(targetClient)) {
		client->reply(ERR_USERONCHANNEL(host, nick, targetNickname, channelName));
		return ;
	}
	if (channel) {
		channel->addInvite(targetClient);
	}
	client->reply(RPL_INVITING(host, nick, targetNickname, channelName));
	targetClient->reply(RPL_INVITE(client->getPrefix(), targetNickname, channelName));
}
