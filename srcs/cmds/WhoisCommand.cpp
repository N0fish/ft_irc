#include "WhoisCommand.hpp"

WhoisCommand::WhoisCommand(Server* server) : Command(server) {}

void WhoisCommand::execute(Client* client, const std::vector<std::string>& args) {
    if (args.empty()) {
        client->reply(":" + _server->getHostname() + " 431 :No nickname given");
        return;
    }

    std::string targetNick = args[0];
    Client* target = _server->findClientByNickname(args[0]);
    if (!target) {
        client->reply(":" + _server->getHostname() + " 401 " + targetNick + " :No such nick");
        return;
    }

    //  Основная информация о пользователе (RPL_WHOISUSER - 311)
    std::string whoisInfo = ":" + _server->getHostname() + " 311 " + client->getNickname() +
                            " " + target->getNickname() + " " + target->getUsername() + " " +
                            target->getIpAddr() + " * :" + target->getRealName();
    client->reply(whoisInfo);

    //  Информация о сервере пользователя (RPL_WHOISSERVER - 312)
    std::string whoisServer = ":" + _server->getHostname() + " 312 " + client->getNickname() +
                              " " + target->getNickname() + " server_name :Server description";
    client->reply(whoisServer);

    //  Список каналов пользователя (RPL_WHOISCHANNELS - 319)
    std::string whoisChannels = ":" + _server->getHostname() + " 319 " + client->getNickname() +
                                " " + target->getNickname() + " :";
    const std::vector<std::string>& channels = target->getChannels();
    for (size_t i = 0; i < channels.size(); ++i) {
        if (i > 0) whoisChannels += " ";
        whoisChannels += channels[i];
    }
    client->reply(whoisChannels);

    // Время бездействия пользователя (RPL_WHOISIDLE - 317)
    std::ostringstream ss; // Используем std::ostringstream вместо std::to_string() для C++98
    ss << target->getIdleTime();
    std::string idleTimeStr = ss.str();

    std::string whoisIdle = ":" + _server->getHostname() + " 317 " + client->getNickname() +
                            " " + target->getNickname() + " " + idleTimeStr +
                            " :seconds idle";
    client->reply(whoisIdle);

    //  Завершение WHOIS (RPL_ENDOFWHOIS - 318)
    std::string whoisEnd = ":" + _server->getHostname() + " 318 " + client->getNickname() +
                           " " + target->getNickname() + " :End of WHOIS list";
    client->reply(whoisEnd);
}