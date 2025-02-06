/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:34:06 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:34:07 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCommand.hpp"
/*
MODE command.
Handles viewing and modifying channel modes according.
Supports operator management (+o), invite-only (+i), topic restriction (+t),
password (+k), user limit (+l).

Команда MODE.
Обрабатывает просмотр и изменение режимов канала.
Поддерживает оператора (+o), доступ по приглашению (+i), ограничение темы (+t),
пароль (+k), лимит пользователей (+l).
*/
ModeCommand::ModeCommand(Server* server) : Command(server) {}

void ModeCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "MODE"));
		return ;
	}

	std::string	channelName = args[0];
	if (channelName.empty() || std::string("#&+!").find(channelName[0]) == std::string::npos) {
		client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
		return ;
	}

	Channel*	channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
		return ;
	}
	if (args.size() == 1) {
		std::string modes = "+";
		if (channel->isInviteOnly()) modes += "i";
		if (channel->isTopicRestricted()) modes += "t";
		if (!channel->getPassword().empty()) modes += "k";
		if (channel->getLimit() > 0) modes += "l";
		client->reply(RPL_CHANNELMODEIS(host, nick, channelName, modes));
		return ;
	}
	if (!channel->isOperator(client)) {
		client->reply(ERR_CHANOPRIVSNEEDED(host, nick, channelName));
		return ;
	}

	std::string modeString = args[1];
	for (size_t i = 0; i < modeString.size(); ++i) {
		if ((modeString[i] == '+' || modeString[i] == '-')
			&& (i + 1 >= modeString.size() || isspace(modeString[i + 1]))) {
			client->reply(ERR_UNKNOWNMODE(host, nick, std::string(1, modeString[i])));
			return ;
		}
	}

	bool		adding = true;
	size_t		argIndex = 2;
	int			parameterizedCount = 0;
	std::string	appliedModes;
	std::string	appliedParams;

	for (size_t i = 0; i < modeString.size(); ++i) {
		char	mode = modeString[i];

		if (mode == '+') {
			adding = true;
			appliedModes += "+";
		} else if (mode == '-') {
			adding = false;
			appliedModes += "-";
		} else if (mode == 'o' || mode == 'k' || mode == 'l') {
			if (argIndex >= args.size() || parameterizedCount >= 3) {
				client->reply(ERR_NEEDMOREPARAMS(host, nick, "MODE"));
				return ;
			}

			if (mode == 'o') {
				Client* target = _server->findClientByNickname(args[argIndex]);
				if (!target || !channel->getClients().count(target)) {
					client->reply(ERR_USERNOTINCHANNEL(host, nick, args[argIndex], channelName));
					return ;
				}
				if (adding) {
					channel->addOperator(target);
				} else {
					channel->removeOperator(target);
				}
				appliedModes += "o";
				appliedParams += " " + target->getNickname();
				argIndex++;
			} else if (mode == 'k') {
				if (parameterizedCount > 0) {
					client->reply(ERR_UNKNOWNMODE(host, nick, "k"));
					return ;
				}
				if (adding) {
					channel->setPassword(args[argIndex]);
				} else {
					channel->setPassword("");
				}
				appliedModes += "k";
				appliedParams += " " + args[argIndex];
				argIndex++;
			} else if (mode == 'l') {
				if (argIndex >= args.size()) {
					client->reply(ERR_NEEDMOREPARAMS(host, nick, "MODE"));
					return ;
				}
				std::string	limitStr = args[argIndex];
				for (size_t j = 0; j < limitStr.size(); j++) {
					if (!isdigit(limitStr[j])) {
						client->reply(ERR_UNKNOWNMODE(host, nick, "l"));
						return ;
					}
				}
				int limit = std::atoi(limitStr.c_str());
				if (adding) {
					channel->setLimit(limit);
				} else {
					channel->setLimit(0);
				}
				appliedModes += "l";
				appliedParams += " " + limitStr;
				argIndex++;
			}
			parameterizedCount++;
		} else if (mode == 'i') {
			channel->setInviteOnly(adding);
			appliedModes += "i";
		} else if (mode == 't') {
			channel->setTopicRestricted(adding);
			appliedModes += "t";
		} else {
			client->reply(ERR_UNKNOWNMODE(host, nick, std::string(1, mode)));
			return	;
		}
	}

	if (!appliedModes.empty()) {
		std::string	broadcastMsg = ":" + client->getPrefix() + " MODE " + channelName + " " + appliedModes + appliedParams;
		channel->broadcast(broadcastMsg, NULL);
	}
}
