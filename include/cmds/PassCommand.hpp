/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:07:54 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:32:18 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"

class PassCommand : public Command {
	public:
		PassCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif