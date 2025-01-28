#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (!client->isAuthenticated()) {
		std::string errorMsg = ":server 451 NICK :You have not registered\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	if (args.empty()) {
		std::string errorMsg = ":server 431 :No nickname given\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	if (_server->isNicknameTaken(args[0])) {
		std::string errorMsg = ":server 433 * "
								+ args[0]
								+ " :Nickname is already in use\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	client->setNickname(args[0]);
	client->setNicknameSet(true);
	std::string successMsg = ":server 001 "
								+ args[0]
								+ " :Nickname set successfully\r\n";
	send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
}

// НЕТ ИСПОЛЬЗОВАНИЯ send()
// void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
// 	if (!client->isAuthenticated()) {
// 		std::cout	<< "Error: Client must authenticate with PASS first."
// 					<< std::endl;
// 		return ;
// 	}

// 	if (args.empty()) {
// 		std::cout	<< "Error: No nickname provided."
// 					<< std::endl;
// 		return ;
// 	}

// 	if (_server->isNicknameTaken(args[0])) {
// 		std::cout	<< "Error: Nickname already in use."
// 					<< std::endl;
// 		return ;
// 	}

// 	client->setNickname(args[0]);
// 	client->setNicknameSet(true);
// 	std::cout	<< "Client nickname set to: "
// 				<< args[0]
// 				<< std::endl;
// }
