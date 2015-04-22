/*
 C ECHO client example using sockets
 */
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#define BUFF_SIZE 20

void clearVector(char vector[])
{
    for (int i = 0; i< BUFF_SIZE; i++) {
        vector[i] = 0;
    }
    
}

int main(int argc , char *argv[])
{
    int sock, totalSize = 0;
    struct sockaddr_in server;
    char message[1000] , server_reply[10];
    
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
    
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    
    puts("Connected\n");
    
    //keep communicating with server
    while(1)
    {
        printf("Enter message : ");
        scanf("%s" , message);
        
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        
        while(1)
        {
            if((totalSize = recv(sock , server_reply , BUFF_SIZE, 0)) < 0)
            {
                puts(server_reply);
                printf("nao consigo mais ler");
                break;
            }
//            server_reply[totalSize] = 0;
            //sair do while
            if(server_reply[totalSize-1] != EOF)
            {
                puts(server_reply);
                clearVector(server_reply);
            }
            else {
                puts(server_reply);
                break;
            }
            
        }
    }
    
    close(sock);
    return 0;}