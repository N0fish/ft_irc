#include "UserCommand.hpp"
#include "ListCommand.hpp"

UserCommand::UserCommand(Server* server) : Command(server) {}

void	UserCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client->getState() == UNAUTHENTICATED) {
		client->reply(":" + _server->getHostname()
					+ " 451 " + client->getNickname() + " USER :You have not registered");
		// client->reply(":server 451 USER :You have not registered");
		return ;
	}

	if (!client->isNicknameSet()) {
		client->reply(":" + _server->getHostname()
					+ " 461 " + client->getNickname() + " USER :You must set a nickname first");
		// client->reply(":server 461 USER :You must set a nickname first");
		return ;
	}

	if (client->isUsernameSet()) {
		client->reply(":" + _server->getHostname()
					+ " 462 " + client->getNickname() + " USER :You may not reregister");
		client->reply(":server 462 USER :You may not reregister");
		return ;
	}

	// if (args.empty()) { // пока делаю тесты с одной командой, но вообще вроде как должно быть четыре. пока не разобралась на сколько это важно 4 аргумента
	// 	// client->reply(":server 461 USER :Not enough parameters");
	// 	client->reply(":" + _server->getHostname() 
	// 				+ " 461 " + client->getNickname() + " USER :Not enough parameters");
	// 	return ;
	// }

	if (args.size() < 4) {
		client->reply(":" + _server->getHostname() 
					+ " 461 " + client->getNickname() + " USER :Not enough parameters");
		// client->reply(":server 461 USER :Not enough parameters");
		return ;
	}

	client->setUsername(args[0]);
	client->setUsernameSet(true);
	client->setRealName(args[3]);

	client->reply(":" + _server->getHostname() + " NOTICE " + client->getNickname() +
				" :Username set successfully");
	// client->reply(":server NOTICE " + client->getUsername() + " :Username set successfully");
	// if (client->isNicknameSet() && client->isUsernameSet()) {
	// 	client->registerAction(_server);
	// }

	// Если PASS, NICK и USER уже введены, клиент считается зарегистрированным
	if (client->isNicknameSet() && client->isUsernameSet()) {
		client->registerAction(_server);
		// client->setState(REGISTERED);

		// // Отправляем приветствие и код 001
		// client->reply(":" + _server->getHostname() + " 001 " + client->getNickname() +
		// 			" :Welcome to the IRC Network " + client->getNickname() + "!" +
		// 			client->getUsername() + "@" + _server->getHostname());

		// client->reply(":" + _server->getHostname() + " 002 " + client->getNickname() +
		// 			" :Your host is " + _server->getHostname() + ", running version 1.0");

		// std::stringstream	ss;
		// ss << _server->getCreationTime();
		// client->reply(":" + _server->getHostname() + " 003 " + client->getNickname() +
		// 			" :This server was created " + ss.str());

		// client->reply(":" + _server->getHostname() + " 004 " + client->getNickname() +
		// 			" " + _server->getHostname() + " 1.0 o i k l b t");

		// // Отправляем список каналов после подключения
		// Command *listCmd = new ListCommand(_server);
		// listCmd->execute(client, std::vector<std::string>());
		// delete listCmd;
	}

	// _server->handleCommand(client, "LIST");
}
