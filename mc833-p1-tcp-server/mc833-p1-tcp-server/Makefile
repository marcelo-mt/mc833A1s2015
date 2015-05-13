SRC_DIR=.

all: tcp udp

tcp: tcpclient tcpserver

udp: udpclient udpserver

tcpserver: movie.c movie_rental.c movie_rental_server.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpserver.c
	gcc movie.c movie_rental.c movie_rental_server.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpserver.c -o tcpserver

tcpclient: movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpclient.c
	gcc movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpclient.c -o tcpclient

udpserver: movie.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c udp_movie_rental.c udpserver.c
	gcc movie.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c udp_movie_rental.c udpserver.c -o udpserver

udpclient: movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c udpclient.c
	gcc movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c udpclient.c -o udpclient

clean:
	-rm -f $(SRC_DIR)/*.o *.o tcpclient tcpserver udpclient udpserver

