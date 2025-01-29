#pragma once

#include "Command.hpp"
#include "Client.hpp"

// Класс команды JOIN
class JoinCommand : public Command {
protected:
    Server* server;
    
public:
    // Конструктор принимает указатель на сервер
    JoinCommand(Server* server);

    // Метод для выполнения команды
    virtual void execute(Client* client, const std::vector<std::string>& args);
};