//
//  main.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 3/29/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include <stdio.h>

#include "movie.h"

int main(int argc, const char * argv[]) {
    
    Movie *movie = new_movie();
    print_movie(movie);
    free_movie(movie);
    
    Movie * allMovies = get_all_movies();
    
    for (int i = 0; i < 6; i ++) {
         print_movie(&allMovies[i]);
    }
   
    
    return 0;
}
