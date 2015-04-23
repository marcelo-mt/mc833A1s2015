//
//  movie_rental.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/22/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "movie_rental.h"
#include "commonheader.h"

#define BUFF_SIZE 3999
#define INF_SIZE 40000
#define NUM_FILMES 6
void clearVector(char vector[])
{
    for (int i = 0; i < BUFF_SIZE; i++) {
        vector[i] = 0;
    }
    
}
/*
 Funcao criada para colocar as informacoes no socket para o usuário
 */
void putInSocket (int socket, char text[])
{
    puts(text);
    strcat(text, "--");
    text[MAXLINE -1] = EOF;
    Writen(socket, text, strlen(text));
}

int listOfMoviesOfGenre (int sock, int genre)
{
    char resp [INF_SIZE];
    char aux[BUFF_SIZE];
    FILE * file;
    if (genre ==MovieGenreAdventure){
        //buscar Adventure
        if ((file = fopen("Adventure.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
    }
    else if(genre == MovieGenreRomance){
        //buscar Romance
        
        if ((file = fopen("Romance.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
    } else if (genre == MovieGenreScienceFiction){
        //buscar ScienceFiction
        if ((file = fopen("ScienceFiction.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
    } else{
        putInSocket(sock, "Nao possuímos nenhum filme com este gënero.");
        return 1;
    }
    while (!feof(file)) {
        fgets(aux, sizeof(aux), file);
        strcat(resp, aux);
        clearVector(aux);
    }
    strcat(resp, "\n");
    putInSocket(sock, resp);
    clearVector(resp);
    fclose(file);
    return 1;
}
int allTitlesAndDates (int sock)
{
    FILE *file;
    char resp[INF_SIZE];
    if ((file = fopen("infos.txt", "r"))== NULL) {
        printf("arquivo nao pode ser aberto");
    }
    while (!feof(file)) {
        char a[BUFF_SIZE];
        
        fgets(a, sizeof(a), file);
        
        strcat(resp, a);
        clearVector(a);
        fgets(a, sizeof(a), file); //Genero
        
        fgets(a, sizeof(a), file); // Diretor
        
        fgets(a, sizeof(a), file); //Ano
        strcat(resp, a);
        clearVector(a);
        fgets(a, sizeof(a), file); // Tempo
        
        fgets(a, sizeof(a), file); //identificador
        
        fgets(a, sizeof(a), file); // Disponibilidade
        clearVector(a);
        
    }
    putInSocket(sock, resp);
    fclose(file);
    return 1;
}
int numOfMoviewWithId (int sock, int id)
{
    FILE *file;
    char a[BUFF_SIZE];
    //passando o numero para char
    a[0] = id + '0';
    strcat(a, "info.txt");
    if ((file = fopen(a, "r"))== NULL) {
        printf("arquivo nao pode ser aberto");
    }
    
    
    fgets(a, sizeof(a), file);
    //    printf("movie = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Genre = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Director = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //    printf("Year = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Time = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("ID = %s",a);
    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //            printf("Disponible = %s \n",a);
    clearVector(a);
    fclose(file);
    //so funfa com ascii
    putInSocket(sock, a);
    return  1;
    
}
int getSynopsisOfMovie (int id, char resp[INF_SIZE])
{
    char movie[BUFF_SIZE];
    
    FILE * file;
    
    snprintf(movie, sizeof (movie), "%dsynopsis.txt", id);
    if ((file = fopen(movie, "r")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",movie);
        return 0;
    } else {
        while (!feof(file)) {
            fgets(movie, sizeof(movie), file);
            strcat(resp, movie);
        }
        fclose(file);
        return 1;
    }
}
int getInfoOfMovie (int id, char resp[INF_SIZE])
{
    char syn [BUFF_SIZE];
    char aux[BUFF_SIZE];
    
    FILE * file;
    
    snprintf(aux, sizeof (aux), "%dinfo.txt", id);
    if ((file = fopen(aux, "r")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",aux);
        return 0;
    } else {
        while (!feof(file)) {
            fgets(aux, sizeof(aux), file);
            strcat(resp, aux);
        }
        strcat(resp, "\n");
        if (getSynopsisOfMovie(id, syn)) {
            strcat(resp, syn);
            clearVector(syn);
        } else{
            return 0;
        }
        strcat(resp, "\n");
        fclose(file);
        return 1;
    }
}
int infoOfMovie (int id, int sock)
{
    char movie[INF_SIZE];
    char syn [INF_SIZE];
    char aux[BUFF_SIZE];
    
    FILE * file;
    
    snprintf(aux, sizeof (aux), "%dinfo.txt", id);
    if ((file = fopen(aux, "r")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",aux);
        return 0;
    } else {
        while (!feof(file)) {
            fgets(aux, sizeof(aux), file);
            strcat(movie, aux);
            clearVector(aux);
        }
        strcat(movie, "\n");
        if (getSynopsisOfMovie(id, syn)) {
            strcat(movie, syn);
            clearVector(syn);
        } else{
            return 0;
        }
        strcat(movie, "\n");
        putInSocket(sock, movie);
        clearVector(movie);
    }
    fclose(file);
    return 1;
    
}
int allInfo (int sock)
{
    char resp[INF_SIZE], aux[BUFF_SIZE];
    for (int i = 1; i <= NUM_FILMES; i ++) {
        getInfoOfMovie(i, aux);
        strcat(resp, aux);
        clearVector(aux);
    }
    
    putInSocket(sock, resp);
    return 1;
    
    
}
int synopsisOfMovie (int id, int sock)
{
    char movie[BUFF_SIZE];
    char resp[INF_SIZE];
    FILE * file;
    
    snprintf(movie, sizeof (movie), "%dsynopsis.txt", id);
    if ((file = fopen(movie, "r")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",movie);
        return 0;
    } else {
        while (!feof(file)) {
            fgets(movie, sizeof(movie), file);
            strcat(resp, movie);
        }
        putInSocket(sock, resp);
    }
    fclose(file);
    return 1;
}
int editDisponibilityOfMovie(int id, int sock, int newDisp)
{
    char title [BUFF_SIZE];
    char genre [BUFF_SIZE];
    char director [BUFF_SIZE];
    char year [BUFF_SIZE];
    char duration [BUFF_SIZE];
    char identifier [BUFF_SIZE];
    char disponibility [BUFF_SIZE];
    
    char aux [BUFF_SIZE];
    FILE * file;
    
    snprintf(aux, sizeof (aux), "%dinfo.txt", id);
    if ((file = fopen(aux, "r")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",aux);
        return 0;
    } else {
        fgets(title, sizeof(title), file); //tittle
        fgets(genre, sizeof(genre), file); //Genero
        fgets(director, sizeof(director), file); // Diretor
        fgets(year, sizeof(year), file); //Ano
        fgets(duration, sizeof(duration), file); // Tempo
        fgets(identifier, sizeof(identifier), file); //identificador
        snprintf(disponibility, sizeof (disponibility), "%d", newDisp);
        fclose(file);
    }
    
    if ((file = fopen(aux, "w")) == NULL) {
        printf("nao foi possivel abrir o arquivo: %s\n",aux);
        return 0;
    } else {
        
        fputs(title, file);
        fputs(genre, file);
        fputs(director, file);
        fputs(year, file);
        fputs(duration, file);
        fputs(identifier, file);
        fputs(disponibility, file);
        fclose(file);
    }
    
    clearVector(title);
    clearVector(genre);
    clearVector(director);
    clearVector(year);
    clearVector(duration);
    clearVector(identifier);
    clearVector(disponibility);
    fclose(file);
    return 1;
}




void execute_action_with_request(int sockfd, Request *request)
{
    switch (request->action) {
        case MovieRentalActionListTitleYear:
            list_all_title_year(sockfd);
            break;
        case MovieRentalActionListTitleYearGenre:
            list_all_title_year_bygenre(sockfd, (MovieGenre)request->parameter1);
            break;
        case MovieRentalActionGetSynopsis:
            get_synopsis_by_id(sockfd, request->parameter1);
            break;
        case MovieRentalActionGetCompleteInfo:
            get_info_by_id(sockfd, request->parameter1);
            break;
        case MovieRentalActionListAllCompleteInfo:
            list_all_complete(sockfd);
            break;
        case MovieRentalActionSetQuantity:
            set_quantity_for_id(sockfd, request->parameter1, request->parameter2);
            break;
        case MovieRentalActionGetQuantity:
            get_quantity_by_id(sockfd, request->parameter1);
            break;
        default:
            
            // UNKNOWN ACTION
            Writen(sockfd, "Unknown Action", sizeof("Unknown Action"));
            
            break;
    }
    
#warning Aqui coloca no socket o caracter que diz que acabou a mensagem
    puts("Acabou o server");
    char  * aux = "--";
    putInSocket(sockfd, aux);
    
}

void send_to_socket(int sockfd, char msg[])
{
    ssize_t		n;
    
    n = strlen(msg);
    Writen(sockfd, msg, n);
#warning BRUNO É AKI NESSES MÉTODO TA BOM? Coloca o conteudo da mensagem, sem terminar ela.
}

void list_all_title_year(int sockfd)
{
//    char msg[MAXLINE];
    printf("list_all_title_year");
//    snprintf(msg, sizeof(msg), "list_all_title_year\n");
//    send_to_socket(sockfd, msg);
    allTitlesAndDates(sockfd);
    
}

void list_all_title_year_bygenre(int sockfd, MovieGenre genre)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "list_all_title_year_bygenre: %s\n", movie_genre_string(genre));
//    send_to_socket(sockfd, msg);
    puts(msg);
    listOfMoviesOfGenre(sockfd, genre);
}

void get_synopsis_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_synopsis_by_id: %d\n", identifier);
//    send_to_socket(sockfd, msg);
    synopsisOfMovie(identifier, sockfd);
    
}

void get_info_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_info_by_id: %d\n", identifier);
//    send_to_socket(sockfd, msg);
    infoOfMovie(identifier, sockfd);
}

void list_all_complete(int sockfd)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "list_all_complete\n");
//    send_to_socket(sockfd, msg);
    allInfo(sockfd);
}

void set_quantity_for_id(int sockfd, int identifier, int quantity)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "set_quantity_for_id: %d %d\n", identifier, quantity);
//    send_to_socket(sockfd, msg);
    editDisponibilityOfMovie(identifier, sockfd, quantity);
}

void get_quantity_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_quantity_by_id: %d\n", identifier);
//    send_to_socket(sockfd, msg);
    numOfMoviewWithId(sockfd, identifier);
}
