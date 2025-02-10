/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:12 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:32:05 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_COMMAND_HPP
# define LIST_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class ListCommand : public Command {
	public:
		ListCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif