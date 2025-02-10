3.2.2 Part message

      Command: PART
   Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

   The PART command causes the user sending the message to be removed
   from the list of active members for all given channels listed in the
   parameter string.  If a "Part Message" is given, this will be sent
   instead of the default message, the nickname.  This request is always
   granted by the server.

   Servers MUST be able to parse arguments in the form of a list of
   target, but SHOULD NOT use lists when sending PART messages to
   clients.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_NOTONCHANNEL

   Examples:

   PART #twilight_zone             ; Command to leave channel
                                   "#twilight_zone"

   PART #oz-ops,&group5            ; Command to leave both channels
                                   "&group5" and "#oz-ops".

   :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
                                   ; User WiZ leaving channel
                                   "#playzone" with the message "I
                                   lost".
_____________________________________________________________________________________________________________________
3.2.2 Частичное сообщение

      Команда: PART
   Параметры: <канал> *( "," <канал> ) [ <сообщение о выходе> ]

   Команда PART позволяет пользователю покинуть указанные каналы.
   Если передано "Сообщение о выходе", оно отправляется участникам канала вместо стандартного сообщения, содержащего никнейм.

   Сервер должен уметь разбирать аргументы в виде списка каналов, но не должен использовать списки при отправке PART сообщений клиентам.

   Числовые ответы:

           ERR_NEEDMOREPARAMS – недостаточно параметров
           ERR_NOSUCHCHANNEL – канал не существует
           ERR_NOTONCHANNEL – пользователь не находится в канале

   Примеры:

   PART #twilight_zone               ; Пользователь покидает канал #twilight_zone

   PART #oz-ops,&group5              ; Пользователь покидает каналы #oz-ops и &group5

   :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost  
                                     ; WiZ покидает #playzone с сообщением "I lost"

