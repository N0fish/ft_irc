/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:27 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 15:27:28 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_COMMAND_HPP
# define INFO_COMMAND_HPP

# include "Command.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)
# define COMPILE_DATE __DATE__
# define COMPILE_TIME __TIME__

class InfoCommand : public Command {
	public:
		InfoCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif