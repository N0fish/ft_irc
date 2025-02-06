#include "TopicCommand.hpp"

TopicCommand::TopicCommand(Server* server) : Command(server) {}

void TopicCommand::execute(Client* client, const std::vector<std::string>& args) {
    if (args.size() < 1) {
        client->reply(":server 461 TOPIC :Not enough parameters");
        return;
    }

    std::string channelName = args[0];

    // Проверяем, существует ли канал
    Channel* channel = _server->getChannel(channelName);
    if (!channel) {
        client->reply(":server 403 " + channelName + " :No such channel");
        return;
    }

    // Проверяем, состоит ли клиент в канале
    if (!channel->getClients().count(client)) {
        client->reply(":server 442 " + channelName + " :You're not on that channel");
        return;
    }

    // Если передан только `TOPIC #channel`, отправляем текущую тему
    if (args.size() == 1) {
        if (channel->hasTopic()) {
            std::stringstream ss;
            ss << channel->getTopicSetTime(); // Преобразуем time_t в строку
            std::string topicTime = ss.str(); // Получаем строку

            client->reply(":server 332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic());
            client->reply(":server 333 " + client->getNickname() + " " + channelName + " " + channel->getTopicSetter() + " " + topicTime);
        } else {
            client->reply(":server 331 " + client->getNickname() + " " + channelName + " :No topic is set");
        }
        return;
    }

	// Проверяем, может ли клиент менять тему
	if (channel->isTopicRestricted() && !channel->isOperator(client)) {
		client->reply(":server 482 " + channelName + " :You're not channel operator");
		return ;
	}

	// Меняем тему канала
	std::string newTopic = args[1];
    if (newTopic.size() > 0 && newTopic[0] == ':') {
        newTopic.erase(0, 1);
    }
	channel->setTopic(newTopic, client);

	// Рассылаем всем пользователям обновлённую тему
	channel->broadcast(":" + client->getNickname() + " TOPIC " + channelName + " :" + newTopic, client);
}
