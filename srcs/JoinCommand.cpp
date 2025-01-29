#include "JoinCommand.hpp"
#include "Server.hpp"

// Конструктор команды JOIN
JoinCommand::JoinCommand(Server* server) : Command(server) {}

// Реализация метода execute
void JoinCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Перенаправляем вызов на handleJOIN в Server
    server->handleJOIN(client, args);
}
