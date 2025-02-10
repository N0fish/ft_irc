3.1.3 User message

      Command: USER
   Parameters: <user> <mode> <unused> <realname>

   The USER command is used at the beginning of connection to specify
   the username, hostname and realname of a new user.

   The <mode> parameter should be a numeric, and can be used to
   automatically set user modes when registering with the server.  This
   parameter is a bitmask, with only 2 bits having any signification: if
   the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
   set, the user mode 'i' will be set.  (See Section 3.1.5 "User
   Modes").

   The <realname> may contain space characters.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

   USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan", and asking to be set
                                   invisible.
_____________________________________________________________________________________________________________________
3.1.3 Сообщение пользователя
      Команда: USER
   Parameters: <user> <mode> <unused> <realname>

   Используется для регистрации нового клиента на сервере IRC. Согласно протоколу, команда принимает следующие параметры:

   <user> — имя пользователя.
   <mode> — числовое значение, которое задает начальные пользовательские режимы (w для wallops, i для invisibility).
   <unused> — параметр, который не используется, но его необходимо передавать.
   <realname> — реальное имя пользователя, может содержать пробелы.

   Обработки ошибок

           ERR_NEEDMOREPARAMS (461) — если передано недостаточно параметров.
           ERR_ALREADYREGISTRED (462) — если пользователь уже зарегистрирован.

   Пример использования

   USER guest 0 * :Ronnie Reagan   ; Регистрирует пользователя guest 
   								   с реальным именем Ronnie Reagan.