#include	"commonheader.h"

#include "movie_rental.h"

void str_echo(int sockfd)
{
    ssize_t			n;
    Request         request;
    
    for ( ; ; ) {
        
        if ( (n = Readn(sockfd, &request, sizeof(request))) == 0)
            return;		/* connection closed by other end */
        
        execute_action_with_request(sockfd, &request);
    }
}
