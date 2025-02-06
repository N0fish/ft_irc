/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:23 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:25 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class InviteCommand : public Command {
	public:
		InviteCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif