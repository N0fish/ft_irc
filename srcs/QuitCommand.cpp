#include "QuitCommand.hpp"

QuitCommand::QuitCommand(Server* server) : Command(server) {}

void	QuitCommand::execute(Client* client, const std::vector<std::string>& args) {
	(void) args;
	int fd = client->getFd();
	std::string nick = client->getNickname();
	std::cout << "Client(" << fd << ") " << nick << " QUIT REQUESTED" << std::endl;
	_server->disconnectClient(client);
	std::cout << "Client(" << fd << ") " << nick << " QUIT SUCCESS" << std::endl;
}
