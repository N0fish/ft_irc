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

// чтобы на будущее добавить время, когда начала, и хедеры не забыть поставить везде

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"

class Client {
	private:
		int			fd;				// Дескриптор клиента
		bool		authenticated;	// Флаг аутентификации
		std::string	partialMessage;	// Буфер для неполных сообщений
		std::string	nickname;		// Никнейм клиента
		std::string	username;		// Имя пользователя клиента
		bool		nicknameSet;	// Флаг установки никнейма
		bool		usernameSet;	// Флаг установки имени пользователя
		std::vector<std::string> channels; // Каналы, в которых состоит клиент

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

		std::string	getUsername() const;
		void		setUsername(const std::string& user);

		bool		isNicknameSet() const;
		void		setNicknameSet(bool set);

		bool		isUsernameSet() const;
		void		setUsernameSet(bool set);

		void 		joinChannel(const std::string& channel); // Добавление клиента в канал

		void 		leaveChannel(const std::string& channel); // Удаление клиента из канала
		bool 		isInChannel(const std::string& channel); // Проверка, состоит ли клиент в канале

		const std::vector<std::string>& getChannels() const; // Получение списка каналов
};

#endif