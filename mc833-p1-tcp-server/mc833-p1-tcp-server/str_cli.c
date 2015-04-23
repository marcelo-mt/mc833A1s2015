#include	"commonheader.h"

#include "movie_rental.h"
void cVector(char vector[])
{
    for (int i = 0; i< MAXLINE; i++) {
        vector[i] = 0;
    }
    
}

void str_cli(FILE *fp, int sockfd)
{
    char			sendline[MAXLINE], recvline[MAXLINE];
    Request		request;
    long totalSize;
    
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        
        if (sscanf(sendline, "%d%d%d", &request.action, &request.parameter1, &request.parameter2) <= 0) {
            printf("invalid input: %s", sendline);
            continue;
        }
        
        Writen(sockfd, &request, sizeof(request));
        
        while (1) {
            if ((totalSize = (Readline(sockfd, recvline, MAXLINE))) == 0)
                err_quit("str_cli: server terminated prematurely");
           
            if(strstr(recvline, "--") != NULL) {
                break;
            }
            Fputs(recvline, stdout);
            cVector(recvline);
        }
    }
}
