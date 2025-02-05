#include "InfoCommand.hpp"
/*
INFO command.
Provides the client with general information about the server,
including its version, compilation date, patch level, system information, startup time, 
and a fun fact about its developers.
At the end, a message indicating the completion of the INFO response is sent.

Команда INFO.
Предоставляет клиенту общую информацию о сервере, включая его версию,
дату компиляции, уровень патча, информацию о системе, время запуска, 
а также забавный факт о разработчицах.
В конце отправляется сообщение, указывающее на завершение ответа INFO.
*/
InfoCommand::InfoCommand(Server* server) : Command(server) {}

void	InfoCommand::execute(Client* client, const std::vector<std::string>& args) {
	(void)args;
	
	time_t		creationTime = _server->getCreationTime();
	char		timeBuffer[80];
	struct tm	*timeInfo = std::localtime(&creationTime);
	
	client->reply(":server 371 " + client->getNickname() + " :IRC Server version 1.0");
	client->reply(":server 371 " + client->getNickname() + " :Compiled on "
								+ std::string(COMPILE_DATE) + " at " + std::string(COMPILE_TIME));
	client->reply(":server 371 " + client->getNickname() + " :Patch level: " + std::string("1.0.1"));
	client->reply(":server 371 " + client->getNickname() + " :Running on Linux x86_64");
	client->reply(":server 371 " + client->getNickname() + " :Developed by three girls from ecole42 ^_^");

	if (timeInfo) {
		std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
		client->reply(":server 371 " + client->getNickname() + " :Server started at " + std::string(timeBuffer));
	} else {
		client->reply(":server 371 " + client->getNickname() + " :Server start time unknown");
	}
	client->reply(":server 374 " + client->getNickname() + " :End of INFO");
}
