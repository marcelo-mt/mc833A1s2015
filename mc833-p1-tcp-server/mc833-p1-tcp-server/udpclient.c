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
#include "movie_rental_header.h"

void udp_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    size_t		n;
    char	sendline[MAXLINE], recvline[MAXLINE + 1];
    char    msg[MAXLINE];
    
    struct timeval t1, t2;
    long int elapsedTime;
    int server_time;
    char *server_time_str;
    char sr_t[100];
    
    MovieRentalRequest         request;
    
    request.action = -1;
    request.parameter1 = -1;
    request.parameter2 = -1;
    request.timed = 0;
    
    Connect(sockfd, (SA *) pservaddr, servlen);
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        Gettimeofday(&t1, NULL);
        
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
        
        n = Read(sockfd, recvline, MAXLINE);
        
        recvline[n] = 0;	/* null terminate */
        
        Fputs(recvline, stdout);
        
        server_time_str = strrchr(recvline,'|');
        server_time = atoi(server_time_str+1);
        snprintf(sr_t, sizeof(sr_t),"\nTempos: %d;", server_time);
        Fputs(sr_t, stdout);
        
        
        // Termina o timer
        Gettimeofday(&t2, NULL);
        
        // Computa os valores
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
        elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
        
        snprintf(sr_t, sizeof(sr_t),"%ld\n", elapsedTime);
        Fputs(sr_t, stdout);
    }
}

void udp_cli_test(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen, Test test, int rep_count)
{
    size_t		n;
    char	sendline[MAXLINE], recvline[MAXLINE + 1];
    char    msg[MAXLINE];
    
    struct timeval t1, t2;
    long int elapsedTime;
    int server_time;
    char *server_time_str;
    char sr_t[100];
    int i;
    
    MovieRentalRequest         request;
    
    Connect(sockfd, (SA *) pservaddr, servlen);
    
    request.action = -1;
    request.parameter1 = -1;
    request.parameter2 = -1;
    request.timed = 1;
    
    switch (test) {
        case Test2:
            request.action = MovieRentalActionListTitleYearGenre;
            request.parameter1 = MovieGenreAdventure;
            break;
        case Test3:
            request.action = MovieRentalActionGetSynopsis;
            request.parameter1 = 1;
            break;
        case Test4:
            request.action = MovieRentalActionGetCompleteInfo;
            request.parameter1 = 5;
            break;
        case Test5:
            request.action = MovieRentalActionListAllCompleteInfo;
            break;
        case Test6:
            request.action = MovieRentalActionSetQuantity;
            request.parameter1 = 4;
            request.parameter2 = 15;
            break;
        case Test7:
            request.action = MovieRentalActionGetQuantity;
            request.parameter1 = 3;
            break;
        case Test1:
        default:
            request.action = MovieRentalActionListTitleYear;
            break;
    }
    
    snprintf(msg, sizeof(msg), "%d %d %d %d", request.action, request.parameter1, request.parameter2, request.timed);
    
    for (i = 0; i < rep_count; i++) {
        
        Gettimeofday(&t1, NULL);
        
        Write(sockfd, msg, strlen(msg));
        
        n = Read(sockfd, recvline, MAXLINE);
        
        // Termina o timer
        Gettimeofday(&t2, NULL);
        
        recvline[n] = 0;	/* null terminate */
        
        server_time_str = strrchr(recvline,'|');
        server_time = atoi(server_time_str+1);
        snprintf(sr_t, sizeof(sr_t),"%d;", server_time);
        Fputs(sr_t, stdout);
        
        // Computa os valores
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
        elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
        
        snprintf(sr_t, sizeof(sr_t),"%ld\n", elapsedTime);
        Fputs(sr_t, stdout);
        
    }
}

int main(int argc, char **argv)
{
    int					sockfd;
    struct sockaddr_in	servaddr;
    
    int test_rep;
    Test test;
    
    // Parse dos argumentos de entrada para determinar o modo
    // de execução.
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
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    
    if (test == NoTest) {
        udp_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
    } else {
        udp_cli_test(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr), test, test_rep);
    }
    
    exit(0);
}
