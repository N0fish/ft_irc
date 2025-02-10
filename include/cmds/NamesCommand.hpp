/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NamesCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:51:49 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 14:51:51 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMES_COMMAND_HPP
# define NAMES_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class NamesCommand : public Command {
	public:
		NamesCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif