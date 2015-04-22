all: tcpclient tcpserver

tcpserver: error.c wrapunix.c wrapsock.c movietcpsrv.c
	gcc error.c wrapunix.c wrapsock.c movietcpsrv.c -o tcpserver

tcpclient: error.c wrapunix.c wrapsock.c movietcpcli.c
	gcc error.c wrapunix.c wrapsock.c movietcpcli.c -o tcpclient

clean:
	rm tcpclient tcpserver

