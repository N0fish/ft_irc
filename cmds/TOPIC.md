3.2.4 Topic message

      Command: TOPIC
   Parameters: <channel> [ <topic> ]

   The TOPIC command is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if this action is allowed for the user
   requesting it.  If the <topic> parameter is an empty string, the
   topic for that channel will be removed.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED            ERR_NOCHANMODES

   Examples:

   :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
                                   topic.

   TOPIC #test :another topic      ; Command to set the topic on #test
                                   to "another topic".

   TOPIC #test :                   ; Command to clear the topic on
                                   #test.

   TOPIC #test                     ; Command to check the topic for
                                   #test.
_____________________________________________________________________________________________________________________
3.2.4 Тема сообщения

      Команда: TOPIC
   Параметры: <channel> [ <topic> ]

   Команда TOPIC используется для изменения или просмотра темы канала.
   Если параметр <topic> не указан, сервер отправляет текущую тему канала <channel>.
   Если параметр <topic> присутствует, тема канала изменится, если у пользователя есть права.
   Если <topic> — пустая строка, то тема канала будет удалена.

   Числовые ответы:

           461 (ERR_NEEDMOREPARAMS) – Не хватает параметров
           403 (ERR_NOSUCHCHANNEL) – Такого канала не существует
           442 (ERR_NOTONCHANNEL) – Вы не состоите в этом канале
           331 (RPL_NOTOPIC) – На канале нет темы
           332 (RPL_TOPIC) – Текущая тема канала
           333 (RPL_TOPICWHOTIME) – Информация о том, кто и когда установил тему
           482 (ERR_CHANOPRIVSNEEDED) – Недостаточно прав для изменения темы
           477 (ERR_NOCHANMODES) – Канал не поддерживает режимы

   Примеры использования:

   TOPIC #general :Добро пожаловать!   ; Установить тему "Добро пожаловать!"
   TOPIC #general                      ; Запросить текущую тему канала
   TOPIC #general :                    ; Удалить тему канала