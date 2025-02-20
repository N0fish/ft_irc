# ft_irc

## made using Internet Relay Chat: Client Protocol:

```
https://www.rfc-editor.org/rfc/rfc2812#section-3.6.2
```

## program launch :

```
make && ./ircserv 6667 1234
```

## error checking

```
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./ircserv 6667 1234
```

## another terminal

```
nc 127.0.0.1 6667
```

## irssi

```
/connect localhost 6667 1234
```
