//
//  movietcpcli.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/21/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "stripped_unp.h"

#include	<time.h>
#include    <sys/time.h>

typedef enum {
    NoTest = 0,
    Test1 = 1,
    Test2,
    Test3,
    Test4,
    Test5,
    Test6,
    Test7
} Test;

int main(int argc, char **argv)
{
    int					sockfd;
    struct sockaddr_in	servaddr;
    
    // Variaveis para execução dos testes.
    struct timeval t1, t2;
    long int elapsedTime;
    int test_rep;
    Test test;
    
    if (argc != 4)
        err_quit("usage: tcpclient <IPaddress> <Test#> <RepCount>");
    
    test = atoi(argv[2]);
    test_rep = atoi(argv[3]);
    
    printf("test %d;rep_count %d\n", test, test_rep);
    printf("consulta/atualizacao;total\n");
    
    for (int i = 0; i < test_rep; i++) {
        
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);
        
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        
        // Começa o timer
        gettimeofday(&t1, NULL);
        
        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
        str_cli(stdin, sockfd);		/* do it all */
        
        // Termina o timer
        gettimeofday(&t2, NULL);
        
        // Computa os valores
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
        elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
        
        printf("%ld\n", elapsedTime);
        Close(sockfd);
    }
    
    exit(0);
}