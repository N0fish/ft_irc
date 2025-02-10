3.1.7 Quit

      Command: QUIT
   Parameters: [ <Quit Message> ]

   A client session is terminated with a quit message.  The server
   acknowledges this by sending an ERROR message to the client.

   Numeric Replies:

           None.

   Example:

   QUIT :Gone to have lunch        ; Preferred message format.

   :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
                                   syrk has quit IRC to have lunch.
_____________________________________________________________________________________________________________________
3.1.7 QUIT (Выход из сети)

      Команда: QUIT
   Параметры: [ <Quit Message> ] (необязательное сообщение о выходе)

   Команда QUIT используется для завершения сессии клиента.
   Сервер подтверждает выход, отправляя клиенту сообщение ERROR.

   Числовые ответы (Numeric Replies):

           Нет специальных ответов (Numeric Replies) для этой команды.

   Примеры использования:

   QUIT :Gone to have lunch        ; Клиент отключается с сообщением "Gone to have lunch".
                                   Сервер уведомляет других пользователей о выходе:

   :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch  ; Пользователь 
                                                        syrk вышел из сети с указанным сообщением.