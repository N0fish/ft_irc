/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:52:01 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 14:52:02 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class NickCommand : public Command {
	public:
		NickCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif