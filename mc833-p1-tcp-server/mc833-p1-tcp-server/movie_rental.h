#ifndef __mc833_p1_tcp_server__movie_rental__
#define __mc833_p1_tcp_server__movie_rental__

#include <stdio.h>

/**
 Enum definindo alguns gêneros de filme
 */
typedef enum {
    MovieGenreAction,
    MovieGenreDrama,
    MovieGenreRomance,
    MovieGenreAdventure,
    MovieGenreScienceFiction
} MovieGenre;

/**
 Enum definindo as ações suportadas pelo servidor
 da locadora.
 */
typedef enum {
    /**
     Títulos e ano de lançamento de todos os filmes.
     */
    MovieRentalActionListTitleYear = 0,
    /**
     Títulos e ano de lançamento de todos os filmes
     de um dado gênero passado como parâmetro.
     */
    MovieRentalActionListTitleYearGenre,
    /**
     Sinopse do filme com id passado como parâmetro.
     */
    MovieRentalActionGetSynopsis,
    /**
     Todos os dados de um filme com id passado como
     parâmetro.
     */
    MovieRentalActionGetCompleteInfo,
    /**
     Todos os dados de todos os filmes.
     */
    MovieRentalActionListAllCompleteInfo,
    /**
     Altera a quantidade disponível de um filme
     com id passado como parâmetro.
     */
    MovieRentalActionSetQuantity,
    /**
     Retorna a quantidade disponível de um filme
     com id passado como parâmetro.
     */
    MovieRentalActionGetQuantity
} MovieRentalAction;

/**
 Estrutura que representa uma requisição.
 Tendo em vista a simplicidade, dado que todas
 as ações são bem definidas e possuem no máximo
 dois parâmetros, modelou-se uma requisição da
 seguinte maneira:
  - timed é uma flag que indica se servidor deve
  computar e enviar o tempo (em micro segundos)
 que levou para processar a requisição.
 */
typedef struct _request {
    MovieRentalAction action;
    int parameter1;
    int parameter2;
    int timed;
} MovieRentalRequest;

/**
 Função que roteia uma MovieRentalRequest para a função apropriada,
 passando os parâmetros da maneira correta.
 */
void execute_action_with_request(int sockfd, MovieRentalRequest *request);

/**
 Função associada à Action MovieRentalActionListTitleYear.
 */
void list_all_title_year(int sockfd);
/**
 Função associada à Action MovieRentalActionListTitleYearGenre.
 */
void list_all_title_year_bygenre(int sockfd, MovieGenre genre);
/**
 Função associada à Action MovieRentalActionGetSynopsis.
 */
void get_synopsis_by_id(int sockfd, int identifier);
/**
 Função associada à Action MovieRentalActionGetCompleteInfo.
 */
void get_info_by_id(int sockfd, int identifier);
/**
 Função associada à Action MovieRentalActionListAllCompleteInfo.
 */
void list_all_complete(int sockfd);
/**
 Função associada à Action MovieRentalActionSetQuantity.
 */
void set_quantity_for_id(int sockfd, int identifier, int quantity);
/**
 Função associada à Action MovieRentalActionGetQuantity.
 */
void get_quantity_by_id(int sockfd, int identifier);

#endif /* defined(__mc833_p1_tcp_server__movie_rental__) */
