#include "PassCommand.hpp"

PassCommand::PassCommand(Server* server) : Command(server) {}

// Это первое, что должен сделать клиент !!! Если нет PASS, другие команды не работают

void	PassCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 461 PASS :Not enough parameters");
		_server->disconnectClient(client);
		return ;
	}

	if (client->getState() != UNAUTHENTICATED) {
		client->reply(":server 462 PASS :You may not reregister");
		return ;
	}

	if (args[0] == _server->getPassword()) {
		client->setState(PASS_PROVIDED);
		client->reply(":server 001 PASS :Authentication successful");
	} else {
		client->reply(":server 464 :Password incorrect");
		_server->disconnectClient(client);
	}
}
