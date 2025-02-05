#include "PingCommand.hpp"

PingCommand::PingCommand(Server* server) : Command(server) {}

void	PingCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 409 PING :No origin specified");
		return ;
	}

	std::string	pongMsg = "PONG " + args[0];

	// Если передан второй аргумент, отправляем PONG обратно на этот сервер (межсерверная проверка)
	if (args.size() > 1) {
		pongMsg += " " + args[1];
	}

	client->reply(pongMsg);
}
