/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:29 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:30 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class JoinCommand : public Command {
	public:
		JoinCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif