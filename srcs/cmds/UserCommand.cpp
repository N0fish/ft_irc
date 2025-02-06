#include "UserCommand.hpp"
#include "ListCommand.hpp"
#include "ReplyCodes.hpp"

UserCommand::UserCommand(Server *server) : Command(server) {}

void UserCommand::execute(Client *client, const std::vector<std::string> &args)
{
    std::string host = _server->getHostname();
    std::string nick = client->getNickname();

    if (client->getState() == UNAUTHENTICATED)
    { // если есть возможность оставить это условие за место второго. то оно будет лучше, так как проверяет на PASS and NICK, ну и написано в одном стиле с предыдущими командами
        client->reply(ERR_NOTREGISTERED(host, nick));
        return;
    }
    if (client->isUsernameSet())
    {
        client->reply(ERR_ALREADYREGISTERED(host, nick));
        return;
    }
    if (!client->isNicknameSet())
    {
        client->reply(ERR_NONICKNAME(host, nick));
        return;
    }
    if (args.size() < 4)
    {
        client->reply(ERR_NEEDMOREPARAMS(host, nick, "USER"));
        return;
    }
    if (args[0].size() > 9)
    {
        client->reply(ERR_INVALIDUSERNAME(host, nick, "(too long, max 9 chars)"));
        return;
    }
    if (!isNumber(args[1]))
    {
        client->reply(ERR_INVALIDPARAMS(host, nick, "USER"));
        return;
    }

    client->setUsername(args[0]);
    client->setUsernameSet(true);

    std::string realname = args[3];
    if (args[3][0] == ':')
    {
        realname = args[3].substr(1);
        for (size_t i = 4; i < args.size(); ++i)
        {
            realname += " " + args[i];
        }
    }
    client->setRealName(realname);
    client->reply(RPL_NOTICE(host, nick, "Username set successfully"));

    if (client->isNicknameSet() && client->isUsernameSet())
    {
        client->registerAction(_server);
    }
}
