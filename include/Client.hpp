/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:34:05 by algultse          #+#    #+#             */
/*   Updated: 2025/01/26 23:53:34 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// чтобы на будущее добавить время когда начала и хедеры везде

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"

class Client {
	private:
		int			fd;
		bool		authenticated;
		std::string	partialMessage;
		std::string	nickname;

	public:
		Client(int fd);
		~Client();

		int			getFd() const;
		bool		isAuthenticated() const;
		void		setAuthenticated(bool auth);
		std::string	getPartialMessage() const;
		void		setPartialMessage(const std::string& message);

		std::string	getNickname() const;
		void		setNickname(const std::string& nick);
};

#endif
