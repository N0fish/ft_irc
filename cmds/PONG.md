3.7.3 Pong message

      Command: PONG
   Parameters: <server> [ <server2> ]

   PONG message is a reply to ping message.  If parameter <server2> is
   given, this message MUST be forwarded to given target.  The <server>
   parameter is the name of the entity who has responded to PING message
   and generated this message.

   Numeric Replies:

           ERR_NOORIGIN                  ERR_NOSUCHSERVER

   Example:

   PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
                                   tolsun.oulu.fi
_____________________________________________________________________________________________________________________
3.7.3 Команда PONG

      Команда: PONG
   Параметры: <server> [ <server2> ]

   Сообщение PONG является ответом на сообщение PING. Если передан параметр <server2>, 
   то сообщение PONG обязательно должно быть переслано указанному целевому серверу.

   Параметр <server> указывает имя объекта, который ответил на PING и сгенерировал это сообщение.

   Числовые ответы (Numeric Replies)
           ERR_NOORIGIN (409) — Не указан источник запроса.
           ERR_NOSUCHSERVER (402) — Указанного сервера не существует.

   Пример

PONG csd.bu.edu tolsun.oulu.fi  ; Сервер csd.bu.edu отвечает PONG серверу tolsun.oulu.fi