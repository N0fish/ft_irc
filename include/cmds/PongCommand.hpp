/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PongCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:59 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:00 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONG_COMMAND_HPP
# define PONG_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class PongCommand : public Command {
	public:
		PongCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif