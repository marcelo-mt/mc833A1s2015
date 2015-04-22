//
//  main.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 4090
//#include "movie.h"

void clearVector(char vector[])
{
    for (int i = 0; i< BUFF_SIZE; i++) {
        vector[i] = 0;
    }
    
}

void allTitlesAndDates ()
{
    FILE *file;
    if ((file = fopen("infos.txt", "r"))== NULL) {
        printf("arquivo nao pode ser aberto");
    }
    while (!feof(file)) {
        char a[BUFF_SIZE];
        int aux;
        float auxFloat;
        
        fgets(a, sizeof(a), file);
        printf("movie = %s",a);
        clearVector(a);

        fgets(a, sizeof(a), file);
//        printf("Genre = %s",a);
//        clearVector(a);
        
        fgets(a, sizeof(a), file);
//        printf("Director = %s",a);
//        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Year = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
//        printf("Time = %s",a);
//        clearVector(a);
        
        fgets(a, sizeof(a), file);
//        printf("ID = %s",a);
//        clearVector(a);
        
        fgets(a, sizeof(a), file);
//        printf("Disponible = %s",a);
        clearVector(a);
        
    }
    fclose(file);
}

int numOfMoviewWithId (int id)
{
    FILE *file;
    int num;
    char a[BUFF_SIZE];
    char b[1];
    //passando o numero para char
    a[0] = id + '0';
   strcat(a, "info.txt");
    if ((file = fopen(a, "r"))== NULL) {
        printf("arquivo nao pode ser aberto");
    }

    
    fgets(a, sizeof(a), file);
//    printf("movie = %s",a);
//    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Genre = %s",a);
    //        clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Director = %s",a);
    //        clearVector(a);
    
    fgets(a, sizeof(a), file);
//    printf("Year = %s",a);
//    clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("Time = %s",a);
    //        clearVector(a);
    
    fgets(a, sizeof(a), file);
    //        printf("ID = %s",a);
            clearVector(a);
    
    fgets(a, sizeof(a), file);
//            printf("Disponible = %s \n",a);

    fclose(file);
    //so funfa com ascii
    return  a[0] - '0';
    
}

void allInfo ()
{
    FILE *file, *file2;
    char a[BUFF_SIZE];
    char b[BUFF_SIZE];
    char c[40];
    
    //passando o numero para char
    if ((file = fopen("infos.txt", "r"))== NULL) {
        printf("arquivo nao pode ser aberto");
    }
    
    while (!feof(file)) {
        fgets(a, sizeof(a), file);
        printf("movie = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Genre = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Director = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Year = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Time = %s",a);
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Identifier = %s",a);
        
        //removendo quebra linha
        int i = 0;
        while (1) {
            if (a[i] == '\n') {
                a[i] = 0;
                break;
            }
            i++;
        }
        snprintf(c, sizeof (c), "%ssynopsis.txt", a);
        
        puts(c);
        if ((file2 = fopen(c, "r")) == NULL) {
            printf("nao foi possivel abrir o arquivo: %s\n",c);
        } else {
            while (!feof(file2)) {
                fgets(b, sizeof(b), file2);
                puts(b);
            }
        }
        
        clearVector(a);
        
        fgets(a, sizeof(a), file);
        printf("Disponible = %s \n",a);
        clearVector(a);

    }
        fclose(file);
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
    printf("Main");
    allInfo();
    return 0;
}
