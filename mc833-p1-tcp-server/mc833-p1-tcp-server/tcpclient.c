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
    
    Fputs("AAA", stdout);
    
    printf("%d\n", argc);
    
    if (argc == 2) {
        
        printf("MODO NORMALISSIMO\n");
        
        test = NoTest;
        test_rep = 1;
        
        printf("SAI UATI\n");
        
    } else {
        
        printf("MODO TESTE");
        
        if (argc != 4) {
            err_quit("usage: tcpclient <IPaddress> <Test#> <RepCount>");
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
    
    printf("PORRA\n");
    printf("CACILDA\n");
    printf("BBB\n");
    
    printf("Teste %d\n", test);
    
//    if (test != NoTest) {
//        
//        printf("AKI NAO\n");
//        
//        printf("test %d;rep_count %d\n", test, test_rep);
//        printf("consulta/atualizacao;total\n");
//    }
    printf("MAMAE\n");
    
    printf("PAPAI\n");

    printf("%d\n", test_rep);
    
    for (i = 0; i < test_rep; i++) {
        printf("B");
        
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        
        if (test != NoTest) {
            Gettimeofday(&t1, NULL);
        }
        
        printf("E");
        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
        printf("Conectation");
        
        if (test == NoTest) {
            printf("NIGGA G\n");
            movie_rental_client(stdin, sockfd);
            printf("YO");
        } else {
            printf("TESRTE\n");
            movie_rental_client_test(stdin, sockfd, test, test_rep, t1);
        }
        
        printf("VAI CLOSA");
        Close(sockfd);
        printf("CLOSO");
        
    }
    
    printf("\n");
    
//    for (i = 0; i < test_rep; i++) {
//        printf("B");
//        sockfd = Socket(AF_INET, SOCK_STREAM, 0);
//        printf("C");
//        bzero(&servaddr, sizeof(servaddr));
//        servaddr.sin_family = AF_INET;
//        servaddr.sin_port = htons(SERV_PORT);
//        Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
//        printf("D");
//        if (test != NoTest) {
//            // Começa o timer se em modo de teste
//            gettimeofday(&t1, NULL);
//        }
//        
//        printf("E");
//        Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
//        printf("F");
//        if (test != NoTest) {
//            printf("G");
//            movie_rental_client(stdin, sockfd);
//        } else {
//            printf("H");
//            movie_rental_client_test(stdin, sockfd, test, test_rep, t1);
//        }
//        
//        
//        Close(sockfd);
//    }
    
    exit(0);
    
}