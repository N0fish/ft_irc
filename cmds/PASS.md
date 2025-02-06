3.1.1 Password message

      Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   optional password can and MUST be set before any attempt to register
   the connection is made.  Currently this requires that user send a
   PASS command before sending the NICK/USER combination.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere
_____________________________________________________________________________________________________________________
3.1.1 Сообщение пароля

      Команда: PASS
   Параметры: <пароль>

   Команда PASS используется для установки "пароля соединения".
   Пароль должен быть установлен до попытки регистрации соединения.
   Это означает, что перед отправкой комбинации NICK и USER клиент обязан отправить команду PASS.

   Числовые ответы:

           ERR_NEEDMOREPARAMS – недостаточно параметров
           ERR_ALREADYREGISTRED – повторная регистрация невозможна

   Пример:

           PASS secretpasswordhere  ; Установка пароля "secretpasswordhere"