#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

// - eсли у клиента не прошёл PASS, он получает ошибку, и может его ввести только после того как клиент ввел PASS
// - eсли клиент не передал аргумент с никнеймом, то есть пустой - ошибка
// - если ник уже занят (isNicknameTaken) - ошибка
// - или ник устанавливается, и клиент получает подтверждение

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client->getState() == UNAUTHENTICATED) {
		client->reply(":server 451 NICK :You have not registered");
		return ;
	}

	if (args.empty()) {
		client->reply(":server 431 :No nickname given");
		return ;
	}

	if (_server->isNicknameTaken(args[0])) {
		client->reply(":server 433 * " + args[0] + " :Nickname is already in use");
		return ;
	}

	client->setNickname(args[0]);
	client->setNicknameSet(true);
	client->reply(":server 001 " + args[0] + " :Nickname set successfully");

	if (client->isNicknameSet() && client->isUsernameSet()) {
		client->setState(REGISTERED);
	}
}
