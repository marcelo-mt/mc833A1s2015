#include "stripped_unp.h"

#include "movie_rental.h"

void movie_rental_server(int sockfd)
{
    ssize_t             n;
    MovieRentalRequest  request;
    char                time_str[100];
    
    struct timeval t1, t2;
    long int elapsedTime;
    
    
    for ( ; ; ) {
        
        if ( (n = Readn(sockfd, &request, sizeof(request))) == 0)
            return;		/* connection closed by other end */
        
        if (request.timed) {
            // Tempo do começo do consulta/atualização da requisição
            Gettimeofday(&t1, NULL);
        }
        
        execute_action_with_request(sockfd, &request);
        
        if (request.timed) {
            // Tempo do fim do consulta/atualização da requisição - Resposta já foi escrita no buffer.
            Gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000;      // sec to us
            elapsedTime += (t2.tv_usec - t1.tv_usec);   // us
            
            // Append to tempo de consulta/atualização ao final (em microsegundos)
            snprintf(time_str, sizeof(time_str), "|%ld--\n", elapsedTime);
        } else {
            snprintf(time_str, sizeof(time_str), "--\n");
        }
        
        n = strlen(time_str);
        Writen(sockfd, time_str, n);
    }
}
