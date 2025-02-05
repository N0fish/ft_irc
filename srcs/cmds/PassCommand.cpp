#include "PassCommand.hpp"

PassCommand::PassCommand(Server* server) : Command(server) {}

void	PassCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client->getState() != UNAUTHENTICATED) {
		client->reply(":server 462 PASS :You may not reregister");
		return ;
	}

	if (args.empty()) {
		client->reply(":server 461 PASS :Not enough parameters");
		_server->disconnectClient(client);  
		return ;
	}

	if (args[0] != _server->getPassword()) {
		client->reply(":server 464 PASS :Password incorrect");
		_server->disconnectClient(client);
		return;
	}
	client->setState(PASS_PROVIDED);
	client->reply(":server NOTICE * :Authentication successful");
}
