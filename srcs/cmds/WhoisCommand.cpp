#include "WhoisCommand.hpp"

WhoisCommand::WhoisCommand(Server *server) : Command(server) {}

void	WhoisCommand::execute(Client *client, const std::vector<std::string> &args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (args.empty()) {
		return ;
	}

	std::string	targetNick = args[0];
	Client		*target = _server->findClientByNickname(targetNick);
	if (!target) {
		client->reply(":" + _server->getHostname() + " 401 " + targetNick + " :No such nick");
		return ;
	}

	std::string	whoisInfo = ":" + _server->getHostname() + " 311 " + client->getNickname() +
							" " + target->getNickname() + " " + target->getUsername() + " " +
							target->getIpAddr() + " * :" + target->getRealName();
	client->reply(whoisInfo);

	std::string	whoisServer = ":" + _server->getHostname() + " 312 " + client->getNickname() +
							" " + target->getNickname() + " " + _server->getHostname() +
							" :42IRC Server";
	client->reply(whoisServer);

	if (!target->getChannels().empty())
	{
		std::string	whoisChannels = ":" + _server->getHostname() + " 319 " + client->getNickname() +
									" " + target->getNickname() + " :";

		const std::vector<std::string>	&channels = target->getChannels();
		for (size_t i = 0; i < channels.size(); ++i)
		{
			std::string	prefix = "";
			Channel		*channel = _server->getChannel(channels[i]);
			if (channel && channel->isOperator(target))
			{
				prefix = "@";
			}
			whoisChannels += (i > 0 ? " " : "") + prefix + channels[i];
		}
		client->reply(whoisChannels);
	}

	std::ostringstream	idleTime;
	idleTime << target->getIdleTime();

	std::string whoisIdle = ":" + _server->getHostname() + " 317 " + client->getNickname() +
							" " + target->getNickname() + " " + idleTime.str() +
							" " + target->getFormattedSignonTime() + " :seconds idle, signon time";
	client->reply(whoisIdle);

	std::string	whoisEnd = ":" + _server->getHostname() + " 318 " + client->getNickname() +
						" " + target->getNickname() + " :End of WHOIS list";
	client->reply(whoisEnd);
}
