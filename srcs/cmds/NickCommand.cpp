#include "NickCommand.hpp"

NickCommand::NickCommand(Server* server) : Command(server) {}

void	NickCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (client->getState() == UNAUTHENTICATED) {
		client->reply(":server 451 NICK :You have not registered");
		return ;
	}
	if (args.empty()) {
		client->reply(":server 431 :No nickname given");
		return ;
	}
	std::string	newNick = args[0];
	if (args.size() > 1) {
		client->reply(":server 432 " + newNick + " :Erroneous nickname");
		return ;
	}

	const int	MAX_NICK_LEN = 9;
	if (newNick.length() > MAX_NICK_LEN) {
		client->reply(":server 432 " + newNick + " :Erroneous nickname");
		return ;
	}
	if (!std::isalpha(newNick[0])) {
		client->reply(":server 432 " + newNick + " :Erroneous nickname");
		return ;
	}
	std::string	allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-[]\\^{}";
	if (newNick.find_first_not_of(allowedChars) != std::string::npos) {
		client->reply(":server 432 " + newNick + " :Erroneous nickname");
		return ;
	}
	if (_server->isNicknameTaken(args[0])) {
		client->reply(":server 433 * " + args[0] + " :Nickname is already in use");
		return ;
	}
	std::string	oldNick = client->getNickname();

	_server->removeNickname(client->getNickname());
	client->setNickname(newNick);
	client->setNicknameSet(true);
	_server->addNickname(newNick);

	if (!client->isRegistered()) {
		client->reply(":server NOTICE " + newNick + " :Nickname set successfully");
		if (client->isNicknameSet() && client->isUsernameSet()) {
			client->registerAction(_server);
		}
		return ;
	}

	std::string	nickChangeMsg = ":" + oldNick + "!" + client->getUsername() + "@server NICK " + newNick;
	_server->broadcast(nickChangeMsg, NULL);
}
