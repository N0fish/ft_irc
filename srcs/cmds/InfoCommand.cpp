#include "InfoCommand.hpp"
/*
INFO command.
 Provides the client with general information about the server,
including its version, compilation date, patch level, system information,
startup time, and a fun fact about its developers.
 If a target server is specified, an error is returned because
this IRC server does not support a network of multiple servers.
 At the end, a message indicating the completion of the INFO response is sent.

Команда INFO.
 Предоставляет клиенту общую информацию о сервере, включая его версию,
дату компиляции, уровень патча, информацию о системе, время запуска,
а также забавный факт о разработчицах.
 Если указан целевой сервер, возвращается ошибка, так как
этот IRC-сервер не поддерживает сеть из нескольких серверов.
 В конце отправляется сообщение, указывающее на завершение ответа INFO.
*/
InfoCommand::InfoCommand(Server* server) : Command(server) {}

void	InfoCommand::execute(Client* client, const std::vector<std::string>& args) {
	std::string	host = _server->getHostname();
	std::string	nick = client->getNickname();
	if (!args.empty()) {
		client->reply(ERR_NOSUCHSERVER(host, client->getNickname(), args[0]));
		return ;
	}

	time_t		creationTime = _server->getCreationTime();
	char		timeBuffer[80];
	struct tm	*timeInfo = std::localtime(&creationTime);

	client->reply(RPL_INFO(host, nick, "IRC Server version 1.0"));
	client->reply(RPL_INFO(host, nick, "Compiled on "
								+ std::string(COMPILE_DATE) + " at " + std::string(COMPILE_TIME)));
	client->reply(RPL_INFO(host, nick, "Patch level: 1.0.1"));
	client->reply(RPL_INFO(host, nick, "Running on Linux x86_64"));
	client->reply(RPL_INFO(host, nick, "Developed by three girls from ecole42 ^_^"));

	if (timeInfo) {
		std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
		client->reply(RPL_INFO(host, nick, "Server started at " + std::string(timeBuffer)));
	} else {
		client->reply(RPL_INFO(host, nick, "Server start time unknown"));
	}
	client->reply(RPL_ENDOFINFO(host, client->getNickname()));
}
