/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:33:58 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:33:59 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListCommand.hpp"
/*
LIST command.
Provides the client with a list of all available channels on the server.
For each channel, it displays the channel name, the number of users,
and a default topic message.
The command sends a header message before the list and an end-of-list message after.

Команда LIST.
Предоставляет клиенту список всех доступных каналов на сервере.
Для каждого канала выводится его название, количество пользователей
и стандартное сообщение о теме.
Перед списком отправляется заголовочное сообщение, а после — сообщение о завершении.
*/
ListCommand::ListCommand(Server* server) : Command(server) {}

void	ListCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	client->reply(RPL_LISTSTART(host, nick));

	std::map<std::string, Channel*>	channels = _server->getChannels();
	std::set<std::string>			requestedChannels;
	if (!args.empty()) {
		std::vector<std::string>	splitArgs = split(args[0], ',');
		if (splitArgs.size() > 10) {
			client->reply(ERR_TOOMANYMATCHES(host, nick));
			return ;
		}
		requestedChannels.insert(splitArgs.begin(), splitArgs.end());
	}

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		Channel				*channel = it->second;
		std::stringstream	ss;
		ss << channel->getUserCount();

		std::string			topic = channel->getTopic();
		if (topic.empty()) {
			topic = ":";
		}

		if (!requestedChannels.empty() && requestedChannels.find(channel->getName()) == requestedChannels.end()) {
			continue;
		}

		client->reply(RPL_LIST(host, nick, channel->getName(), ss.str(), topic));
	}
	client->reply(RPL_LISTEND(host, nick));
}
