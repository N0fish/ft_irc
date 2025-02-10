# ft_irc_3fill

```
https://www.rfc-editor.org/rfc/rfc2812#section-3.6.2
```

## make && :

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
