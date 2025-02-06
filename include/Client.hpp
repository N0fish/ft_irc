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

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
/*
Class representing a connected IRC server client.
Manages client information, including nickname, username,
authentication state, list of channels, and invitations.
Also provides methods for sending messages and interacting with the server.

Класс, представляющий подключенного клиента IRC-сервера.
Управляет информацией о клиенте, включая его никнейм, имя пользователя,
статус аутентификации, список каналов и приглашений.
Также предоставляет методы для отправки сообщений и взаимодействия с сервером.
*/
enum ClientState {
    UNAUTHENTICATED,
    PASS_PROVIDED,
    REGISTERED
};

class Client {
	private:
		int							fd;
		std::string					ip;
		uint16_t					port;
		ClientState					state;
		std::string					partialMessage;
		std::string					nickname;
		std::string					username;
		std::string					realname;
		bool						nicknameSet;
		bool						usernameSet;
		std::vector<std::string>	channels;
		std::set<std::string>		invitedChannels;
		time_t						lastActivity;
		time_t						signonTime;

	public:
		Client(int fd, std::string, uint16_t port);
		~Client();

		int								getFd() const;
		void							reply(const std::string &message);

		ClientState						getState() const;
		void							setState(ClientState newState);

		std::string						getPartialMessage() const;
		void							setPartialMessage(const std::string &message);

		std::string						getNickname() const;
		void							setNickname(const std::string &nick);
		std::string						getUsername() const;
		void							setUsername(const std::string &user);
		std::string						getRealName() const;
		void							setRealName(const std::string &name);

		uint16_t						getPort() const;
		std::string						getPrefix() const;

		bool							isNicknameSet() const;
		void							setNicknameSet(bool set);
		bool							isUsernameSet() const;
		void							setUsernameSet(bool set);

		void							joinChannel(const std::string &channel);
		void							leaveChannel(const std::string &channel);
		bool							isInChannel(const std::string &channel);

		void							addInvite(const std::string &channel);
		bool							isInvited(const std::string &channel) const;

		bool							isRegistered() const;
		std::string						getIpAddr() const;

		const std::vector<std::string>	&getChannels() const;
		void							registerAction(Server *server);

		std::string						getServer() const;
		time_t							getIdleTime() const;
		time_t							getSignonTime() const;
		std::string						getFormattedSignonTime() const;
		time_t							getLastActivity() const;
		void							updateActivity();
};

#endif