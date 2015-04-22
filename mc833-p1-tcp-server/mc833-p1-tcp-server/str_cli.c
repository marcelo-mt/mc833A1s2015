#include	"commonheader.h"

#include "movie_rental.h"

void str_cli(FILE *fp, int sockfd)
{
    char			sendline[MAXLINE], recvline[MAXLINE];
    Request		request;
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
            printf("invalid input: %s", sendline);
            continue;
        }
        
        Writen(sockfd, &request, sizeof(request));
        
        if (Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely");
        
        Fputs(recvline, stdout);
    }
}
