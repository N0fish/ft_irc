#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		std::cout	<< "Error: No nickname provided."
					<< std::endl;
		return ;
	}

	client->setNickname(args[0]);
	std::cout	<< "Client nickname set to: "
				<< args[0]
				<< std::endl;
}
