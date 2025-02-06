/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:22:04 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:04 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_COMMAND_HPP
# define PRIVMSG_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class PrivmsgCommand : public Command {
	public:
		PrivmsgCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif