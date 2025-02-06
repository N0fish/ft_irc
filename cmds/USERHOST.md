4.8 Userhost message

      Command: USERHOST
   Parameters: <nickname> *( SPACE <nickname> )

   The USERHOST command takes a list of up to 5 nicknames, each
   separated by a space character and returns a list of information
   about each nickname that it found.  The returned list has each reply
   separated by a space.

   Numeric Replies:

           RPL_USERHOST                  ERR_NEEDMOREPARAMS

   Example:

   USERHOST Wiz Michael syrk       ; USERHOST request for information on
                                   nicks "Wiz", "Michael", and "syrk"

   :ircd.stealth.net 302 yournick :syrk=+syrk@millennium.stealth.net
                                   ; Reply for user syrk
_____________________________________________________________________________________________________________________
4.8 Сообщение USERHOST

      Команда: USERHOST
   Параметры: <nickname> *( SPACE <nickname> )

   Команда USERHOST принимает список до 5 никнеймов, разделённых пробелами, и возвращает информацию о каждом найденном никнейме. Ответ содержит список, в котором информация о каждом пользователе разделена пробелом.

   Числовые ответы (Numeric Replies):

           RPL_USERHOST (302) – успешный ответ с информацией.
           ERR_NEEDMOREPARAMS (461) – ошибка при недостатке параметров.

   Пример:

   USERHOST Wiz Michael syrk       ; Запрос информации о пользователях Wiz, Michael и syrk.

   :ircd.stealth.net 302 yournick :syrk=+syrk@millennium.stealth.net
                                   ; Ответ содержит информацию о пользователе syrk.