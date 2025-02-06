#include "TopicCommand.hpp"
/*
TOPIC command.
Allows users to view or change the topic of a channel.
- If no topic is provided, the current topic is shown.
- If a new topic is given, it is updated for the channel.
- If an empty topic is provided, the topic is removed.
- Topic changes may be restricted to operators.
- Updates are broadcasted to all channel members.

Команда TOPIC.
Позволяет пользователям просматривать или изменять тему канала.
- Без аргументов отображает текущую тему.
- Новый аргумент обновляет тему.
- Пустая строка удаляет тему.
- Изменение темы может быть ограничено операторами.
- Обновления рассылаются всем участникам канала.
*/
TopicCommand::TopicCommand(Server* server) : Command(server) {}

void TopicCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		client->reply(ERR_NEEDMOREPARAMS(host, nick, "TOPIC"));
		return ;
	}

	std::string	channelName = args[0];
	Channel*	channel = _server->getChannel(channelName);
	if (!channel) {
		client->reply(ERR_NOSUCHCHANNEL(host, nick, channelName));
		return ;
	}
	if (!channel->getClients().count(client)) {
		client->reply(ERR_NOTONCHANNEL(host, nick, channelName));
		return ;
	}

	if (args.size() == 1) {
		if (channel->hasTopic()) {
			std::stringstream	ss;
			ss << channel->getTopicSetTime();
			std::string	topicTime = ss.str();

			client->reply(RPL_TOPIC(host, nick, channelName, channel->getTopic()));
			client->reply(RPL_TOPICWHOTIME(host, nick, channelName, channel->getTopicSetter(), topicTime));
		} else {
			client->reply(RPL_NOTOPIC(host, nick, channelName));
		}
		return ;
	}

	if (channel->isTopicRestricted() && !channel->isOperator(client)) {
		client->reply(ERR_CHANOPRIVSNEEDED(host, nick, channelName));
		return ;
	}
	if (!channel->supportsTopic()) {
		client->reply(ERR_NOCHANMODES(host, client->getNickname(), channelName));
		return ;
	}
	std::string	newTopic = args[1];
	if (newTopic.size() > 0 && newTopic[0] == ':') {
		newTopic.erase(0, 1);
	}
	channel->setTopic(newTopic, client);

	std::string	msg = BROADCAST_TOPIC(client, channel, newTopic);
    channel->broadcast(msg, NULL);
}
