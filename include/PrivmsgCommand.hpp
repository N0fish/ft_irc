#pragma once

#include "Command.hpp"
#include "Client.hpp"

// Класс для обработки команды PRIVMSG
class PrivmsgCommand : public Command {
protected:
    Server* server; // Указатель на сервер
    
public:
    PrivmsgCommand(Server* server); // Конструктор
    virtual void execute(Client* client, const std::vector<std::string>& args); // Выполнение команды
};
