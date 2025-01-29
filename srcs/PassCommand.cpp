#include "PassCommand.hpp"

PassCommand::PassCommand(Server* server) : Command(server) {}

void	PassCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		std::string errorMsg = ":server 461 PASS :Not enough parameters\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		_server->disconnectClient(client);
		return ;
	}

	if (args[0] == _server->getPassword()) {
		client->setAuthenticated(true);
		std::string successMsg = ":server 001 PASS :Authentication successful\r\n";
		send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
	} else {
		std::string errorMsg = ":server 464 :Password incorrect\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		_server->disconnectClient(client);
	}
}
