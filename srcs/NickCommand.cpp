#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (!client->isAuthenticated()) {
		std::cout	<< "Error: Client must authenticate with PASS first."
					<< std::endl;
		return ;
	}

	if (args.empty()) {
		std::cout	<< "Error: No nickname provided."
					<< std::endl;
		return ;
	}

	if (_server->isNicknameTaken(args[0])) {
		std::cout	<< "Error: Nickname already in use."
					<< std::endl;
		return ;
	}

	client->setNickname(args[0]);
	client->setNicknameSet(true);
	std::cout	<< "Client nickname set to: "
				<< args[0]
				<< std::endl;
}
