//
//  udpserver.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 5/12/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include <stdio.h>

#include "movie_rental.h"

void udp_srv(int sockfd, SA *pcliaddr, socklen_t clilen)
{
//    int			n;
    socklen_t	len;
    char		mesg[MAXLINE];
    char        out[MAXLINE];
    
    ssize_t             n;
    MovieRentalRequest  request;
    
    struct timeval t1;
    
    for ( ; ; ) {
        len = clilen;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        
        Gettimeofday(&t1, NULL);
        
        if (sscanf(mesg, "%d%d%d%d", &request.action, &request.parameter1, &request.parameter2, &request.timed) <= 0) {
            printf("invalid input: %s", mesg);
            continue;
        }
        
        snprintf(out, sizeof(out), "Action que chegou no servidor: %d %d %d %d", request.action, request.parameter1, request.parameter2, request.timed);
        
        execute_udp_action_with_request(sockfd, &request, pcliaddr, clilen, t1);
        
    }
}


int main(int argc, char **argv)
{
    int					sockfd;
    struct sockaddr_in	servaddr, cliaddr;
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    
    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
    
    udp_srv(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
}
