//
//  udpclient.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 5/12/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include <stdio.h>
#include "stripped_unp.h"

#include "movie_rental.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    size_t		n;
    char	sendline[MAXLINE], recvline[MAXLINE + 1];
    char    msg[MAXLINE];
    
    MovieRentalRequest         request;
    
    request.action = -1;
    request.parameter1 = -1;
    request.parameter2 = -1;
    request.timed = 0;
    
    Connect(sockfd, (SA *) pservaddr, servlen);
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        request.action = -1;
        request.parameter1 = -1;
        request.parameter2 = -1;
        request.timed = 0;
        
        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
            printf("invalid input: %s", sendline);
            continue;
        }
        
        request.timed = 0;
        
        printf("Request enviada: %d %d %d %d\n", request.action, request.parameter1, request.parameter2, request.timed);
        snprintf(msg, sizeof(msg), "%d %d %d %d", request.action, request.parameter1, request.parameter2, request.timed);
        
        Write(sockfd, msg, strlen(msg));
        
//        while (1) {
            n = Read(sockfd, recvline, MAXLINE);
            
            recvline[n] = 0;	/* null terminate */
            Fputs(recvline, stdout);
//        }
    }
}

int main(int argc, char **argv)
{
    int					sockfd;
    struct sockaddr_in	servaddr;
    
    if (argc != 2)
        err_quit("usage: udpcli <IPaddress>");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
    
    exit(0);
}
