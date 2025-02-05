#include "ListCommand.hpp"
/*
LIST command.
Provides the client with a list of all available channels on the server.
For each channel, it displays the channel name, the number of users,
and a default topic message.
The command sends a header message before the list and an end-of-list message after.

Команда LIST.
Предоставляет клиенту список всех доступных каналов на сервере.
Для каждого канала выводится его название, количество пользователей
и стандартное сообщение о теме.
Перед списком отправляется заголовочное сообщение, а после — сообщение о завершении.
*/
ListCommand::ListCommand(Server* server) : Command(server) {}

void	ListCommand::execute(Client* client, const std::vector<std::string>& args) {
	client->reply(":server 321 " + client->getNickname() + " Channel :Users  Topic");

	std::map<std::string, Channel*>	channels = _server->getChannels();
	std::set<std::string>			requestedChannels;

	if (!args.empty()) {
		std::vector<std::string>	splitArgs = split(args[0], ',');
		requestedChannels.insert(splitArgs.begin(), splitArgs.end());
	}

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		Channel				*channel = it->second;
		std::stringstream	ss;
		ss << channel->getUserCount();

		std::string			topic = channel->getTopic();
		if (topic.empty()) {
			topic = ":";
		}

		if (!requestedChannels.empty() && requestedChannels.find(channel->getName()) == requestedChannels.end()) {
			continue;
		}

		client->reply(":server 322 " + client->getNickname()
						+ " " + channel->getName()
						+ " " + ss.str()
						+ " :" + topic);
	}

	client->reply(":server 323 " + client->getNickname() + " :End of LIST");
}
