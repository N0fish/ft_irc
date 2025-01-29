#include "PrivmsgCommand.hpp"
#include "Server.hpp"

// Конструктор команды PRIVMSG
PrivmsgCommand::PrivmsgCommand(Server* server) : Command(server) {}

// Реализация метода execute
void PrivmsgCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Перенаправляем выполнение команды на handlePRIVMSG
    server->handlePRIVMSG(client, args);
}
