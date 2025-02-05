3.2.8 Kick command

      Command: KICK
   Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]

   The KICK command can be used to request the forced removal of a user
   from a channel.  It causes the <user> to PART from the <channel> by
   force.  For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.

   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

   Examples:

   KICK &Melbourne Matthew         ; Command to kick Matthew from
                                   &Melbourne

   KICK #Finnish John :Speaking English
                                   ; Command to kick John from #Finnish
                                   using "Speaking English" as the
                                   reason (comment).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; KICK message on channel #Finnish
                                   from WiZ to remove John from channel

3.3 Sending messages

   The main purpose of the IRC protocol is to provide a base for clients
   to communicate with each other.  PRIVMSG, NOTICE and SQUERY
   (described in Section 3.5 on Service Query and Commands) are the only
   messages available which actually perform delivery of a text message
   from one client to another - the rest just make it possible and try
   to ensure it happens in a reliable and structured manner.
_____________________________________________________________________________________________________________________
3.2.8 Команда KICK

      Команда: KICK
   Параметры: <канал> *( "," <канал> ) <пользователь> *( "," <пользователь> )
               [<комментарий>]

   Команда KICK используется для принудительного удаления пользователя из канала.
   Она заставляет <пользователя> выйти из <канала> силой.

   Для того чтобы команда была синтаксически правильной, ДОЛЖНО быть либо:

   Один параметр канала и несколько пользователей,
   Либо столько же каналов, сколько пользователей.
   Если предоставлен "комментарий", он будет отправлен вместо стандартного сообщения,
   которое по умолчанию содержит никнейм пользователя, выполняющего KICK.

   Сервер НЕ ДОЛЖЕН отправлять клиентам KICK-сообщения с несколькими каналами или пользователями.
   Это необходимо для сохранения обратной совместимости со старыми клиентами.

   Числовые ответы (Numeric Replies):

           ERR_NEEDMOREPARAMS (461)	Недостаточно параметров.
           ERR_NOSUCHCHANNEL (403)	Канал не существует.
           ERR_BADCHANMASK (476)	Некорректное имя канала.
           ERR_CHANOPRIVSNEEDED (482)	Вы не оператор канала.
           ERR_USERNOTINCHANNEL (441)	Пользователь не в канале.
           ERR_NOTONCHANNEL (442)	Вы не на этом канале.

   Примеры:

   KICK &Melbourne Matthew         ; Команда для исключения пользователя Matthew из канала
                                   &Melbourne.

   KICK #Finnish John :Speaking English
                                   ; Команда для исключения пользователя John из #Finnish
								   с причиной "Speaking English".

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; Сообщение KICK от пользователя WiZ,
								   который кикнул John из #Finnish.