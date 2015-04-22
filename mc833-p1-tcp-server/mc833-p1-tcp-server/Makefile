all: tcpclient tcpserver

tcpserver: error.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c movietcpsrv.c
	gcc error.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c movietcpsrv.c -o tcpserver

tcpclient: error.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c movietcpcli.c
	gcc error.c wrapunix.c wrapsock.c inet_aton.c inet_ntop_ipv4.c inet_pton_ipv4.c readn.c writen.c readline.c wraplib.c movietcpcli.c -o tcpclient

clean:
	rm tcpclient tcpserver

