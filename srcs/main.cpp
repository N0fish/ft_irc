/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:24:13 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:24:13 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "libraries.hpp"

Server*	g_server = NULL;

void	signal_handler(int signal)
{
	if (signal == SIGINT && g_server != NULL) {
		g_server->cleanup();
		g_server = NULL;
		std::exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	int			port = std::atoi(argv[1]);
	std::string	password = argv[2];
	std::signal(SIGINT, signal_handler);
	try {
		Server server(port, password);
		g_server = &server;
		server.run();
		server.cleanup();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
