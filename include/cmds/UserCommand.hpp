/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:51:37 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 14:51:39 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class UserCommand : public Command {
	public:
		UserCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif