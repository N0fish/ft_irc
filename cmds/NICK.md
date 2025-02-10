3.1.2 Nick message


      Command: NICK
   Parameters: <nickname>

   NICK command is used to give user a nickname or change the existing
   one.

   Numeric Replies:

           ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED

   Examples:

   NICK Wiz                ; Introducing new nick "Wiz" if session is
                           still unregistered, or user changing his
                           nickname to "Wiz"

   :WiZ!jto@tolsun.oulu.fi NICK Kilroy
                           ; Server telling that WiZ changed his
                           nickname to Kilroy.
_____________________________________________________________________________________________________________________
3.1.2 Ник сообщение

      Команда: NICK
   Параметры: <nickname>

   Команда NICK используется для задания пользователем ника или изменения уже существующего ника.

   Числовые ответы (Numeric Replies):

           ERR_NONICKNAMEGIVEN — Никнейм не был указан.
           ERR_ERRONEUSNICKNAME — Ошибочный никнейм.
           ERR_NICKNAMEINUSE — Ник уже используется.
           ERR_NICKCOLLISION — Конфликт никнеймов.
           ERR_UNAVAILRESOURCE — Ресурс недоступен.
           ERR_RESTRICTED — Ограничения на смену ника.

   Примеры:

   NICK Wiz                ; Представление нового ника Wiz, 
   						   если сессия еще не зарегистрирована,
						   или пользователь меняет свой ник на Wiz.


   :WiZ!jto@tolsun.oulu.fi NICK Kilroy
                           ; Сервер сообщает, что WiZ 
						   изменил ник на Kilroy.