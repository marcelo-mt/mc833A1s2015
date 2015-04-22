//
//  movie.h
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#ifndef __mc833_p1_tcp_server__movie__
#define __mc833_p1_tcp_server__movie__

#include <stdio.h>
#include <stdlib.h>

#define NUM_MOVIES 6

typedef enum {
    MovieGenreAction,
    MovieGenreDrama,
    MovieGenreRomance,
    MovieGenreAdventure,
    MovieGenreScienceFiction
} MovieGenre;

typedef struct _movie {
    char *title;
    int year;
    MovieGenre genre;
    float duration;
    char *synopsis;
    char *director;
    //cast
    int available_units;
    int identifier;
    
} Movie;

Movie * new_movie();
void print_movie(Movie *movie);
char * movie_genre_string(MovieGenre genre);
void free_movie(Movie *movie);

/*
 This method create an array with 6 movies
 
 author: Bruno Vargas
 */
Movie * get_all_movies ();

/*
 This method deallocate all moview contained by allMoview vector
 
 author: Bruno Vargas
 */
void free_vector_movies (Movie * allMovies[]);



#endif /* defined(__mc833_p1_tcp_server__movie__) */
