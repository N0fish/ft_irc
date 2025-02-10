/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: econtess <econtess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:22:11 by econtess          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:12 by econtess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "Command.hpp"
# include "Channel.hpp"
# include "Client.hpp"

class TopicCommand : public Command {
	public:
		TopicCommand(Server* server);
		virtual void	execute(Client* client, const std::vector<std::string>& args);
};

#endif