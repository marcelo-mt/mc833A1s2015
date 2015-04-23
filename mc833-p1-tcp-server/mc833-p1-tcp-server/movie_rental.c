//
//  movie_rental.c
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/22/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#include "movie_rental.h"
#include "stripped_unp.h"

void execute_action_with_request(int sockfd, MovieRentalRequest *request)
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
    
}

void send_to_socket(int sockfd, char msg[MAXLINE])
{
    ssize_t		n;
    
    n = strlen(msg);
    Writen(sockfd, msg, n);
#warning BRUNO É AKI NESSES MÉTODO TA BOM? Coloca o conteudo da mensagem, sem terminar ela.
}

void list_all_title_year(int sockfd)
{
    char msg[MAXLINE];
    printf("list_all_title_year");
    snprintf(msg, sizeof(msg), "list_all_title_year");
    send_to_socket(sockfd, msg);
}

void list_all_title_year_bygenre(int sockfd, MovieGenre genre)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "list_all_title_year_bygenre: %s", movie_genre_string(genre));
    send_to_socket(sockfd, msg);
}

void get_synopsis_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_synopsis_by_id: %d", identifier);
    send_to_socket(sockfd, msg);
}

void get_info_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_info_by_id: %d", identifier);
    send_to_socket(sockfd, msg);
}

void list_all_complete(int sockfd)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "list_all_complete");
    send_to_socket(sockfd, msg);
}

void set_quantity_for_id(int sockfd, int identifier, int quantity)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "set_quantity_for_id: %d %d", identifier, quantity);
    send_to_socket(sockfd, msg);
}

void get_quantity_by_id(int sockfd, int identifier)
{
    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "get_quantity_by_id: %d", identifier);
    send_to_socket(sockfd, msg);
}
