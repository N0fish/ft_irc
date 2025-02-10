/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:09:35 by algultse          #+#    #+#             */
/*   Updated: 2025/02/03 21:10:09 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "libraries.hpp"

class Server;
class Client;

/*
Base class for all server commands.
Defines a common interface with the execute() method.

Базовый класс для всех команд сервера.
Определяет общий интерфейс с методом execute().
*/

class Command {
	protected:
		Server*	_server;

	public:
		Command(Server* server) : _server(server) {}
		virtual ~Command() {}

		virtual void	execute(Client* client, const std::vector<std::string>& args) = 0;
};

#endif