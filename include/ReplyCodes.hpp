#ifndef REPLY_CODES_HPP
# define REPLY_CODES_HPP

# include "RplNumerical.hpp"

// INFO
# define RPL_INFO(host, client, message) (":" + host + " 371 " + client + " :" + message)
# define RPL_ENDOFINFO(host, client) (":" + host + " 374 " + client + " :End of INFO")
# define ERR_NOSUCHSERVER(host, client, target) (":" + host + " 402 " + client + " " + target + " :No such server")

// INVITE
# define ERR_NEEDMOREPARAMS(host, client, command) (":" + host + " 461 " + client + " " + command + " :Not enough parameters")
# define ERR_NOSUCHNICK(host, client, nickname) (":" + host + " 401 " + client + " " + nickname + " :No such nick")
# define ERR_NOSUCHCHANNEL(host, client, nickname) (":" + host + " 403 " + client + " " + nickname + " :Cannot invite to local channels")
# define ERR_NOTONCHANNEL(host, client, channel) (":" + host + " 442 " + client + " " + channel + " :You're not on that channel")
# define ERR_USERONCHANNEL(host, client, nick, channel) (":" + host + " 443 " + client + " " + nick + " " + channel + " :User already on channel")
# define ERR_CHANOPRIVSNEEDED(host, client, channel) (":" + host + " 482 " + client + " " + channel + " :You're not channel operator")
# define RPL_INVITING(host, client, nick, channel) (":" + host + " 341 " + client + " " + nick + " " + channel)
# define RPL_INVITE(user_prefix, nick, channel) (":" + user_prefix + " INVITE " + nick + " :" + channel)

#endif