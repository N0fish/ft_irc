/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoisCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:22:25 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:26 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHOIS_COMMAND_HPP
# define WHOIS_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class WhoisCommand : public Command {
	public:
		WhoisCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif