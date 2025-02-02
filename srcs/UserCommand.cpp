#include "UserCommand.hpp"

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

	client->reply(":server NOTICE " + client->getUsername() + " :Username set successfully");
	if (client->isNicknameSet() && client->isUsernameSet()) {
		client->registerAction(_server);
	}

	// _server->handleCommand(client, "LIST");
}
