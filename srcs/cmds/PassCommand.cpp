#include "PassCommand.hpp"
/*
PASS command.
Handles client authentication by verifying the connection password.
The password must be provided before registration (NICK/USER).
If authentication fails, the client is disconnected.

Команда PASS.
Обрабатывает аутентификацию клиента, проверяя пароль соединения.
Пароль должен быть предоставлен до регистрации (NICK/USER).
Если аутентификация не удалась, клиент отключается.
*/
PassCommand::PassCommand(Server* server) : Command(server) {}

void	PassCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();

	if (client->getState() != UNAUTHENTICATED) {
		client->reply(ERR_ALREADYREGISTRED(host, nick));
		return ;
	}

	if (args.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "PASS"));
		_server->disconnectClient(client);  
		return ;
	}

	if (args[0] != _server->getPassword()) {
		client->reply(ERR_PASSWDMISMATCH(host, nick));
		_server->disconnectClient(client);
		return;
	}
	client->setState(PASS_PROVIDED);
	client->reply(RPL_AUTH_SUCCESS(host));
}
