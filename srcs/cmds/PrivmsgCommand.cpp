#include "PrivmsgCommand.hpp"
#include "Server.hpp"

// Конструктор команды PRIVMSG
PrivmsgCommand::PrivmsgCommand(Server* server) : Command(server) {}

void	PrivmsgCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) {
		client->reply(":server 461 PRIVMSG :Not enough parameters");
		return ;
	}

	std::string target = args[0];
	std::string message;

	// Собираем полное сообщение (объединяем все аргументы после первого)
	for (size_t i = 1; i < args.size(); ++i) {
		message += args[i] + " ";
	}

	// Убираем двоеточие в начале сообщения (если есть)
	if (!message.empty() && message[0] == ':') {
		message = message.substr(1);
	}

	// Если сообщение отправляется в канал
	if (target[0] == '#') {
		Channel* channel = _server->getChannel(target);
		if (!channel) {
			client->reply(":server 403 " + target + " :No such channel");
			return ;
		}

		// Проверка: является ли клиент участником канала
		if (!client->isInChannel(target)) {
			client->reply(":server 404 " + target + " :Cannot send to channel");
			return ;
		}

		// Отправляем сообщение всем участникам канала, кроме отправителя
		std::string msg = ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message;
		channel->broadcast(msg, client);
	}
	// Если сообщение отправляется пользователю
	else {
		Client* recipient = _server->findClientByNickname(target);
		if (!recipient) {
			client->reply(":server 401 " + target + " :No such nick");
			return ;
		}

		std::string msg = ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message;
		recipient->reply(msg);
	}
}

// Реализация метода execute
// void PrivmsgCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Перенаправляем выполнение команды на handlePRIVMSG
    // server->handlePRIVMSG(client, args);
// }

// void Server::handlePRIVMSG(Client* client, const std::vector<std::string>& args) {
//     if (args.size() < 2) {
//         std::string errorMsg = ":server 461 PRIVMSG :Not enough parameters\r\n";
//         send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }

//     const std::string& target = args[0];
//     const std::string& message = args[1];

//     if (target[0] == '#') { // Сообщение в канал
//         // Проверяем, существует ли канал
//         if (channels.find(target) == channels.end()) {
//             std::string errorMsg = ":server 403 " + target + " :No such channel\r\n";
//             send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
//             return;
//         }

//         // Получаем канал и отправляем сообщение всем клиентам
//         Channel* channel = channels[target];
//         std::set<Client*>::const_iterator it = channel->getClients().begin();
//         for (; it != channel->getClients().end(); ++it) {
//             Client* recipient = *it;
//             if (recipient != client) {
//                 std::string msg = ":" + client->getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";
//                 send(recipient->getFd(), msg.c_str(), msg.size(), 0);
//             }
//         }

//     } else { // Личное сообщение
//         // Ищем клиента по никнейму
//         Client* recipient = findClientByNickname(target);
//         if (!recipient) {
//             std::string errorMsg = ":server 401 " + target + " :No such nick\r\n";
//             send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
//             return;
//         }

//         // Отправляем личное сообщение
//         std::string msg = ":" + client->getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";
//         send(recipient->getFd(), msg.c_str(), msg.size(), 0);
//     }
// }
