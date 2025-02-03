#include "UserCommand.hpp"
#include "ListCommand.hpp"

UserCommand::UserCommand(Server* server) : Command(server) {}

void	UserCommand::execute(Client* client, const std::vector<std::string>& args) {
    if (client->isUsernameSet()) {
        client->reply(":" + _server->getHostname()
                    + " 462 " + client->getNickname() + " USER :You may not reregister");
        return ;
    }

    if (!client->isNicknameSet()) {
        client->reply(":" + _server->getHostname()
                    + " 461 " + client->getNickname() + " USER :You must set a nickname first");
        return ;
    }

    if (args.size() < 4) {
        client->reply(":" + _server->getHostname() 
                    + " 461 " + client->getNickname() + " USER :Not enough parameters");
        return ;
    }

    if (args[0].size() > 9) {
        client->reply(":" + _server->getHostname() + " 432 " + client->getNickname()
                    + " USER :Username is too long (max 9 characters)");
        return ;
    }

    client->setUsername(args[0]);
    client->setUsernameSet(true);

    std::string realname;
    if (args[3][0] == ':') { 
        realname = args[3].substr(1);
        for (size_t i = 4; i < args.size(); ++i) {
            realname += " " + args[i];
        }
    } else {
        realname = args[3];
    }

    client->setRealName(realname);
    client->reply(":" + _server->getHostname() + " NOTICE " + client->getNickname() +
                " :Username set successfully");

    if (client->isNicknameSet() && client->isUsernameSet()) {
        client->registerAction(_server);
    }
}
