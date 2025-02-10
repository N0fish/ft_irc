3.2.6 List message

      Command: LIST
   Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

   The list command is used to list channels and their topics.  If the
   <channel> parameter is used, only the status of that channel is
   displayed.

   If the <target> parameter is specified, the request is forwarded to
   that server which will generate the reply.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
           RPL_LIST                        RPL_LISTEND

   Examples:

   LIST                            ; Command to list all channels.

   LIST #twilight_zone,#42         ; Command to list channels
                                   #twilight_zone and #42
_____________________________________________________________________________________________________________________
3.2.6 Список сообщений

      Команда: LIST
   Параметры: [ <channel> *( "," <channel> ) [ <target> ] ]

   Команда LIST используется для отображения списка каналов и их тем.
   Если параметр <channel> указан, выводится только статус этого канала.

   Если указан параметр <target>, запрос пересылается на тот сервер, который должен сформировать ответ.

   В параметре <target> разрешены подстановочные знаки (wildcards).

   Числовые ответы (replies):

           ERR_TOOMANYMATCHES (ERR 416) – Слишком много совпадений.
           ERR_NOSUCHSERVER (ERR 402) – Указанного сервера не существует.
           RPL_LIST (RPL 322) – Информация о канале.
           RPL_LISTEND (RPL 323) – Окончание списка каналов.

   Примеры:

   LIST                            ; Команда для получения списка всех каналов.

   LIST #twilight_zone,#42         ; Команда для получения списка каналов
                                   #twilight_zone и #42.