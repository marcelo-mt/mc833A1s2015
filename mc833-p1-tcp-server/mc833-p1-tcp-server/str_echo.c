#include	"stripped_unp.h"

#include "movie_rental.h"

#include <sys/time.h>

void str_echo(int sockfd)
{
    ssize_t			n;
    Request         request;
    char            time_str[MAXLINE];
    
    struct timeval t1, t2;
    long int elapsedTime;
    
    
    for ( ; ; ) {
        
        if ( (n = Readn(sockfd, &request, sizeof(request))) == 0)
            return;		/* connection closed by other end */
        
        
        gettimeofday(&t1, NULL);
        
        execute_action_with_request(sockfd, &request);
        
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
        elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
        
        snprintf(time_str, sizeof(time_str), "-%ld\n", elapsedTime);
        
        n = strlen(time_str);
        Writen(sockfd, time_str, n);
        
    }
}
