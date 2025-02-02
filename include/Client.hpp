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

enum ClientState {
    UNAUTHENTICATED, // Клиент только подключился	----- Никакие команды, кроме PASS
    PASS_PROVIDED, // Клиент ввел PASS				----- NICK, USER
    REGISTERED // Клиент ввел PASS, NICK и USER		----- Все команды
}; 
// этот инюм нужен, чтобы был порядок вначале комант PASS NICK USER, 
//до этого другие команды вводить нельзя

class Client {
	private:
		int							fd;				// Дескриптор клиента
		ClientState					state;			// Новый статус клиента
		std::string					partialMessage;	// Буфер для неполных сообщений
		std::string					nickname;		// Никнейм клиента
		std::string					username;		// Имя пользователя клиента
		bool						nicknameSet;	// Флаг установки никнейма
		bool						usernameSet;	// Флаг установки имени пользователя
		std::vector<std::string>	channels;		// Каналы, в которых состоит клиент
		std::set<std::string>		invitedChannels;

	public:
		Client(int fd);
		~Client();

		int			getFd() const;
		void		reply(const std::string& message); // Использовать для отправки сообщений через send()!!!!!

		ClientState	getState() const;
		void		setState(ClientState newState);

		std::string	getPartialMessage() const;
		void		setPartialMessage(const std::string& message);

		std::string	getNickname() const;
		void		setNickname(const std::string& nick);

		std::string	getUsername() const;
		void		setUsername(const std::string& user);

		std::string	getPrefix() const; // нужен серверу, чтобы формировать сообщения,  не изменяет состояние клиента, а просто возвращает данные.

		bool		isNicknameSet() const;
		void		setNicknameSet(bool set);

		bool		isUsernameSet() const;
		void		setUsernameSet(bool set);

		void 		joinChannel(const std::string& channel); // Добавление клиента в канал

		void 		leaveChannel(const std::string& channel); // Удаление клиента из канала
		bool 		isInChannel(const std::string& channel); // Проверка, состоит ли клиент в канале

		void		addInvite(const std::string& channel);
		bool		isInvited(const std::string& channel) const;

		bool		isRegistered() const;
		std::string	getIpAddr() const;
		std::string	getUserSymbol() const;

		const 		std::vector<std::string>&	getChannels() const; // Получение списка каналов
		void		registerAction(Server *server);
};

#endif