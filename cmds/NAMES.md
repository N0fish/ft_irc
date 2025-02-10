3.2.5 Names message

      Command: NAMES
   Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

   By using the NAMES command, a user can list all nicknames that are
   visible to him. For more details on what is visible and what is not,
   see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
   <channel> parameter specifies which channel(s) to return information
   about.  There is no error reply for bad channel names.

   If no <channel> parameter is given, a list of all channels and their
   occupants is returned.  At the end of this list, a list of users who
   are visible but either not on any channel or not on a visible channel
   are listed as being on `channel' "*".

   If the <target> parameter is specified, the request is forwarded to
   that server which will generate the reply.

   Wildcards are allowed in the <target> parameter.

   Numerics:

           ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
           RPL_NAMREPLY                    RPL_ENDOFNAMES

   Examples:

   NAMES #twilight_zone,#42        ; Command to list visible users on
                                   #twilight_zone and #42

   NAMES                           ; Command to list all visible
                                   channels and users
_____________________________________________________________________________________________________________________
3.2.5 ИМЕНА

      Команда: NAMES
   Параметры: [ <channel> *( "," <channel> ) [ <target> ] ]

   С помощью команды NAMES пользователь может получить список всех видимых ему никнеймов. Для получения информации о том, какие никнеймы видимы, см. "Internet Relay Chat: Channel Management" [IRC-CHAN].

   Параметр <channel> указывает, для каких каналов нужно вывести список участников.
   Если параметр <channel> не указан, сервер вернет список всех каналов и их участников.
   В конце списка будут указаны пользователи, которые видимы, но не находятся ни на одном канале или находятся на невидимом канале, помеченные как *.
   Если указан параметр <target>, запрос будет переслан на сервер-адресат, который отправит ответ.

   В <target> разрешены подстановочные символы (wildcards).

   Коды ответов:

           ERR_TOOMANYMATCHES - слишком много совпадений.
           ERR_NOSUCHSERVER - сервер не найден.
           RPL_NAMREPLY - список участников канала.
           RPL_ENDOFNAMES - конец списка участников.

   Примеры:

   NAMES #twilight_zone,#42        ; Команда для получения списка видимых пользователей на каналах
                                   #twilight_zone и #42
   NAMES                           ; Команда для получения списка всех видимых каналов и их участников