//
//  movie.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "movie.h"

static void free_string(char *string);

Movie * new_movie(void) {
    
    Movie *movie = (Movie *)malloc(sizeof(Movie));
    
    movie->title = "Terminator";
    movie->year = 1984;
    movie->genre = MovieGenreScienceFiction;
    movie->duration = 108.0f;
    movie->synopsis = "Disguised as a human, a cyborg assassin known as a Terminator (Arnold Schwarzenegger) travels from 2029 to 1984 to kill Sarah Connor (Linda Hamilton). Sent to protect Sarah is Kyle Reese (Michael Biehn), who divulges the coming of Skynet, an artificial intelligence system that will spark a nuclear holocaust. Sarah is targeted because Skynet knows that her unborn son will lead the fight against them. With the virtually unstoppable Terminator in hot pursuit, she and Kyle attempt to escape.";
    movie->director = "James Cameron";
    movie->available_units = 4;
    movie->identifier = 1;
    
    return movie;
}

void print_movie(Movie *movie) {
    printf("\tTitle: %s\n"
           "\tYear: %d\n"
           "\tGenre: %s\n"
           "\tDuration: %.2f\n"
           "\tSynopsis: %s\n"
           "\tDirector: %s\n"
           "\tAvailable Units: %d\n"
           "\tIdentifier: %d\n", movie->title, movie->year, movie_genre_string(movie->genre), movie->duration, movie->synopsis, movie->director, movie->available_units, movie->identifier);
}

char * movie_genre_string(MovieGenre genre) {
    switch (genre) {
        case MovieGenreAction:
            return "Action";
            break;
        case MovieGenreDrama:
            return "Drama";
            break;
        case MovieGenreRomance:
            return "Romance";
            break;
        case MovieGenreAdventure:
            return "Adventure";
            break;
        case MovieGenreScienceFiction:
            return "Science Fiction";
            break;
        default:
            return "Unknown";
            break;
    }
}

void free_movie(Movie *movie) {
    if (movie != NULL) {
//        free_string(movie->title);
//        free_string(movie->synopsis);
//        free_string(movie->director);
        free(movie);
    }
}

static void free_string(char *string) {
    if (string != NULL) {
        free(string);
    }
}