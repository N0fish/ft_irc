#pragma once

#include "Command.hpp"
#include "Client.hpp"

// Класс для обработки команды PING
class PingCommand : public Command {
protected:
    Server* server; // Указатель на сервер
    
public:
    PingCommand(Server* server); // Конструктор
    virtual void execute(Client* client, const std::vector<std::string>& args); // Выполнение команды
};
