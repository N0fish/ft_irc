/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:34 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:35 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class KickCommand : public Command {
	public:
		KickCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif