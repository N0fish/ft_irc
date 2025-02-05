3.2.7 Invite message

      Command: INVITE
   Parameters: <nickname> <channel>

   The INVITE command is used to invite a user to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  However, if the channel exists, only members of the channel
   are allowed to invite other users.  When the channel has invite-only
   flag set, only channel operators may issue INVITE command.

   Only the user inviting and the user being invited will receive
   notification of the invitation.  Other channel members are not
   notified.  (This is unlike the MODE changes, and is occasionally the
   source of trouble for users.)

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITING                    RPL_AWAY

   Examples:

   :Angel!wings@irc.org INVITE Wiz #Dust

                                   ; Message to WiZ when he has been
                                   invited by user Angel to channel
                                   #Dust

   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
                                   #Twilight_zone

_____________________________________________________________________________________________________________________
3.2.7 Пригласительное сообщение

      Команда: INVITE
   Параметры: <nickname> <channel>

   Команда INVITE используется для приглашения пользователя в канал.
   Параметр <nickname> — это никнейм пользователя, которого приглашают в целевой канал <channel>.
   Нет требования, чтобы канал, в который приглашают пользователя, уже существовал или был валидным каналом.
   Однако, если канал существует, только его участники имеют право приглашать других пользователей.
   Если на канале установлен режим invite-only (+i), то отправлять INVITE могут только операторы канала.

   ❗ Только приглашающий и приглашаемый получают уведомление о приглашении.
   Другие участники не получают уведомления.
   (Это отличие от изменений MODE, из-за чего пользователи иногда сталкиваются с неудобствами.)

   Числовые ответы (replies)

           ERR_NEEDMOREPARAMS (461) – Не хватает параметров.
           ERR_NOSUCHNICK (401) – Такого ника нет.
           ERR_NOTONCHANNEL (442) – Вы не на этом канале.
           ERR_USERONCHANNEL (443) – Пользователь уже на канале.
           ERR_CHANOPRIVSNEEDED (482) – У вас нет прав для приглашения.
           RPL_INVITING (341) – Приглашение отправлено.
           RPL_AWAY (301) – Пользователь в AWAY-режиме.

   Примеры

   :Angel!wings@irc.org INVITE Wiz #Dust

                                   ; Сообщение для Wiz: пользователь 
								   Angel пригласил его в канал 
								   #Dust.

   INVITE Wiz #Twilight_Zone       ; Команда для приглашения Wiz в 
                                   #Twilight_Zone.