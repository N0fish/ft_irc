#include "QuitCommand.hpp"
/*
QUIT command.
Handles user disconnection from the server.
If a quit message is provided, it is broadcasted to all channels.
The client receives a final ERROR message before disconnection.

Команда QUIT.
Обрабатывает отключение пользователя от сервера.
Если передано сообщение, оно транслируется в каналы.
Перед разрывом соединения клиент получает сообщение ERROR.
*/
QuitCommand::QuitCommand(Server* server) : Command(server) {}

void	QuitCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();

	std::string	quitMessage = "Client Quit";
	if (!args.empty()) {
		quitMessage = args[0][0] == ':' ? args[0].substr(1) : args[0];
	}

	std::string	quitMsg = RPL_QUIT(client->getPrefix(), quitMessage);
	_server->broadcast(quitMsg, client);
	client->reply(RPL_ERROR(host, nick, "Closing connection"));
	_server->removeClientFromChannels(client);
	_server->disconnectClient(client);
}
