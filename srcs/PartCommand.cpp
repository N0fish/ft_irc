#include "PartCommand.hpp"
#include "Server.hpp"

// Конструктор команды PART
PartCommand::PartCommand(Server* server) : Command(server) {}

// Реализация метода execute
void PartCommand::execute(Client* client, const std::vector<std::string>& args) {
    // Проверяем наличие аргументов
    if (args.empty()) {
        std::string errorMsg = ":server 461 PART :Not enough parameters\r\n";
        send(client->getFd(), errorMsg.c_str(), errorMsg.size(), 0);
        return;
    }

    const std::string& channelName = args[0]; // Получаем имя канала

    // Вызываем метод handlePART у сервера
    server->handlePART(client->getFd(), channelName);
}
