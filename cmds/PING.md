3.7.2 Ping message

      Command: PING
   Parameters: <server1> [ <server2> ]

   The PING command is used to test the presence of an active client or
   server at the other end of the connection.  Servers send a PING
   message at regular intervals if no other activity detected coming
   from a connection.  If a connection fails to respond to a PING
   message within a set amount of time, that connection is closed.  A
   PING message MAY be sent even if the connection is active.

   When a PING message is received, the appropriate PONG message MUST be
   sent as reply to <server1> (server which sent the PING message out)
   as soon as possible.  If the <server2> parameter is specified, it
   represents the target of the ping, and the message gets forwarded
   there.

   Numeric Replies:

           ERR_NOORIGIN                  ERR_NOSUCHSERVER

   Examples:

   PING tolsun.oulu.fi             ; Command to send a PING message to
                                   server

   PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
                                   message to server "tolsun.oulu.fi"

   PING :irc.funet.fi              ; Ping message sent by server
                                   "irc.funet.fi"
_____________________________________________________________________________________________________________________
3.7.2 Команда PING

      Команда: PING
   Параметры: <server1> [ <server2> ]

   Команда PING используется для проверки наличия активного клиента или сервера на другом конце соединения. Серверы отправляют PING через регулярные промежутки времени, если не обнаруживают другой активности от соединения. Если соединение не отвечает на PING в течение заданного времени, оно закрывается.

   PING может быть отправлен даже при активном соединении.

   Когда сервер получает PING, он обязан ответить PONG, отправив его обратно на <server1> (сервер, который отправил PING). Если указан параметр <server2>, то PING перенаправляется на этот сервер.

   Числовые ответы (Numeric Replies)

           ERR_NOORIGIN (409) — Не указан источник запроса.
           ERR_NOSUCHSERVER (402) — Указанного сервера не существует.

   Примеры

   PING tolsun.oulu.fi       ; Клиент отправляет PING на сервер tolsun.oulu.fi
   PING WiZ tolsun.oulu.fi   ; Клиент WiZ отправляет PING на сервер tolsun.oulu.fi
   PING :irc.funet.fi        ; Сервер отправляет PING серверу irc.funet.fi