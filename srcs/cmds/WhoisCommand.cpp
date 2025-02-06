#include "WhoisCommand.hpp"
/*
WHOIS command.
Retrieves user information: nickname, username, IP, channels, idle time.

Команда WHOIS.
Получает информацию о пользователе: ник, имя, IP, каналы, время простоя.
*/
WhoisCommand::WhoisCommand(Server *server) : Command(server) {}

void	WhoisCommand::execute(Client *client, const std::vector<std::string> &args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
        client->reply(ERR_NONICKNAMEGIVEN(host, nick));
        return ;
    }

	for (size_t i = 0; i < args.size() && i < 5; ++i) { // Обрабатываем до 5 никнеймов
		std::string	targetNick = args[i];
		Client		*target = _server->findClientByNickname(targetNick);
		if (!target) {
			client->reply(ERR_NOSUCHNICK(host, nick, targetNick));
			continue;
		}
		client->reply(RPL_WHOISUSER(host, nick, target->getNickname(),
									target->getUsername(), target->getIpAddr(), target->getRealName()));
		client->reply(RPL_WHOISSERVER(host, nick, target->getNickname(), host, "42IRC Server"));

		for (size_t i = 0; i < target->getChannels().size(); ++i) {
			Channel*	channel = _server->getChannel(target->getChannels()[i]);
			if (channel && channel->isOperator(target)) {
				client->reply(RPL_WHOISOPERATOR(host, nick, target->getNickname()));
				break ;
			}
		}

		if (!target->getChannels().empty()) {
			std::string		channelList;
			for (size_t i = 0; i < target->getChannels().size(); ++i) {
				Channel*	channel = _server->getChannel(target->getChannels()[i]);
				if (channel) {
					std::string	prefix = channel->isOperator(target) ? "@" : "";
					if (!channelList.empty()) {
						channelList += " ";
					}
					channelList += prefix + target->getChannels()[i];
				}
			}
			client->reply(RPL_WHOISCHANNELS(host, nick, target->getNickname(), channelList));
		}

		std::ostringstream	idleTime;
		idleTime << target->getIdleTime();
		client->reply(RPL_WHOISIDLE(host, nick, target->getNickname(), idleTime.str(), target->getFormattedSignonTime()));
	}
	client->reply(RPL_ENDOFWHOIS(host, nick, args[0]));
}
