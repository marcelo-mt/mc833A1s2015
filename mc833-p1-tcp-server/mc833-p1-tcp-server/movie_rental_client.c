#include "stripped_unp.h"
#include "movie_rental_header.h"
#include "movie_rental.h"

void cVector(char vector[])
{
    for (int i = 0; i< MAXLINE; i++) {
        vector[i] = 0;
    }
}

void movie_rental_client(FILE *fp, int sockfd)
{
    char			sendline[MAXLINE];
    char            recvline[MAXLINE];
    MovieRentalRequest         request;
    long totalSize;
    
    printf("In: ");
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
            printf("invalid input: %s", sendline);
            continue;
        }
        printf("\nOut:\n");
        
        request.timed = 0;
        
        Writen(sockfd, &request, sizeof(request));
        
        while (1) {
            if ((totalSize = (Readline(sockfd, recvline, MAXLINE))) == 0)
                err_quit("movie_rental_client: server terminated prematurely");
            
            if(strstr(recvline, "--") != NULL) {
                break;
            }
            
            Fputs(recvline, stdout);
            cVector(recvline);
        }
        
        Fputs(recvline, stdout);
        
        printf("In: ");
    }
}

void movie_rental_client_test(FILE *fp, int sockfd, Test test, int rep_count, struct timeval t1)
{
    char            recvline[MAXLINE];
    MovieRentalRequest         request;
    long totalSize;
    
    struct timeval t2;
    long int elapsedTime;
    int server_time;
    char *server_time_str;
    char sr_t[100];
    
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
    
    request.timed = 1;
    
    Writen(sockfd, &request, sizeof(request));
    
    while (1) {
        if ((totalSize = (Readline(sockfd, recvline, MAXLINE))) == 0)
            err_quit("movie_rental_client_test: server terminated prematurely");
        
        if(strstr(recvline, "--") != NULL) {
            break;
        }
        
//        Fputs(recvline, stdout);
        cVector(recvline);
    }
    
    server_time_str = strrchr(recvline,'|');
    server_time = atoi(server_time_str+1);
    snprintf(sr_t, sizeof(sr_t),"%d;", server_time);
    Fputs(sr_t, stdout);
    
    
    // Termina o timer
    gettimeofday(&t2, NULL);
    
    // Computa os valores
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
    elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
    
    snprintf(sr_t, sizeof(sr_t),"%ld\n", elapsedTime);
    Fputs(sr_t, stdout);
    
}

