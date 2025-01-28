#include "UserCommand.hpp"

UserCommand::UserCommand(Server* server) : Command(server) {}

void UserCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (!client->isAuthenticated()) {
		std::string errorMsg = ":server 451 USER :You have not registered\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	if (!client->isNicknameSet()) {
		std::string errorMsg = ":server 461 USER :You must set a nickname first\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	if (client->isUsernameSet()) {
		std::string errorMsg = ":server 462 USER :You may not reregister\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	if (args.empty()) {
		std::string errorMsg = ":server 461 USER :Not enough parameters\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	client->setUsername(args[0]);
	client->setUsernameSet(true);
	std::string successMsg = ":server 001 USER :User registered successfully\r\n";
	send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
}

// НЕТ ИСПОЛЬЗОВАНИЯ send()
// void	UserCommand::execute(Client* client, const std::vector<std::string>& args) {
// 	if (!client->isAuthenticated()) {
// 		std::cout	<< "Error: Client must authenticate with PASS first."
// 					<< std::endl;
// 		return ;
// 	}
// 	if (!client->isNicknameSet()) {
// 		std::cout	<< "Error: Client must set a nickname with NICK first."
// 					<< std::endl;
// 		return ;
// 	}
// 	if (client->isUsernameSet()) {
// 		std::cout	<< "Error: Username already set. Cannot change it."
// 					<< std::endl;
// 		return ;
// 	}

// 	if (args.empty()) {
// 		std::cout << "Error: No username provided." << std::endl;
// 		return ;
// 	}
// 	client->setUsername(args[0]);
// 	client->setUsernameSet(true);
// 	std::cout	<< "Client username set to: "
// 				<< args[0]
// 				<< std::endl;
// }
