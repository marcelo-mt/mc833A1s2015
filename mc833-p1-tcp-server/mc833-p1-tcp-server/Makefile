SRC_DIR=.

all: tcpclient tcpserver

tcpserver: movie.c movie_rental.c movie_rental_server.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpserver.c
	gcc movie.c movie_rental.c movie_rental_server.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpserver.c -o tcpserver

tcpclient: movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpclient.c
	gcc movie.c movie_rental.c movie_rental_client.c error.c signal.c sigchldwaitpid.c wrapunix.c wrapsock.c readn.c writen.c readline.c wraplib.c wrapstdio.c tcpclient.c -o tcpclient

clean:
	-rm -f $(SRC_DIR)/*.o *.o tcpclient tcpserver

