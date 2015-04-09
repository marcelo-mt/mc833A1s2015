//
//  movie.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "movie.h"

#define NUM_MOVIES 6 

static void free_string(char *string);

Movie * new_movie(void) {
    //Terminator
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


Movie * get_all_movies ()
{
    Movie * allMovies = (Movie *) malloc(sizeof(Movie) * NUM_MOVIES);
        //Terminator
        Movie *movie1 = (Movie *)malloc(sizeof(Movie));
        
        movie1->title = "Terminator";
        movie1->year = 1984;
        movie1->genre = MovieGenreScienceFiction;
        movie1->duration = 108.0f;
        movie1->synopsis = "Disguised as a human, a cyborg assassin known as a Terminator (Arnold Schwarzenegger) travels from 2029 to 1984 to kill Sarah Connor (Linda Hamilton). Sent to protect Sarah is Kyle Reese (Michael Biehn), who divulges the coming of Skynet, an artificial intelligence system that will spark a nuclear holocaust. Sarah is targeted because Skynet knows that her unborn son will lead the fight against them. With the virtually unstoppable Terminator in hot pursuit, she and Kyle attempt to escape.";
        movie1->director = "James Cameron";
        movie1->available_units = 4;
        movie1->identifier = 1;
        
        //Matrix
        Movie *movie2 = (Movie *)malloc(sizeof(Movie));
        
        movie2->title = "Matrix";
        movie2->year = 1999;
        movie2->genre = MovieGenreScienceFiction;
        movie2->duration = 136.0f;
        movie2->synopsis = "A computer hacker learns from mysterious rebels about the true nature of his reality and his role in the war against its controllers.";
        movie2->director = "Andy Wachowski";
        movie2->available_units = 2;
        movie2->identifier = 2;
        
        
        //The Lord of the Rings the return of the king
        Movie *movie3 = (Movie *)malloc(sizeof(Movie));
        
        movie3->title = "The Lord of the Rings: The Return of the King";
        movie3->year = 2003;
        movie3->genre = MovieGenreAdventure;
        movie3->duration = 201.0f;
        movie3->synopsis = "Gandalf and Aragorn lead the World of Men against Sauron's army to draw his gaze from Frodo and Sam as they approach Mount Doom with the One Ring.";
        movie3->director = "Peter Jackson";
        movie3->available_units = 5;
        movie3->identifier = 3;
        
        //Interview with the Vampire: The Vampire Chronicles
        Movie *movie4 = (Movie *)malloc(sizeof(Movie));
        
        movie4->title = "Interview with the Vampire: The Vampire Chronicles";
        movie4->year = 1994;
        movie4->genre = MovieGenreRomance;
        movie4->duration = 123.0f;
        movie4->synopsis = "A vampire tells his epic life story: love, betrayal, loneliness, and hunger.";
        movie4->director = "Neil Jordan";
        movie4->available_units = 1;
        movie4->identifier = 4;
        
        
        //Red Cliff
        Movie *movie5 = (Movie *)malloc(sizeof(Movie));
        
        movie5->title = "Red Cliff";
        movie5->year = 2008;
        movie5->genre = MovieGenreAdventure;
        movie5->duration = 148.0f;
        movie5->synopsis = "The first chapter of a two-part story centered on a battle fought in China's Three Kingdoms period (220-280 A.D.).";
        movie5->director = "John Woo";
        movie5->available_units = 1;
        movie5->identifier = 5;
        
        
        //Three Kingdoms
        Movie *movie6 = (Movie *)malloc(sizeof(Movie));
        
        movie6->title = "Three Kingdoms";
        movie6->year = 2008;
        movie6->genre = MovieGenreAdventure;
        movie6->duration = 102.0f;
        movie6->synopsis = "His country torn asunder by civil war, Zhao Zilong, a common man heeds the call of duty and from the humblest of roots rises through the ranks on wings of courage and cunning to command an army charged with liberating the land from an evil warlord. Inspiring by action, honor and a dream of unifying his divided nation, Zhao Zilong's heroism becomes legend, but as the years pass and the throne changes hands the war still rages on. When a newly enthroned king decides peace can only be achieved by defeating the warlords once and for all, the aging Zhao Zilong embarks on his final and greatest campaign, a road to adventure that will crown his name in glory for all time.";
        movie6->director = "Daniel Lee";
        movie6->available_units = 1;
        movie6->identifier = 3;
        
    
    allMovies[0] = *movie1;
    allMovies[1] = *movie2;
    allMovies[2] = *movie3;
    allMovies[3] = *movie4;
    allMovies[4] = *movie5;
    allMovies[5] = *movie6;
    
    return allMovies;
    
}

void freev_ector_movies (Movie * allMovies[])
{
    for (int i = 0; i < NUM_MOVIES; i ++) {
        free_movie(allMovies[i]);
    }
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