#include "PassCommand.hpp"

PassCommand::PassCommand(Server* server) : Command(server) {}

void	PassCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		std::cout	<< "Error: No password provided."
					<< std::endl;;
		_server->disconnectClient(client);
		return ;
	}

	if (args[0] == _server->getPassword()) {
		client->setAuthenticated(true);
		std::cout	<< "Client authenticated successfully."
					<< std::endl;;
	}
	else {
		std::cout	<< "Client provided incorrect password."
					<< std::endl;
		_server->disconnectClient(client);
	}
}
