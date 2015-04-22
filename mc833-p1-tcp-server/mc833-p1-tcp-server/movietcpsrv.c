//
//  movietcpsrv.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/21/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "commonheader.h"

#include	<time.h>

int main(int argc, char **argv)
{
    pid_t pid;
    int					listenfd, connfd;
    socklen_t			len;
    struct sockaddr_in	servaddr, cliaddr;
    char				buff[MAXLINE];
    time_t				ticks;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(5005);	/* daytime server */
    
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);
    
    for ( ; ; ) {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &len);
        
        if( (pid = Fork()) == 0) {
            
            Close(listenfd);
        
            printf("connection from %s, port %d\n",
                   Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
                   ntohs(cliaddr.sin_port));
            sleep(5);
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            Write(connfd, buff, strlen(buff));
            
            Close(connfd);
            exit(0);
            
        }
        
        Close(connfd);
    }
}