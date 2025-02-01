#include "UserCommand.hpp"
#include "ListCommand.hpp"

UserCommand::UserCommand(Server* server) : Command(server) {}

// проверка на то что ввел ли криент PASS и NICK
// если клиент не прошёл PASS - ошибка
// если клиент не установил NICK- ошибка
// если USER уже установлен - ошибка
// если не передан аргумент - ошибка
// - или имя пользователя устанавливается - registered successfully

void	UserCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client->getState() == UNAUTHENTICATED) {
		client->reply(":server 451 USER :You have not registered");
		return ;
	}

	if (!client->isNicknameSet()) {
		client->reply(":server 461 USER :You must set a nickname first");
		return ;
	}

	if (client->isUsernameSet()) {
		client->reply(":server 462 USER :You may not reregister");
		return ;
	}

	if (args.empty()) {
		client->reply(":server 461 USER :Not enough parameters");
		return ;
	}

	client->setUsername(args[0]);
	client->setUsernameSet(true);

	if (client->isNicknameSet() && client->isUsernameSet()) {
		client->setState(REGISTERED);
	}

	client->reply(":server 001 " + args[0] + " :Welcome to the IRC network "+ args[0] + "!!!");
	// client->reply(":server 002 " + args[0] + " :Your host is server, running version 1.0");
	// client->reply(":server 003 " + args[0] + " :This server was created Sun Feb 4 12:00:00 2024");
	// client->reply(":server 004 " + args[0] + " server 1.0 oirw abeiIklmnoOpqrstv");
	client->reply("PING :server");
	Command *listCmd = new ListCommand(_server);
	listCmd->execute(client, args);
	delete listCmd;
	// _server->handleCommand(client, "LIST");
}
