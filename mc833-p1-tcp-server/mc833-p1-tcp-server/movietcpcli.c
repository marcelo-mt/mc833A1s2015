//
//  movietcpcli.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/21/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "commonheader.h"

#include	<time.h>

int main(int argc, char **argv)
{
    int					sockfd;
    struct sockaddr_in	servaddr;
    
    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");
    
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
    
    str_cli(stdin, sockfd);		/* do it all */
    
    exit(0);
}