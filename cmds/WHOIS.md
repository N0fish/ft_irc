3.6.2 Whois query

      Command: WHOIS
   Parameters: [ <target> ] <mask> *( "," <mask> )

   This command is used to query information about particular user.
   The server will answer this command with several numeric messages
   indicating different statuses of each user which matches the mask (if
   you are entitled to see them).  If no wildcard is present in the
   <mask>, any information about that nick which you are allowed to see
   is presented.

   If the <target> parameter is specified, it sends the query to a
   specific server.  It is useful if you want to know how long the user
   in question has been idle as only local server (i.e., the server the
   user is directly connected to) knows that information, while
   everything else is globally known.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
           RPL_WHOISUSER                 RPL_WHOISCHANNELS
           RPL_WHOISCHANNELS             RPL_WHOISSERVER
           RPL_AWAY                      RPL_WHOISOPERATOR
           RPL_WHOISIDLE                 ERR_NOSUCHNICK
           RPL_ENDOFWHOIS

   Examples:

   WHOIS wiz                       ; return available user information
                                   about nick WiZ

   WHOIS eff.org trillian          ; ask server eff.org for user
                                   information  about trillian
_____________________________________________________________________________________________________________________
3.6.2 Whois-запрос

      Команда WHOIS
   Используется для запроса информации о пользователе.

   Если в <mask> нет символов подстановки, сервер возвращает всю доступную информацию о пользователе.
   Если указан <target>, запрос отправляется на конкретный сервер (например, чтобы узнать время простоя).
   Сервер отвечает числовыми сообщениями, содержащими ник, хост, статус, список каналов, время входа и другие параметры.
   Если пользователь не найден, отправляется ошибка ERR_NOSUCHNICK.
   Запрос может содержать несколько масок, разделённых запятыми.

   Числовые ответы:

           RPL_WHOISUSER – информация о нике, имени пользователя и хосте.
           RPL_WHOISCHANNELS – список каналов, в которых состоит пользователь.
           RPL_WHOISSERVER – сервер, к которому подключён пользователь.
           RPL_WHOISIDLE – время простоя пользователя и время входа.
           RPL_WHOISOPERATOR – статус оператора, если применимо.
           ERR_NOSUCHNICK – ник не найден.
           ERR_NOSUCHSERVER – сервер не найден.
           RPL_ENDOFWHOIS – конец списка.

   Примеры:

   WHOIS wiz                       ; получить информацию о нике wiz.
   WHOIS eff.org trillian          ; запросить сервер eff.org о trillian.