#include "stripped_unp.h"
#include "movie_rental_header.h"

int main(int argc, char **argv)
{
    int					listenfd, connfd;
    pid_t				childpid;
    socklen_t			clilen;
    struct sockaddr_in	cliaddr, servaddr;
    void				sig_chld(int);
    char				buff[MAXLINE];
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);
    
    // Wrapper do unp.h que lida com os sinal SIGCHLD
    // fazendo o processo dar um waitpid para evitar
    // que os processos filhos se tornem zumbis.
    Signal(SIGCHLD, sig_chld);	/* must call waitpid() */
    
    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;		/* back to for() */
            else
                err_sys("accept error");
        }
        
        printf("connection from %s, port %d\n",
               Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
               ntohs(cliaddr.sin_port));
        
        if ( (childpid = Fork()) == 0) {	/* Processo Filho */
        
            // Fecha o socket de escuta - processo filho
            Close(listenfd);
        
            // Processamento da Requisição
            movie_rental_server(connfd);
            
            exit(0);
        }
        // Processo pai fecha o socket - filho processa
        Close(connfd);
    }
}