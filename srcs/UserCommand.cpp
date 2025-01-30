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
	client->reply(":server 001 USER :User registered successfully");

	if (client->isNicknameSet() && client->isUsernameSet()) {
		client->setState(REGISTERED);
	}
}
// если клиент не прошёл PASS - ошибка
// если клиент не установил NICK- ошибка
// если USER уже установлен - ошибка
// если не передан аргумент - ошибка
// - или имя пользователя устанавливается - registered successfully

// void UserCommand::execute(Client* client, const std::vector<std::string>& args) {
// 	// Проверка: если клиент не аутентифицирован (не ввёл PASS)
// 	if (!client->isAuthenticated()) {
// 		std::string errorMsg = ":server 451 USER :You have not registered\r\n";
// 		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
// 		return ;
// 	}

// 	// Проверка: если клиент не установил NICK
// 	if (!client->isNicknameSet()) {
// 		std::string errorMsg = ":server 461 USER :You must set a nickname first\r\n";
// 		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
// 		return ;
// 	}

// 	// Проверка: если клиент уже установил USER, повторно установить нельзя
// 	if (client->isUsernameSet()) {
// 		std::string errorMsg = ":server 462 USER :You may not reregister\r\n";
// 		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
// 		return ;
// 	}

// 	// Проверяем, передан ли аргумент
// 	if (args.empty()) {
// 		std::string errorMsg = ":server 461 USER :Not enough parameters\r\n";
// 		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
// 		return ;
// 	}

// 	// Устанавливаем имя пользователя
// 	client->setUsername(args[0]);
// 	client->setUsernameSet(true);
// 	std::string successMsg = ":server 001 USER :User registered successfully\r\n";
// 	send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
// }
