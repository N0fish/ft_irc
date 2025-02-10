/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:26:43 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:26:44 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class QuitCommand : public Command {
	public:
		QuitCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif