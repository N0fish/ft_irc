#include "PrivmsgCommand.hpp"
/*
PRIVMSG command.
Sends private messages to users or channels.
Supports server masks ($<mask>) and host masks (#<mask>) for operators.

Команда PRIVMSG.
Отправляет личные сообщения пользователям или сообщения в канал.
Поддерживает маски сервера ($<mask>) и хоста (#<mask>) для операторов.
*/
PrivmsgCommand::PrivmsgCommand(Server* server) : Command(server) {}

void	PrivmsgCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();

	if (args.empty()) {
		client->reply(ERR_NORECIPIENT(host, nick));
		return ;
	}
	if (args.size() < 2) {
		client->reply(ERR_NOTEXTTOSEND(host, nick));
		return ;
	}

	std::string	target = args[0];
	std::string	message;
	for (size_t i = 1; i < args.size(); ++i) {
		message += args[i] + " ";
	}
	if (!message.empty()) {
		message.erase(message.size() - 1);
	}
	if (!message.empty() && message[0] == ':') {
		message = message.substr(1);
	}

	if (std::string("#&+!").find(target[0]) != std::string::npos) {
		Channel*	channel = _server->getChannel(target);
		if (!channel) {
			client->reply(ERR_NOSUCHNICK(host, nick, target));
			return ;
		}
		if (!client->isInChannel(target)) {
			client->reply(ERR_CANNOTSENDTOCHAN(host, nick, target));
			return ;
		}

		std::string	msg = RPL_PRIVMSG(client->getPrefix(), target, message);
		channel->broadcast(msg, client);
	}
	else {
		Client*	recipient = _server->findClientByNickname(target);
		if (!recipient) {
			client->reply(ERR_NOSUCHNICK(host, nick, target));
			return ;
		}

		std::string	msg = RPL_PRIVMSG(client->getPrefix(), target, message);
		recipient->reply(msg);
	}
}
