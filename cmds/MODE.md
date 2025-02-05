3.2.3 Channel mode message

      Command: MODE
   Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

   The MODE command is provided so that users may query and change the
   characteristics of a channel.  For more details on available modes
   and their uses, see "Internet Relay Chat: Channel Management" [IRC-
   CHAN].  Note that there is a maximum limit of three (3) changes per
   command for modes that take a parameter.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_KEYSET
           ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
           ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
           RPL_CHANNELMODEIS
           RPL_BANLIST                     RPL_ENDOFBANLIST
           RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
           RPL_INVITELIST                  RPL_ENDOFINVITELIST
           RPL_UNIQOPIS

   The following examples are given to help understanding the syntax of
   the MODE command, but refer to modes defined in "Internet Relay Chat:
   Channel Management" [IRC-CHAN].

   Examples:

   MODE #Finnish +imI *!*@*.fi     ; Command to make #Finnish channel
                                   moderated and 'invite-only' with user
                                   with a hostname matching *.fi
                                   automatically invited.

   MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
                                   to Kilroy on channel #Finnish.

   MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
                                   #Finnish.

   MODE #Fins -s                   ; Command to remove 'secret' flag
                                   from channel #Fins.

   MODE #42 +k oulu                ; Command to set the channel key to
                                   "oulu".

   MODE #42 -k oulu                ; Command to remove the "oulu"
                                   channel key on channel "#42".

   MODE #eu-opers +l 10            ; Command to set the limit for the
                                   number of users on channel
                                   "#eu-opers" to 10.

   :WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
                                   ; User "WiZ" removing the limit for
                                   the number of users on channel "#eu-
                                   opers".

   MODE &oulu +b                   ; Command to list ban masks set for
                                   the channel "&oulu".

   MODE &oulu +b *!*@*             ; Command to prevent all users from
                                   joining.

   MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
                                   ; Command to prevent any user from a
                                   hostname matching *.edu from joining,
                                   except if matching *.bu.edu

   MODE #bu +be *!*@*.edu *!*@*.bu.edu
                                   ; Comment to prevent any user from a
                                   hostname matching *.edu from joining,
                                   except if matching *.bu.edu

   MODE #meditation e              ; Command to list exception masks set
                                   for the channel "#meditation".

   MODE #meditation I              ; Command to list invitations masks
                                   set for the channel "#meditation".

   MODE !12345ircd O               ; Command to ask who the channel
                                   creator for "!12345ircd" is
_____________________________________________________________________________________________________________________
3.2.3 Сообщение о режиме канала

      Команда: MODE
   Параметры: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

   Команда MODE используется для запроса и изменения характеристик канала.
   Для подробной информации о доступных режимах и их применении см. "Internet Relay Chat: Channel Management" [IRC-CHAN].
   Обратите внимание, что максимальное количество изменений за одну команду составляет три (3), если режим требует параметра.

   Числовые ответы сервера (Numeric Replies):

           ERR_NEEDMOREPARAMS – недостаточно параметров.
           ERR_KEYSET – ключ уже установлен.
           ERR_NOCHANMODES – у канала нет режимов.
           ERR_CHANOPRIVSNEEDED – недостаточно прав для изменения режима.
           ERR_USERNOTINCHANNEL – пользователь не находится в указанном канале.
           ERR_UNKNOWNMODE – неизвестный режим.
           RPL_CHANNELMODEIS – отображение текущих режимов канала.
           RPL_BANLIST / RPL_ENDOFBANLIST – список заблокированных пользователей.
           RPL_EXCEPTLIST / RPL_ENDOFEXCEPTLIST – список исключений.
           RPL_INVITELIST / RPL_ENDOFINVITELIST – список приглашений.
           RPL_UNIQOPIS – информация об уникальном операторе канала.

   Примеры использования команды MODE

   MODE #Finnish +imI *!*@*.fi     ; Устанавливает режимы "модерируемый" (+m) 
   								   и "только по приглашению" (+i) для канала #Finnish,
								   а также автоматически приглашает пользователей с хостом,
								   соответствующим *.fi.

   MODE #Finnish +o Kilroy         ; Назначает пользователя Kilroy оператором канала #Finnish.

   MODE #Finnish +v Wiz            ; Позволяет пользователю WiZ говорить в канале #Finnish 
   								   (режим +v – voice).

   MODE #Fins -s                   ; Удаляет флаг "секретный" (-s) у канала #Fins.

   MODE #42 +k oulu                ; Устанавливает пароль oulu на канал #42.

   MODE #42 -k oulu                ; Удаляет пароль oulu с канала #42.

   MODE #eu-opers +l 10            ; Устанавливает лимит пользователей в канале #eu-opers на 10.

   :WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
                                   ; Пользователь WiZ снимает ограничение на количество пользователей в канале #eu-opers.

   MODE &oulu +b                   ; Выводит список масок блокировок (банов) для канала &oulu.

   MODE &oulu +b *!*@*
                                   ; Запрещает всем пользователям заходить в канал &oulu.

   MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
                                   ; Блокирует всех пользователей с доменом *.edu, кроме тех, кто из *.bu.edu.

   MODE #meditation e              ; Выводит список исключений (exception masks) для канала #meditation.

   MODE #meditation I              ; Выводит список масок приглашений (invite masks) для 
                                   канала #meditation.

   MODE !12345ircd O               ; Запрашивает информацию о создателе канала !12345ircd.