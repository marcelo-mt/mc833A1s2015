//
//  movie_rental.h
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/22/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#ifndef __mc833_p1_tcp_server__movie_rental__
#define __mc833_p1_tcp_server__movie_rental__

#include <stdio.h>
#include "movie.h"


typedef enum {
    MovieRentalActionListTitleYear = 0,
    MovieRentalActionListTitleYearGenre,
    MovieRentalActionGetSynopsis,
    MovieRentalActionGetCompleteInfo,
    MovieRentalActionListAllCompleteInfo,
    MovieRentalActionSetQuantity,
    MovieRentalActionGetQuantity
} MovieRentalAction;

typedef struct _request {
    MovieRentalAction action;
    int parameter1;
    int parameter2;
    
} Request;

void execute_action_with_request(int sockfd, Request *request);

void list_all_title_year(int sockfd);
void list_all_title_year_bygenre(int sockfd, MovieGenre genre);
void get_synopsis_by_id(int sockfd, int identifier);
void get_info_by_id(int sockfd, int identifier);
void list_all_complete(int sockfd);
void set_quantity_for_id(int sockfd, int identifier, int quantity);
void get_quantity_by_id(int sockfd, int identifier);

#endif /* defined(__mc833_p1_tcp_server__movie_rental__) */
