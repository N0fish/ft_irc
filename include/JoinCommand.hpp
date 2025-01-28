#pragma once

#include "Command.hpp"
#include "Client.hpp"

class JoinCommand : public Command {
public:
    JoinCommand(Server* server); // Конструктор
    virtual void execute(Client* client, const std::vector<std::string>& args); // Выполнение команды
};

