#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

// - eсли клиент не прошёл PASS, он получает ошибку
// - eсли клиент не передал аргумент с никнеймом - ошибка
// - если ник уже занят (isNicknameTaken) - ошибка
// - или ник устанавливается, и клиент получает подтверждение

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	// Проверка: если клиент не аутентифицирован (не ввёл PASS)
	if (!client->isAuthenticated()) {
		std::string errorMsg = ":server 451 NICK :You have not registered\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	// Проверяем, передан ли никнейм
	if (args.empty()) {
		std::string errorMsg = ":server 431 :No nickname given\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	// Проверяем, занят ли никнейм
	if (_server->isNicknameTaken(args[0])) {
		std::string errorMsg = ":server 433 * "
								+ args[0]
								+ " :Nickname is already in use\r\n";
		send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
		return ;
	}

	// Устанавливаем никнейм и подтверждаем его установку
	client->setNickname(args[0]);
	client->setNicknameSet(true);
	std::string successMsg = ":server 001 "
								+ args[0]
								+ " :Nickname set successfully\r\n";
	send(client->getFd(), successMsg.c_str(), successMsg.size(), 0);
}
