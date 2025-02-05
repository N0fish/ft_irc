#include "ModeCommand.hpp"

ModeCommand::ModeCommand(Server* server) : Command(server) {}

void	ModeCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.size() < 2) {
		client->reply(":server 461 MODE :Not enough parameters");
		return ;
	}

	std::string	channelName = args[0];
	if (channelName.empty() || std::string("#&+!").find(channelName[0]) == std::string::npos) {
		client->reply(":server 403 " + channelName + " :No such channel");
		return ;
	}
	if (channelName.find(',') != std::string::npos) {
		client->reply(":server 461 MODE :Not enough parameters");
		return ;
	}

	Channel*	channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(":server 403 " + channelName + " :No such channel");
		return ;
	}

	if (args.size() == 1) {
		std::string	modes = "+";
		if (channel->isInviteOnly()) modes += "i";
		if (channel->isTopicRestricted()) modes += "t";
		if (!channel->getPassword().empty()) modes += "k";
		if (channel->getLimit() > 0) modes += "l";

		client->reply(":server 324 " + client->getNickname() + " " + channelName + " " + modes);
		return ;
	}

	if (!channel->isOperator(client)) {
		client->reply(":server 482 " + channelName + " :You're not channel operator");
		return ;
	}

	std::string	modeString = args[1];
	bool		adding = true;
	size_t		argIndex = 2;

	std::string	broadcastMsg = client->getPrefix() + " MODE " + channelName + " ";  
	std::string	appliedModes; 

	for (size_t i = 0; i < modeString.size(); ++i) {
		char	mode = modeString[i];

		if (mode == '+') {
			adding = true;
			appliedModes += "+";
		} else if (mode == '-') {
			adding = false;
			appliedModes += "-";
		} else if (mode == 'o') { // Назначение оператора
			if (argIndex >= args.size()) {
				client->reply(":server 461 MODE :Not enough parameters");
				return ;
			}
			Client* target = _server->findClientByNickname(args[argIndex++]);
			if (!target || !channel->getClients().count(target)) {
				client->reply(":server 441 " + args[argIndex - 1] + " " + channelName + " :They aren't on that channel");
				return ;
			}
			if (adding) {
				channel->addOperator(target);
			} else {
				channel->removeOperator(target);
			}
			appliedModes += "o " + target->getNickname() + " ";
		} else if (mode == 'i') { // Режим "по приглашению"
			channel->setInviteOnly(adding);
			appliedModes += "i ";
			// channel->broadcast(":server 324 " + client->getNickname() + " " + channelName + (adding ? " +i" : " -i"), NULL);
		} else if (mode == 't') { // Ограничение на изменение темы
			channel->setTopicRestricted(adding);
			appliedModes += "t ";
			// channel->broadcast(":server 324 " + client->getNickname() + " " + channelName + (adding ? " +t" : " -t"), NULL);
		} else if (mode == 'k') { // Пароль
			if (adding) {
				if (argIndex >= args.size()) {
					client->reply(":server 461 MODE :Not enough parameters");
					return ;
				}
				channel->setPassword(args[argIndex++]);
			} else {
				channel->setPassword("");
			}
			appliedModes += "k ";
		} else if (mode == 'l') { // Лимит пользователей
			if (adding) {
				if (argIndex >= args.size()) {
					client->reply(":server 461 MODE :Not enough parameters");
					return ;
				}
				int limit = std::atoi(args[argIndex++].c_str());
				channel->setLimit(limit);
			} else {
				channel->setLimit(0);
			}
			appliedModes += "l ";
		} else if (mode == 'b') { // Бан пользователя
			if (argIndex >= args.size()) {
				client->reply(":server 461 MODE :Not enough parameters");
				return ;
			}
			Client* target = _server->findClientByNickname(args[argIndex++]);
			if (!target || !channel->getClients().count(target)) {
				client->reply(":server 441 " + args[argIndex - 1] + " " + channelName + " :They aren't on that channel");
				return ;
			}
			if (adding) {
				channel->banClient(target);
			} else {
				channel->unbanClient(target);
			}
			appliedModes += "b " + target->getNickname() + " ";
		} else {
			client->reply(":server 501 MODE :Unknown mode flag");
		}
	}
	if (!appliedModes.empty()) {
		channel->broadcast(broadcastMsg + appliedModes, NULL);
	}
}
