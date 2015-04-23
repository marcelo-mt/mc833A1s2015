all: tcpclient tcpserver

tcpserver: movie.c movie_rental.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpsrv.c
	gcc movie.c movie_rental.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpsrv.c -o tcpserver

tcpclient: movie.c movie_rental.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpcli.c
	gcc movie.c movie_rental.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c str_cli.c str_echo.c movietcpcli.c -o tcpclient

clean:
	rm tcpclient tcpserver

