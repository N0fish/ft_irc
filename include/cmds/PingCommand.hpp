/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:55 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:55 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_COMMAND_HPP
# define PING_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class PingCommand : public Command {
	public:
		PingCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif