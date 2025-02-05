#ifndef REPLY_CODES_HPP
# define REPLY_CODES_HPP

# define ERR_NEEDMOREPARAMS(host, client, command) (":" + host + " 461 " + client + " " + command + " :Not enough parameters")
# define ERR_NOSUCHCHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :No such channel")
# define ERR_CHANOPRIVSNEEDED(host, client, channel) (":" + host + " 482 " + client + " " + channel + " :You're not channel operator")
# define ERR_BADCHANMASK(host, client, channel) (":" + host + " 476 " + client + " " + channel + " :Invalid channel name")
# define ERR_NOTONCHANNEL(host, client, channel) (":" + host + " 442 " + client + " " + channel + " :You're not on that channel")
# define ERR_NOSUCHSERVER(host, client, target) (":" + host + " 402 " + client + " " + target + " :No such server")
# define ERR_USERNOTINCHANNEL(host, client, nick, channel) (":" + host + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel")

// INFO
# define RPL_INFO(host, client, message) (":" + host + " 371 " + client + " :" + message)
# define RPL_ENDOFINFO(host, client) (":" + host + " 374 " + client + " :End of INFO")

// INVITE
# define ERR_NOSUCHNICK(host, client, nickname) (":" + host + " 401 " + client + " " + nickname + " :No such nick")
# define ERR_NOSUCHCHANNELL(host, client, nickname) (":" + host + " 403 " + client + " " + nickname + " :Cannot invite to local channels")
# define ERR_USERONCHANNEL(host, client, nick, channel) (":" + host + " 443 " + client + " " + nick + " " + channel + " :User already on channel")
# define RPL_INVITING(host, client, nick, channel) (":" + host + " 341 " + client + " " + nick + " " + channel)
# define RPL_INVITE(user_prefix, nick, channel) (":" + user_prefix + " INVITE " + nick + " :" + channel)

// JOIN
# define ERR_TOOMANYCHANNELS(host, client, channel) (":" + host + " 405 " + client + " " + channel + " :You have joined too many channels")
# define ERR_INVITEONLYCHAN(host, client, channel) (":" + host + " 473 " + client + " " + channel + " :Cannot join channel (+i)")
# define ERR_BANNEDFROMCHAN(host, client, channel) (":" + host + " 474 " + client + " " + channel + " :Cannot join channel (+b)")
# define ERR_BADCHANNELKEY(host, client, channel) (":" + host + " 475 " + client + " " + channel + " :Cannot join channel (+k)")
# define ERR_CHANNELISFULL(host, client, channel) (":" + host + " 471 " + client + " " + channel + " :Channel is full")
# define ERR_UNAVAILRESOURCE(host, client, channel) (":" + host + " 437 " + client + " " + channel + " :Nick/channel is temporarily unavailable")
# define ERR_CANNOTCREATECHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :Cannot create local channel manually")
# define ERR_CHANNELNAMENOTUNIQUE(host, client, channel) (":" + host + " 476 " + client + " " + channel + " :Channel name must be unique")
# define ERR_DUPLICATELOCALCHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :Cannot create local channel with duplicate name")

# define RPL_TOPIC(host, client, channel, topic) (":" + host + " 332 " + client + " " + channel + " :" + topic)
# define RPL_NOTOPIC(host, client, channel) (":" + host + " 331 " + client + " " + channel + " :No topic is set")
# define RPL_NAMREPLY(host, client, symbol, channel, list_of_nicks) (":" + host + " 353 " + client + " " + symbol + " " + channel + " :" + list_of_nicks)
# define RPL_ENDOFNAMES(host, client, channel) (":" + host + " 366 " + client + " " + channel + " :End of /NAMES list")
# define RPL_JOIN(user_prefix, channel) (":" + user_prefix + " JOIN " + channel)

// KICK
# define RPL_KICK(client_prefix, channel, target, reason) (":" + client_prefix + " KICK " + channel + " " + target + " :" + reason)

// LIST
# define ERR_TOOMANYMATCHES(host, client) (":" + host + " 416 " + client + " :Too many matches")
# define RPL_LISTSTART(host, client) (":" + host + " 321 " + client + " Channel :Users  Topic")
# define RPL_LIST(host, client, channel, users, topic) (":" + host + " 322 " + client + " " + channel + " " + users + " :" + topic)
# define RPL_LISTEND(host, client) (":" + host + " 323 " + client + " :End of LIST")

// MODE
# define ERR_NOCHANMODES(host, client, channel) (":" + host + " 477 " + client + " " + channel + " :Channel does not support modes")
# define ERR_UNKNOWNMODE(host, client, mode) (":" + host + " 472 " + client + " " + mode + " :Unknown mode")
# define ERR_KEYSET(host, client, channel) (":" + host + " 467 " + client + " " + channel + " :Channel key already set")

# define RPL_CHANNELMODEIS(host, client, channel, modes) (":" + host + " 324 " + client + " " + channel + " " + modes)
# define RPL_BANLIST(host, client, channel, mask) (":" + host + " 367 " + client + " " + channel + " " + mask)
# define RPL_ENDOFBANLIST(host, client, channel) (":" + host + " 368 " + client + " " + channel + " :End of ban list")

#endif