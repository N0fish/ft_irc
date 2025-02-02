#include "JoinCommand.hpp"
#include "NamesCommand.hpp"
#include "libraries.hpp"

// Конструктор команды JOIN
JoinCommand::JoinCommand(Server* server) : Command(server) {}

void	JoinCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 JOIN :Not enough parameters");
		return ;
	}

	std::vector<std::string> channels = split(args[0], ',');
	for (size_t i = 0; i < channels.size(); i++) {
		std::string	channelName = channels[i];
		std::string	pass = args.size() > 1 ? args[1] : "";

		// JOIN 0 – клиент выходит из всех каналов
		if (channelName == "0") {
			for (size_t i = 0; i < client->getChannels().size(); i++) {
				Channel* channel = _server->getChannel(client->getChannels()[i]);
				if (channel) {
					channel->removeClient(client);
					channel->broadcast(client->getPrefix() + " PART " + channel->getName(), NULL);
					client->leaveChannel(channel->getName());

					if (channel->isEmpty()) {
						_server->deleteChannel(channel->getName());
					}
				}
			}
			return ;
		}

		if (channelName.empty() || channelName[0] != '#' || channelName.size() > 50) {
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			return ;
		}

		if (channelName.find_first_not_of('#') == std::string::npos) {
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			return ;
		}

		if (channelName.find(' ') != std::string::npos || channelName.find(',') != std::string::npos) {
			client->reply(":server 476 " + channelName + " :Invalid channel name");
			return ;
		}

		// Проверка на лимит каналов
		const int MAXCHANNELS = 10; // IRC-серверы обычно ограничивают число каналов на клиента
		if (client->getChannels().size() >= MAXCHANNELS) {
			client->reply(":server 405 " + channelName + " :You have joined too many channels");
			return ;
		}

		Channel* channel = _server->getChannel(channelName);
		bool isNewChannel = false;
		if (!channel) {
			// Если канал не существует, создаём его
			channel = _server->createChannel(channelName, pass, client);
			if (!channel) {
				client->reply(":server 403 " + channelName + " :Could not create channel");
				return ;
			}
			isNewChannel = true;
		}

		if (client->isInChannel(channelName)) {
			return ; // Если уже в канале- выходим
		}

		if (channel->getPassword() != pass && !channel->getPassword().empty()) { //Проверка пароля канала
			client->reply(":server 475 " + channelName + " :Cannot join channel (+k)");
			return ;
		}

		// Проверка, если клиент в бан-листе `+b`
		if (channel->isBanned(client)) {
			client->reply(":server 474 " + channelName + " :Cannot join channel (+b)");
			return ;
		}

		// Проверка, если канал имеет `+i` (инвайт-онли)
		if (channel->isInviteOnly() && !channel->isInvited(client)) {
			client->reply(":server 473 " + channelName + " :Cannot join channel (+i)");
			return ;
		}

		// // Если клиент был приглашён, удаляем его из списка приглашённых
		// channel->removeInvite(client);

		// Проверка лимита пользователей в канале
		if (channel->getLimit() > 0 && channel->getUserCount() >= channel->getLimit()) {
			client->reply(":server 471 " + channelName + " :Channel is full");
			return;
		}

		channel->addClient(client); //Добавляем клиента в канал
		client->joinChannel(channelName);

		if (isNewChannel) {
			channel->addOperator(client);  // Делаем первого участника оператором
		}

		// Сообщаем о входе
		std::string joinMsg = client->getPrefix() + " JOIN " + channelName;
		channel->broadcast(joinMsg, NULL);

		// Отправляем информацию о канале (Topic, User List)
		if (!channel->getTopic().empty()) {
			client->reply(":server 332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic());
		}
		std::vector<std::string> channels(1, channelName);
		(NamesCommand (_server)).execute(client, channels);
	}
}

// void JoinCommand::execute(Client* client, const std::vector<std::string>& args) {
//     // Перенаправляем вызов на handleJOIN в Server
//     server->handleJOIN(client, args);
// }

// void Server::handleJOIN(Client* client, const std::vector<std::string>& args) {
//     if (args.empty()) {
//         send(client->getFd(), ":server 461 JOIN :Not enough parameters\r\n", 43, 0);
//         return;
//     }

//     const std::string& channelName = args[0];

//     if (channels.find(channelName) == channels.end()) {
//         channels[channelName] = new Channel(channelName); // Создаем канал без пароля
//     }

//     Channel* channel = channels[channelName];
//     channel->addClient(client);
//     client->joinChannel(channelName);

//     std::string successMsg = ":" + client->getNickname() + " JOIN :" + channelName + "\r\n";
//     send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
// }