/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReplyCodes.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:07:54 by algultse          #+#    #+#             */
/*   Updated: 2025/02/06 06:36:31 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_CODES_HPP
# define REPLY_CODES_HPP

// general
# define ERR_NEEDMOREPARAMS(host, client, command) (":" + host + " 461 " + client + " " + command + " :Not enough parameters")
# define ERR_INVALIDPARAMS(host, client, command) (":" + host + " 461 " + client + " " + command + " :Invalid parameteers")
# define ERR_NOSUCHCHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :No such channel")
# define ERR_CHANOPRIVSNEEDED(host, client, channel) (":" + host + " 482 " + client + " " + channel + " :You're not channel operator")
# define ERR_BADCHANMASK(host, client, channel) (":" + host + " 476 " + client + " " + channel + " :Invalid channel name")
# define ERR_NOTONCHANNEL(host, client, channel) (":" + host + " 442 " + client + " " + channel + " :You're not on that channel")
# define ERR_NOSUCHSERVER(host, client, target) (":" + host + " 402 " + client + " " + target + " :No such server")
# define ERR_USERNOTINCHANNEL(host, client, nick, channel) (":" + host + " 441 " + client + " " + nick + " " + channel + " :They aren't on that channel")
# define ERR_TOOMANYMATCHES(host, client) (":" + host + " 416 " + client + " :Too many matches")
# define RPL_NAMREPLY(host, client, symbol, channel, list_of_nicks) (":" + host + " 353 " + client + " " + symbol + " " + channel + " :" + list_of_nicks)
# define ERR_UNAVAILRESOURCE(host, client, nicknameorchannel) (":" + host + " 437 " + client + " " + nicknameorchannel + " :Nick/channel is temporarily unavailable")
# define ERR_NOSUCHNICK(host, client, nickname) (":" + host + " 401 " + client + " " + nickname + " :No such nick")

# define RPL_NOTICE(host, client, message) (":" + host + " NOTICE " + client + " :" + message)

// INFO
# define RPL_INFO(host, client, message) (":" + host + " 371 " + client + " :" + message)
# define RPL_ENDOFINFO(host, client) (":" + host + " 374 " + client + " :End of INFO")

// INVITE
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
# define ERR_CANNOTCREATECHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :Cannot create local channel manually")
# define ERR_CHANNELNAMENOTUNIQUE(host, client, channel) (":" + host + " 476 " + client + " " + channel + " :Channel name must be unique")
# define ERR_DUPLICATELOCALCHANNEL(host, client, channel) (":" + host + " 403 " + client + " " + channel + " :Cannot create local channel with duplicate name")

# define RPL_TOPIC(host, client, channel, topic) (":" + host + " 332 " + client + " " + channel + " :" + topic)
# define RPL_JOIN(user_prefix, channel) (":" + user_prefix + " JOIN " + channel)

// KICK
# define RPL_KICK(client_prefix, channel, target, reason) (":" + client_prefix + " KICK " + channel + " " + target + " :" + reason)

// LIST
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

// NAMES
# define RPL_ENDOFNAMES(host, client, channel) (":" + host + " 366 " + client + " " + channel + " :End of NAMES list")

// NICK
# define ERR_NONICKNAMEGIVEN(host, client) (":" + host + " 431 " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(host, client, nickname) (":" + host + " 432 " + client + " " + nickname + " :Erroneous nickname")
# define ERR_NICKNAMEINUSE(host, client, nickname) (":" + host + " 433 " + client + " " + nickname + " :Nickname is already in use")
# define ERR_NICKCOLLISION(host, client, nickname) (":" + host + " 436 " + client + " " + nickname + " :Nickname collision detected")
# define ERR_RESTRICTED(host, client) (":" + host + " 484 " + client + " :Your connection is restricted")
# define RPL_NICKNOTICE(host, newNick) (":" + host + " NOTICE " + newNick + " :Nickname set successfully")
# define RPL_NICKCHANGE(oldNick, username, newNick) (":" + oldNick + "!" + username + "@server NICK " + newNick)

// PART
# define RPL_PART(user_prefix, channel, reason) (":" + user_prefix + " PART " + channel + (reason.empty() ? "" : " :" + reason))

// PASS
# define ERR_ALREADYREGISTRED(host, client) (":" + host + " 462 " + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(host, client) (":" + host + " 464 " + client + " :Password incorrect")
# define RPL_AUTH_SUCCESS(host) (":" + host + " NOTICE * :Authentication successful")

// PING/PONG
# define ERR_NOORIGIN(host, client) (":" + host + " 409 " + client + " :No origin specified")
# define RPL_PONG(server, target) ("PONG " + server + " " + target)

// PRIVMSG
# define ERR_NORECIPIENT(host, client) (":" + host + " 411 " + client + " :No recipient given (PRIVMSG)")
# define ERR_NOTEXTTOSEND(host, client) (":" + host + " 412 " + client + " :No text to send")
# define ERR_CANNOTSENDTOCHAN(host, client, channel) (":" + host + " 404 " + client + " " + channel + " :Cannot send to channel")
# define RPL_PRIVMSG(sender_prefix, target, message) (":" + sender_prefix + " PRIVMSG " + target + " :" + message)

// QUIT
# define RPL_QUIT(user_prefix, reason) (":" + user_prefix + " QUIT :" + reason)
# define RPL_ERROR(host, client, message) (":" + host + " ERROR :" + message)

// TOPIC
# define RPL_NOTOPIC(host, client, channel) (":" + host + " 331 " + client + " " + channel + " :No topic is set")
# define RPL_TOPIC(host, client, channel, topic) (":" + host + " 332 " + client + " " + channel + " :" + topic)
# define RPL_TOPICWHOTIME(host, client, channel, setter, time) (":" + host + " 333 " + client + " " + channel + " " + setter + " " + time)
# define BROADCAST_TOPIC(client, channel, message) (":" + client->getPrefix() + " TOPIC " + channel->getName() + " :" + message);

// USER
# define ERR_NOTREGISTERED(host, client) (":" + host + " 451 " + client + ":You have not registered!")
# define ERR_ALREADYREGISTERED(host, nickname) (":" + host + " 462 " + nickname + " :You may not reregister!")
# define ERR_INVALIDUSERNAME(host, nickname, reason) (":" + host + " 432 " + nickname + " :Invalid username " + reason)
# define ERR_USERSDONTMATCH(host, client) (":" + host + " 502 " + client + " :Cannot change mode for other users")
# define ERR_UMODEUNKNOWNFLAG(host, client, flag) (":" + host + " 501 " + client + " :Unknown MODE flag " + flag)
# define RPL_UMODEIS(host, client, modes) (":" + host + " 221 " + client + " " + modes)

// USERHOST
# define RPL_USERHOST(host, client, info) (":" + host + " 302 " + client + " :" + info)

// WHOIS
# define RPL_WHOISUSER(host, client, nick, user, ip, realname) (":" + host + " 311 " + client + " " + nick + " " + user + " " + ip + " * :" + realname)
# define RPL_WHOISSERVER(host, client, nick, server, info) (":" + host + " 312 " + client + " " + nick + " " + server + " :" + info)
# define RPL_WHOISCHANNELS(host, client, nick, channels) (":" + host + " 319 " + client + " " + nick + " :" + channels)
# define RPL_WHOISOPERATOR(host, client, nick) (":" + host + " 313 " + client + " " + nick + " :is an IRC operator")
# define RPL_WHOISIDLE(host, client, nick, idle, signon) (":" + host + " 317 " + client + " " + nick + " " + idle + " " + signon + " :seconds idle, signon time")
# define RPL_ENDOFWHOIS(host, client, nick) (":" + host + " 318 " + client + " " + nick + " :End of WHOIS list")

#endif