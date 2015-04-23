//
//  movietcpcli.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/21/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "stripped_unp.h"
#include "movie_rental_header.h"

int main(int argc, char **argv)
{
    int					i, sockfd;
    struct sockaddr_in	servaddr;
    
    // Variaveis para execução dos testes.
    struct timeval t1;
    
    int test_rep;
    Test test;
    
    if (argc == 2) {
        
        test = NoTest;
        test_rep = 1;
        
    } else {
        
        if (argc != 4) {
            err_quit("usage: ./tcpclient <IPaddress> <Test#> <RepCount>");
        }
        
        test = atoi(argv[2]);
        test_rep = atoi(argv[3]);
        
        if (test < 1 || test > DEFINED_TESTS) {
            err_quit("test %d not defined", test);
        }
        
        if (test_rep < 1) {
            err_quit("test rep_count should be greater than 0");
        }
        
    }
    
    
    if (test != NoTest) {
        printf("test %d;rep_count %d\n", test, test_rep);
        printf("consulta/atualizacao;total\n");
    }

    for (i = 0; i < test_rep; i++) {
        
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        
        if (test != NoTest) {
            Gettimeofday(&t1, NULL);
        }
        
        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
        
        if (test == NoTest) {
            movie_rental_client(stdin, sockfd);
        } else {
            movie_rental_client_test(stdin, sockfd, test, test_rep, t1);
        }
        
        Close(sockfd);
        
    }
    
    exit(0);
    
}