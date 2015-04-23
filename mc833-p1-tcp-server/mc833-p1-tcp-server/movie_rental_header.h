//
//  tcpheader.h
//  mc833-p1-tcp-server
//
//  Created by Marcelo M Toledo on 4/23/15.
//  Copyright (c) 2015 mc833. All rights reserved.
//

#ifndef mc833_p1_tcp_server_tcpheader_h
#define mc833_p1_tcp_server_tcpheader_h

#define DEFINED_TESTS 7

typedef enum {
    NoTest = -1, // Normal
    Test1 = 1,  // 
    Test2,
    Test3,
    Test4,
    Test5,
    Test6,
    Test7
} Test;

void	 movie_rental_server(int);
void	 movie_rental_client(FILE *, int);
void     movie_rental_client_test(FILE *, int, Test, int, struct timeval);

#endif
