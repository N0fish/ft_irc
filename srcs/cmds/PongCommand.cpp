#include "PongCommand.hpp"
/*
PONG command.
Replies to PING to confirm activity. If a second parameter is provided,
PONG is forwarded to that server.

Команда PONG.
Отвечает на PING, подтверждая активность клиента или сервера.
Если указан второй параметр, PONG пересылается указанному серверу.
*/
PongCommand::PongCommand(Server* server) : Command(server) {}

void	PongCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		client->reply(ERR_NOORIGIN(host, nick));
		return ;
	}
	client->updateActivity();
}
