#include "PongCommand.hpp"

PongCommand::PongCommand(Server* server) : Command(server) {}

void	PongCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 409 PONG :No origin specified");
		return ;
	}

	client->updateActivity();
}
