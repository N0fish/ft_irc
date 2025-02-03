#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

class Channel {
	private:
		std::string			name;				// Название канала
		std::string			password;
		int					limit;
		std::set<Client*>	clients;			// Список клиентов в канале
		std::set<Client*>	bannedClients;   // Забаненные клиенты
    	std::set<Client*>	invitedClients;
		std::set<Client*>	operators;			// Множество операторов канала
		bool				inviteOnly;			// Флаг режима "по приглашению"
    	bool				topicRestricted;	// Флаг ограничения на изменение темы
		std::string			topic;
		std::string			topicSetter;
		time_t				topicSetTime;

	public:
		Channel(const std::string& name, const std::string& pass = "", int lim = 0);
		~Channel();

		const std::string&	getName() const;
		const std::string&	getPassword() const;
		void				setPassword(const std::string& pass);

		int					getLimit() const;
		void				setLimit(int limit);

		int					getUserCount() const;

		void				addClient(Client* client);
		void				removeClient(Client* client);

		bool				isBanned(Client* client) const;
		void				banClient(Client* client);
		void				unbanClient(Client* client);

		bool				isInvited(Client* client) const;
		void				addInvite(Client* client);
		void				removeInvite(Client* client);

		void				addOperator(Client* client);
		void				removeOperator(Client* client);

		bool				isEmpty() const;
		bool				isOperator(Client* client) const;

		bool				isInviteOnly() const;
		void				setInviteOnly(bool value);

		bool				isTopicRestricted() const;
		void				setTopicRestricted(bool value);

		const std::string&	getTopic() const;
		void				setTopic(const std::string& newTopic, Client* setter);
		bool				hasTopic() const;

		std::string			getTopicSetter() const;
		time_t				getTopicSetTime() const;

		void				broadcast(const std::string& message, Client* sender);
		const std::set<Client*>& getClients() const;

		bool 				isClientInChannel(Client* client) const;
};

#endif