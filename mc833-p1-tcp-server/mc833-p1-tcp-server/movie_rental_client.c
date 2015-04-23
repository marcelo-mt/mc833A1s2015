#include "stripped_unp.h"
#include "movie_rental_header.h"
#include "movie_rental.h"

void movie_rental_client(FILE *fp, int sockfd)
{
    char			sendline[MAXLINE];
    char            recvline[MAXLINE];
    MovieRentalRequest         request;
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
            printf("invalid input: %s", sendline);
            continue;
        }
        
        request.timed = 1;
        
        Writen(sockfd, &request, sizeof(request));
        
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        
        Fputs(recvline, stdout);
    }
}

void movie_rental_client_test(FILE *fp, int sockfd, Test test, int rep_count, struct timeval t1)
{
    //    char			sendline[MAXLINE];
    char            recvline[MAXLINE];
    MovieRentalRequest         request;
    char *server_time_str;
    char sr_t[100];
    int server_time;
    
    //    while (Fgets(sendline, MAXLINE, fp) != NULL) {
    
    //        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
    //            printf("invalid input: %s", sendline);
    //            continue;
    //        }
    
    request.action = MovieRentalActionListTitleYearGenre;
    request.parameter1 = MovieGenreRomance;
    request.timed = 0;
    
    Writen(sockfd, &request, sizeof(request));
    
    if (Readline(sockfd, recvline, MAXLINE) == 0)
        err_quit("str_cli: server terminated prematurely");
    
    server_time_str = strrchr(recvline,'-');
    server_time = atoi(server_time_str+1);
    snprintf(sr_t, sizeof(sr_t),"%d;", server_time);
    Fputs(sr_t, stdout);
    
    //        Fputs(recvline, stdout);
    //    }

    struct timeval t2;
    long int elapsedTime;
    
    // Termina o timer
    gettimeofday(&t2, NULL);
    
    // Computa os valores
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
    elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
    
    printf("%ld\n", elapsedTime);
}

