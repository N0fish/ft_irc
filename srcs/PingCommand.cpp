#include "PingCommand.hpp"
#include "Server.hpp"

// Конструктор команды PING
PingCommand::PingCommand(Server* server) : Command(server) {}

void	PingCommand::execute(Client* client, const std::vector<std::string>& args) {
	if (args.empty()) {
		client->reply(":server 409 PING :No origin specified");
		return ;
	}

	std::string target = args[0];
	std::string pongMsg = ":server PONG :" + target;

	// Если передан второй аргумент, отправляем PONG обратно на этот сервер (межсерверная проверка)
	if (args.size() > 1) {
		pongMsg += " " + args[1];
	}

	client->reply(pongMsg);
}

// void PingCommand::execute(Client* client, const std::vector<std::string>& args) {
//     if (args.empty()) {
//         client->reply(":server 409 PING :No origin specified");
//         return;
//     }
//     std::string pongMsg = ":server PONG :" + args[0];
//     client->reply(pongMsg);
// }

// Реализация метода execute
// void PingCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Перенаправляем выполнение команды на handlePING
    // server->handlePING(client, args);
// }

// void Server::handlePING(Client* client, const std::vector<std::string>& args) {
//     if (args.empty()) {
//         // Если аргументы отсутствуют, отправляем ошибку
//         std::string errorMsg = ":server 409 PING :No origin specified\r\n";
//         send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
//         return;
//     }

//     // Формируем PONG-ответ
//     std::string pongMsg = ":server PONG :" + args[0] + "\r\n";
//     send(client->getFd(), pongMsg.c_str(), pongMsg.size(), 0);
// }