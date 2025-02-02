#include "PartCommand.hpp"
#include "Server.hpp"

// Конструктор команды PART
PartCommand::PartCommand(Server* server) : Command(server) {}

void	PartCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 PART :Not enough parameters");
		return ;
	}

	std::vector<std::string>	channelNames;
	std::stringstream			ss(args[0]);
	std::string					channelName;

	// Разбиваем список каналов по запятым
	while (getline(ss, channelName, ',')) {
		channelNames.push_back(channelName);
	}

	std::string reason = args.size() > 1 ? args[1] : "";

	for (size_t i = 0; i < channelNames.size(); ++i) {
		Channel* channel = _server->getChannel(channelNames[i]);
		if (!channel) {
			client->reply(":server 403 " + channelNames[i] + " :No such channel");
			continue ;
		}

		if (!client->isInChannel(channelNames[i])) {
			client->reply(":server 442 " + channelNames[i] + " :You're not on that channel");
			continue ;
		}

		// Отправляем сообщение о выходе
		std::string partMsg = client->getPrefix() + " PART " + channelNames[i];
		if (!reason.empty()) {
			partMsg += " :" + reason;
		}

		channel->broadcast(partMsg, client);
		channel->removeClient(client);
		client->leaveChannel(channelNames[i]);

		// Если канал пуст - удаляем его
		if (channel->isEmpty()) {
			_server->deleteChannel(channelNames[i]);
		}
	}
}

// Реализация метода execute
// void PartCommand::execute(Client* client, const std::vector<std::string>& args) {
//     // Проверяем наличие аргументов
//     if (args.empty()) {
//         std::string errorMsg = ":server 461 PART :Not enough parameters\r\n";
//         send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }

//     const std::string& channelName = args[0]; // Получаем имя канала

//     // Вызываем метод handlePART у сервера
//     server->handlePART(client->getFd(), channelName);
// }

// void Server::handlePART(int clientFd, const std::string& channelName) {
//     // Найти клиента по файловому дескриптору
//     Client* client = findClientByFd(clientFd);
//     if (!client) {
//         std::cerr << "Client not found for fd: " << clientFd << std::endl;
//         return;
//     }

//     // Проверить существование канала
//     if (channels.find(channelName) == channels.end()) {
//         std::string errorMsg = ":server 403 " + channelName + " :No such channel\r\n";
//         send(clientFd, errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }

//     // Проверить, состоит ли клиент в канале
//     if (!client->isInChannel(channelName)) {
//         std::string errorMsg = ":server 442 " + channelName + " :You're not on that channel\r\n";
//         send(clientFd, errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }

//     // Удалить клиента из канала
//     Channel* channel = channels[channelName];
//     channel->removeClient(client);
//     client->leaveChannel(channelName);

//     // Уведомление об успешном выходе
//     std::string successMsg = ":" + client->getNickname() + " PART :" + channelName + "\r\n";
//     send(clientFd, successMsg.c_str(), successMsg.size(), 0);

//     // Если канал пуст, удалить его
//     if (channel->isEmpty()) {
//         delete channel;
//         channels.erase(channelName);
//     }
// }
