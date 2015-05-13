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
        
        // Caso modo de execução seja normal, executa função
        // que permite que usuário interaga interativamente com
        // o servidor.
        if (test == NoTest) {
            movie_rental_client(stdin, sockfd);
        } else {
            // Caso modo seja de teste, passar teste pre-determinado
            // para rodar um caso de uso.
            // Se foi passado como parametro um rep_count > 1
            // esse teste será feito diversas vezes sequencialmente.
            movie_rental_client_test(stdin, sockfd, test, test_rep, t1);
        }
        
        Close(sockfd);
        
    }
    
    exit(0);
    
}