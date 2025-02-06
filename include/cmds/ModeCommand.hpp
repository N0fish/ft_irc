/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:00 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:27:01 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_COMMAND_HPP
# define MODE_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class ModeCommand : public Command {
	public:
		ModeCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif