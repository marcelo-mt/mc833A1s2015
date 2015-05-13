#ifndef mc833_p1_tcp_server_tcpheader_h
#define mc833_p1_tcp_server_tcpheader_h

#define DEFINED_TESTS 7

/**
 Enum listando os testes definidos.
 */
typedef enum {
    // Execução normal/interativa.
    NoTest = -1,
    // MovieRentalActionListTitleYear
    Test1 = 1,
    // MovieRentalActionListTitleYearGenre
    // Genre: Adventure
    Test2,
    // MovieRentalActionGetSynopsis
    // id: 1
    Test3,
    // MovieRentalActionGetCompleteInfo
    // id: 5
    Test4,
    // MovieRentalActionListAllCompleteInfo
    Test5,
    // MovieRentalActionSetQuantity
    // id = 4
    // quantity = 15
    Test6,
    // MovieRentalActionGetQuantity
    // id = 3
    Test7
} Test;

/**
 Função que funciona como interface entre o 
 servidor e a aplicação.
 */
void	 movie_rental_server(int);

/**
 Função que atua como interface de um cliente da aplicação
 no cenário normal on o usuário interage interativamente com
 o servidor.
 */
void	 movie_rental_client(FILE *, int);

/**
 Função que simula a interação do usuário com o servidor execuntando
 um dos testes definidos acima.
 */
void     movie_rental_client_test(FILE *, int, Test, int, struct timeval);

#endif
