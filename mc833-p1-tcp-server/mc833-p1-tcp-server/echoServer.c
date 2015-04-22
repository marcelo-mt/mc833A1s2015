
/*
 C socket server example
 */

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include "movie.h"

#define MAX_NAME 1000
#define BUFF_SIZE 20

void clearVector(char vector[])
{
    for (int i = 0; i< BUFF_SIZE; i++) {
        vector[i] = 0;
    }
    
}
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size, all_size;
    struct sockaddr_in server , client;
    char message_received[2000], resp_message[BUFF_SIZE], all_resp[3000];
    char *pointer;
    
    FILE *file;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    
    //Listen
    listen(socket_desc , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    
    if ((file = fopen("locadora.txt", "r")) == NULL)
    {
        puts("O arquivo nao pode ser aberto");
    }
    
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    //Receive a message from client
    while( (read_size = recv(client_sock , message_received , MAX_NAME , 0)) > 0 )
    {
        if ((file = fopen("locadora.txt", "r")) == NULL)
        {
            puts("O arquivo nao pode ser aberto");
        }

        puts(message_received);
        while (1)
               {
                   if (feof(file)) {
                       fread(resp_message, BUFF_SIZE, 1, file);
                       resp_message[BUFF_SIZE-1] = EOF;
                       write(client_sock, resp_message, strlen(resp_message));
                       puts(resp_message);
            
                       puts("acabou o arquivo");
                       break;
                   } else {
                       fread(resp_message, BUFF_SIZE, 1, file);
                       write(client_sock, resp_message, strlen(resp_message));
                       puts(resp_message);
                       clearVector(resp_message);
                   }
//                   resp_message[0] = 0;
               }
    
//        resp_message[strlen(resp_message)] = EOF;
//        write(client_sock, resp_message, strlen(resp_message));
//        puts(resp_message);
        char aux[3];
        aux[0] = EOF;
        write(client_sock, aux, 1);
        fclose(file);
    }
    
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    fclose(file);
    return 0;
    
}


 
 /*
 C socket server example
 */
/*
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include "movie.h"

#define MAX_NAME 1000
#define BUFF_SIZE 20
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size, all_size;
    struct sockaddr_in server , client;
    char message_received[2000], resp_message[BUFF_SIZE], all_resp[3000];
    char *pointer;
    
    FILE *file;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    
    //Listen
    listen(socket_desc , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    
    if ((file = fopen("locadora.txt", "r")) == NULL)
    {
        puts("O arquivo nao pode ser aberto");
    }
    
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    //Receive a message from client
    while( (read_size = recv(client_sock , message_received , MAX_NAME , 0)) > 0 )
    {
        puts(message_received);
        strcpy(all_resp, "primeiro,segundo,terceiro,quarto,quinto,sexto");
        
        all_size = (int)strlen(all_resp);
        all_resp[all_size] = EOF;
        
        
        int i = 0;
        //        while (!feof(file))
        //               {
        //                   fread(resp_message, BUFF_SIZE, 1, file);
        while (1) {
            if (all_size > BUFF_SIZE * i) {
                pointer = &all_resp[BUFF_SIZE * i];
                i++;
                memccpy(resp_message, pointer, 0, BUFF_SIZE);
                puts(resp_message);
                write(client_sock, resp_message, BUFF_SIZE);
                
                //                   write(client_sock, resp_message, strlen(resp_message));
                
            }
            else{
                char aux[3];
                aux[0] = EOF;
                write(client_sock, aux, strlen(aux));
                break;
            }
            
        }
    }
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    
    fclose(file);
    return 0;
}
 */