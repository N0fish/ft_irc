/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserhostCommand.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:22:20 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:21 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERHOST_COMMAND_HPP
# define USERHOST_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class UserhostCommand : public Command {
	public:
		UserhostCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif