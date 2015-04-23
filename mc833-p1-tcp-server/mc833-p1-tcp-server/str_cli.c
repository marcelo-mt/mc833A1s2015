#include	"commonheader.h"

#include "movie_rental.h"

void str_cli(FILE *fp, int sockfd)
{
//    char			sendline[MAXLINE];
    char            recvline[MAXLINE];
    Request         request;
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
    
        Writen(sockfd, &request, sizeof(request));
        
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
    
        server_time_str = strrchr(recvline,'-');
    server_time = atoi(server_time_str+1);
    snprintf(sr_t, sizeof(sr_t),"%d;", server_time);
    Fputs(sr_t, stdout);
    
//        Fputs(recvline, stdout);
//    }
}
