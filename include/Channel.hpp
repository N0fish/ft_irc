#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

class Channel {
	private:
		std::string			name;		// Название канала
		std::set<Client*>	clients;	// Список клиентов в канале

	public:
		Channel(const std::string& name);
		~Channel();

		const std::string&	getName() const;
		void				addClient(Client* client);
		void				removeClient(Client* client);
		bool				isEmpty() const;
		void				broadcast(const std::string& message, Client* sender);
};

#endif