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

	if (!message.empty()) {
		message.pop_back();
	}

	// Убираем двоеточие в начале сообщения (если есть)
	if (!message.empty() && message[0] == ':') {
		message = message.substr(1);
	}

	if (message.empty()) {
		client->reply(":server 412 PRIVMSG :No text to send");
		return ;
	}

	// Если сообщение отправляется в канал
	if (std::string("#&+!").find(target[0]) != std::string::npos) {
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

		std::string msg = client->getPrefix() + " PRIVMSG " + target + " :" + message;
		recipient->reply(msg);
	}
}
