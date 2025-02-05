#include "InfoCommand.hpp"
/*
INFO command.
Provides the client with general information about the server,
including its version, developers, and startup time.
A message indicating the end of the information is sent at the end.

Команда INFO.
Предоставляет клиенту общую информацию о сервере, включая его версию,
авторов разработки и время запуска.
В конце отправляется сообщение об окончании информации.
*/
InfoCommand::InfoCommand(Server* server) : Command(server) {}

void	InfoCommand::execute(Client* client, const std::vector<std::string>& args) {
	(void)args;
	
	time_t		creationTime = _server->getCreationTime();
	char		timeBuffer[80];
	struct tm	*timeInfo = std::localtime(&creationTime);
	
	client->reply(":server 371 " + client->getNickname() + " :IRC Server version 1.0");
	client->reply(":server 371 " + client->getNickname() + " :Compiled on " + std::string(COMPILE_DATE) + " at " + std::string(COMPILE_TIME));
	client->reply(":server 371 " + client->getNickname() + " :Patch level: " + std::string("1.0.1"));
	client->reply(":server 371 " + client->getNickname() + " :Running on Linux x86_64");

	if (timeInfo) {
		std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
		client->reply(":server 371 " + client->getNickname() + " :Server started at " + std::string(timeBuffer));
	} else {
		client->reply(":server 371 " + client->getNickname() + " :Server start time unknown");
	}
	client->reply(":server 374 " + client->getNickname() + " :End of INFO");
}
