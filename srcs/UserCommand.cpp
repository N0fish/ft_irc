#include "UserCommand.hpp"

UserCommand::UserCommand(Server* server) : Command(server) {}

void	UserCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (!client->isAuthenticated()) {
		std::cout	<< "Error: Client must authenticate with PASS first."
					<< std::endl;
		return ;
	}
	if (!client->isNicknameSet()) {
		std::cout	<< "Error: Client must set a nickname with NICK first."
					<< std::endl;
		return ;
	}
	if (client->isUsernameSet()) {
		std::cout	<< "Error: Username already set. Cannot change it."
					<< std::endl;
		return ;
	}

	if (args.empty()) {
		std::cout << "Error: No username provided." << std::endl;
		return ;
	}
	client->setUsername(args[0]);
	client->setUsernameSet(true);
	std::cout	<< "Client username set to: "
				<< args[0]
				<< std::endl;
}
