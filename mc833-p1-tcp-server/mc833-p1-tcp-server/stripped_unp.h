//
//  stripped_unp.h
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/23/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#ifndef mc833_p1_tcp_server_stripped_unp_h
#define mc833_p1_tcp_server_stripped_unp_h

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */


/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
 kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	MAXSOCKADDR  128	/* max socket address structure size */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* Define some port number that can be used for client-servers */
#define	SERV_PORT		 9878			/* TCP and UDP client-servers */
#define	SERV_PORT_STR	"9878"			/* TCP and UDP client-servers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

/* Following shortens all the type casts of pointer arguments */
#define	SA	struct sockaddr

void	 str_echo(int);
void	 str_cli(FILE *, int);


/* arpa inet wrappers */
const char		*Inet_ntop(int, const void *, char *, size_t);
void			Inet_pton(int, const char *, void *);

/* Signal Handling and Wrapper */
typedef	void	Sigfunc(int);
//Sigfunc         *signal_intr(int, Sigfunc *);
Sigfunc         *Signal(int, Sigfunc *);
//Sigfunc         *Signal_intr(int, Sigfunc *);

/* prototypes for our Unix wrapper functions: see {Sec errors} */
void	 Close(int);
pid_t	 Fork(void);
//void	*Malloc(size_t);
//int		 Open(const char *, int, mode_t);
//void	 Pipe(int *fds);
//ssize_t	 Read(int, void *, size_t);
pid_t	 Waitpid(pid_t, int *, int);
//void	 Write(int, void *, size_t);

/* prototypes for our stdio wrapper functions: see {Sec errors} */
//void	 Fclose(FILE *);
//FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
//FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);

/* prototypes for our socket wrapper functions: see {Sec errors} */
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
//void	 Getpeername(int, SA *, socklen_t *);
//void	 Getsockname(int, SA *, socklen_t *);
//void	 Getsockopt(int, int, int, void *, socklen_t *);
void	 Listen(int, int);
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
ssize_t	 Recv(int, void *, size_t, int);
//ssize_t	 Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
//ssize_t	 Recvmsg(int, struct msghdr *, int);
//void	 Send(int, const void *, size_t, int);
//void	 Sendto(int, const void *, size_t, int, const SA *, socklen_t);
//void	 Sendmsg(int, const struct msghdr *, int);
//void	 Setsockopt(int, int, int, const void *, socklen_t);
//int		 Sockatmark(int);
int		 Socket(int, int, int);
//void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);


/* prototypes for our error functions */
void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#endif
