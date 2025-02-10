/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:21:46 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:21:49 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class PartCommand : public Command {
	public:
		PartCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif