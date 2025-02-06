#include "NickCommand.hpp"
/*
NICK command.
Allows a client to set or change their nickname.
Handles nickname validation, uniqueness, and broadcast of changes.
Supports error handling for invalid or already taken nicknames.

Команда NICK.
Позволяет клиенту установить или изменить никнейм.
Проверяет корректность ника, его уникальность и оповещает других пользователей об изменении.
Обрабатывает ошибки для неверных или уже занятых никнеймов.
*/
NickCommand::NickCommand(Server* server) : Command(server) {}

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (client->getState() == UNAUTHENTICATED) {
		client->reply(ERR_RESTRICTED(host, nick));
		return ;
	}
	if (args.empty()) {
		client->reply(ERR_NONICKNAMEGIVEN(host, nick));
		return ;
	}

	std::string	newNick = args[0];
	if (args.size() > 1) {
		client->reply(ERR_ERRONEUSNICKNAME(host, nick, newNick));
		return ;
	}
	const int	MAX_NICK_LEN = 9;
	if (newNick.length() > MAX_NICK_LEN) {
		client->reply(ERR_ERRONEUSNICKNAME(host, nick, newNick));
		return ;
	}
	std::string	allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-[]\\^{}";
	if (newNick.empty() || !std::isalpha(newNick[0])
		|| newNick.find_first_not_of(allowedChars) != std::string::npos) {
		client->reply(ERR_ERRONEUSNICKNAME(host, nick, newNick));
		return ;
	}
	if (_server->isNicknameTaken(args[0])) {
		client->reply(ERR_NICKNAMEINUSE(host, nick, newNick));
		return ;
	}
	std::string	oldNick = client->getNickname();
	_server->removeNickname(client->getNickname());
	client->setNickname(newNick);
	client->setNicknameSet(true);
	_server->addNickname(newNick);

	if (!client->isRegistered()) {
		client->reply(RPL_NICKNOTICE(host, newNick));
		if (client->isNicknameSet() && client->isUsernameSet()) {
			client->registerAction(_server);
		}
		return ;
	}

	_server->broadcast(RPL_NICKCHANGE(oldNick, client->getUsername(), newNick), NULL);
}
