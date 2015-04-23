//
//  main.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include<unistd.h>    //write

#define BUFF_SIZE 4090
#define INF_SIZE  40090

#define NUM_FILMES 6
//#include "movie.h"


/*
 
 */
void clearVector(char vector[])
{
    for (int i = 0; i < BUFF_SIZE; i++) {
        vector[i] = 0;
    }
    
}
/*
 Funcao criada para colocar as informacoes no socket para o usuário
 */
void putInSocket (int socket, char text[BUFF_SIZE])
{
    if (socket == 0) {
        puts(text);
    } else{
        write(socket, text, strlen(text));
    }
}

int listOfMoviesOfGenre (int sock, int genre)
{
    char resp [INF_SIZE];
    char aux[BUFF_SIZE];
    
    FILE * file;
    if (genre ==0 ){
        //buscar Adventure
        if ((file = fopen("Adventure.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
    }
    else if(genre == 1){
        //buscar Romance
        
        if ((file = fopen("Romance.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
    } else if (genre == 2){
        //buscar ScienceFiction
        if ((file = fopen("ScienceFiction.txt", "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",aux);
            return 0;
        }
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
int numOfMoviewWithId (int id)
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
    return  a[0] - '0';
    
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

int main(int argc, const char * argv[]) {
    
//    Movie *movie = new_movie();
//    print_movie(movie);
//    free_movie(movie);
//    
//    Movie * allMovies = get_all_movies();
//    FILE *file;
//    char a[BUFF_SIZE], b[BUFF_SIZE], c[BUFF_SIZE], d[BUFF_SIZE];
//    int id, disp, year;
//    
//    if ((file = fopen("titles.txt", "r")) == NULL)
//    {
//        puts("O arquivo nao pode ser aberto");
//    }
//    
//    while (1)
//    {
//        if (feof(file)) {
//                puts("acabou o arquivo");
//            break;
//        } else {
//            while( (fgets(a, sizeof(a), file))!=NULL )
//                printf("----%s ", a);
//            
//        }
//    }
//    
//    fclose(file);
//    allTitlesAndDates();
//    printf ("%d",numOfMoviewWithId(1));

//      allInfo(0);
//    infoOfMovie(2, 0);
    char resp[INF_SIZE];

    infoOfMovie(1, 0);
    editDisponibilityOfMovie(1, 0, 0);
    infoOfMovie(1, 0);
    
//    char aux[INF_SIZE];
//    
//    getInfoOfMovie(2, aux);
//    strcat(resp, aux);
//    getInfoOfMovie(1, aux);
//    strcat(resp, aux);
//    puts(resp);
    return 0;
}
