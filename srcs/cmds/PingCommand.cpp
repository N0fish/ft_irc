/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:23:30 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:23:30 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCommand.hpp"
/*
PING command.
Checks if a client or server is active. Servers use PING to detect inactive connections.
If no response is received in time, the connection is closed.

Команда PING.
Проверяет, активен ли клиент или сервер. Серверы используют PING для обнаружения неактивных соединений.
Если в ответ не получен PONG в установленный срок, соединение разрывается.
*/
PingCommand::PingCommand(Server* server) : Command(server) {}

void	PingCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		client->reply(ERR_NOORIGIN(host, nick));
		return ;
	}

	std::string	pongMsg = RPL_PONG(host, args[0]);
	if (args.size() > 1) {
		pongMsg += " " + args[1];
	}
	client->reply(pongMsg);
}
