all: tcpclient tcpserver

tcpserver: error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpsrv.c
	gcc error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpsrv.c -o tcpserver

tcpclient: error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpcli.c
	gcc error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpcli.c -o tcpclient

clean:
	rm tcpclient tcpserver

