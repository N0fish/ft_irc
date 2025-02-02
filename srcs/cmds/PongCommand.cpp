#include "PongCommand.hpp"
#include "Server.hpp"

PongCommand::PongCommand(Server* server) : Command(server) {}

void	PongCommand::execute(Client* client, const std::vector<std::string>& args) {
	(void) client;
	(void) args;
}
