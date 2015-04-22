//
//  movietcpsrv.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/21/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "commonheader.h"

int main(int argc, char **argv)
{
    int					listenfd, connfd;
    struct sockaddr_in	servaddr;
    char				buff[MAXLINE];
    time_t				ticks;
    
    printf("SocketCreation...\n");
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    printf("Socket cleanup...\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(5000);	/* daytime server */
    
    printf("Binding...\n");
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    
    printf("Listening...\n");
    Listen(listenfd, LISTENQ);
    
    printf("Waiting for connectin...");
    for ( ; ; ) {
        connfd = Accept(listenfd, (SA *) NULL, NULL);
        
        printf("Connection Accepted");
        
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        
        Close(connfd);
    }
}