#include "PingCommand.hpp"
#include "Server.hpp"

// Конструктор команды PING
PingCommand::PingCommand(Server* server) : Command(server) {}

// Реализация метода execute
void PingCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Перенаправляем выполнение команды на handlePING
    server->handlePING(client, args);
}
