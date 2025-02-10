3.4.10 Info command

      Command: INFO
   Parameters: [ <target> ]

   The INFO command is REQUIRED to return information describing the
   server: its version, when it was compiled, the patchlevel, when it
   was started, and any other miscellaneous information which may be
   considered to be relevant.

   Wildcards are allowed in the <target> parameter.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_INFO                      RPL_ENDOFINFO

   Examples:

   INFO csd.bu.edu                 ; request an INFO reply from
                                   csd.bu.edu

   INFO Angel                      ; request info from the server that
                                   Angel is connected to.

3.5 Service Query and Commands

   The service query group of commands has been designed to return
   information about any service which is connected to the network.

_____________________________________________________________________________________________________________________
3.4.10 Команда INFO

      Команда: INFO
   Параметры: [ <target> ] (необязательный параметр — целевой сервер или клиент)
Описание:
Команда INFO обязана возвращать информацию, описывающую сервер, включая:
   его версию,
   дату компиляции,
   уровень патча,
   время запуска,
   и любую другую информацию, которая может считаться полезной.

   Разрешены подстановочные знаки (wildcards) в параметре <target> (например, INFO *.example.com).

   Числовые ответы:

           402 ERR_NOSUCHSERVER (Если указанный сервер не существует)
           371 RPL_INFO (Основная информация)
           374 RPL_ENDOFINFO (Окончание списка информации)

   Примеры использования:

   INFO csd.bu.edu   ; запрашивает INFO с сервера csd.bu.edu
   INFO Angel        ; запрашивает INFO с сервера, к которому подключен Angel

3.5 Запрос и команды сервиса

   Группа команд запроса сервиса была разработана для возврата
   информации о любой службе, подключенной к сети.