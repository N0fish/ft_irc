3.2.1 Join message

      Command: JOIN
   Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
               / "0"

   The JOIN command is used by a user to request to start listening to
   the specific channel.  Servers MUST be able to parse arguments in the
   form of a list of target, but SHOULD NOT use lists when sending JOIN
   messages to clients.

   Once a user has joined a channel, he receives information about
   all commands his server receives affecting the channel.  This
   includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
   This allows channel members to keep track of the other channel
   members, as well as channel modes.

   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

   Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
           RPL_TOPIC

   Examples:

   JOIN #foobar                    ; Command to join channel #foobar.

   JOIN &foo fubar                 ; Command to join channel &foo using
                                   key "fubar".

   JOIN #foo,&bar fubar            ; Command to join channel #foo using
                                   key "fubar" and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
                                   key "fubar", and channel #bar using
                                   key "foobar".

   JOIN #foo,#bar                  ; Command to join channels #foo and
                                   #bar.

   JOIN 0                          ; Leave all currently joined
                                   channels.

   :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
                                   on channel #Twilight_zone
_____________________________________________________________________________________________________________________
3.2.1 Сообщение о присоединении (JOIN)

      Команда: JOIN
   Параметры: (<channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
               / "0"

   Команда JOIN используется пользователем для запроса на присоединение к конкретному каналу. Серверы ДОЛЖНЫ уметь разбирать аргументы в виде списка каналов, но НЕ ДОЛЖНЫ отправлять JOIN сообщения клиентам в виде списка.

   Как только пользователь присоединился к каналу, он получает информацию о всех командах, поступающих на сервер, которые влияют на этот канал.
   Это включает команды:

   JOIN, MODE, KICK, PART, QUIT
   А также PRIVMSG и NOTICE.
   Благодаря этому участники канала могут отслеживать других пользователей и узнавать об изменениях режимов канала.

   ✅ Если JOIN прошёл успешно, пользователь получает подтверждение в виде JOIN-сообщения.
   ✅ Затем ему отправляется тема канала (RPL_TOPIC 332) и список пользователей (RPL_NAMREPLY 353), включая самого себя.

   ⚠ Особый случай:
   Если передано значение "0", то пользователь покидает все каналы, в которых он состоит.
   Сервер обрабатывает этот запрос так, как если бы пользователь отправил PART для каждого канала.

   Числовые коды ответов:
           ERR_NEEDMOREPARAMS (461) – Не хватает параметров.
           ERR_BANNEDFROMCHAN (474) – Вы забанены на этом канале.
           ERR_INVITEONLYCHAN (473) – Нельзя войти без приглашения.
           ERR_BADCHANNELKEY (475) – Неверный пароль канала.
           ERR_CHANNELISFULL (471) – Канал заполнен.
           ERR_BADCHANMASK (476) – Недопустимое имя канала.
           ERR_NOSUCHCHANNEL (403) – Такого канала нет.
           ERR_TOOMANYCHANNELS (405) – Превышено максимальное количество каналов.
           ERR_TOOMANYTARGETS (407) – Слишком много получателей.
           ERR_UNAVAILRESOURCE (437) – Ресурс недоступен.
           RPL_TOPIC (332) – Тема канала.

   JOIN #foobar                    ; Присоединиться к каналу `#foobar`.
   JOIN &foo fubar                 ; Присоединиться к `&foo` с паролем `fubar`.
   JOIN #foo,&bar fubar            ; `#foo` с паролем `fubar`, `&bar` без пароля.
   JOIN #foo,#bar fubar,foobar     ; `#foo` с паролем `fubar`, `#bar` с `foobar`.
   JOIN #foo,#bar                  ; Присоединиться к `#foo` и `#bar`.
   JOIN 0                          ; Покинуть все каналы.

   :WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; Пользователь `WiZ`
                                   зашёл на `#Twilight_zone`.


Не из мануала:

При успешном входе клиент получает:
- Подтверждающее сообщение JOIN.
- Тему канала (если установлена) – RPL_TOPIC.
- Список пользователей в канале – RPL_NAMREPLY.

Типы каналов:
- `#` (глобальный) – виден во всей сети серверов.
- `&` (локальный) – виден только на текущем сервере.
- `+` (временный локальный) – исчезает, когда последний участник покидает канал.
- `!` (уникальный глобальный) – требует уникального имени.

Ограничения доступа:
- Если канал требует ключ (+k) и передан неверный ключ, пользователь отклоняется (ERR_BADCHANNELKEY).
- Если канал работает в режиме "только по приглашению" (+i) и пользователь не приглашён, он отклоняется (ERR_INVITEONLYCHAN).
- Если пользователь заблокирован (+b), он отклоняется (ERR_BANNEDFROMCHAN).
- Если канал достиг предела пользователей (+l), вход отклоняется (ERR_CHANNELISFULL).

Числовые ответы:
- `RPL_TOPIC` (332) – Отправляется, если у канала есть тема.
- `RPL_NAMREPLY` (353) – Отправляется со списком пользователей.
- `ERR_NOSUCHCHANNEL` (403) – Отправляется, если канал нельзя создать.
- `ERR_BADCHANNELKEY` (475) – Отправляется, если передан неправильный ключ.
- `ERR_BANNEDFROMCHAN` (474) – Отправляется, если пользователь заблокирован.
- `ERR_INVITEONLYCHAN` (473) – Отправляется, если требуется приглашение.
- `ERR_CHANNELISFULL` (471) – Отправляется, если канал заполнен.
*/