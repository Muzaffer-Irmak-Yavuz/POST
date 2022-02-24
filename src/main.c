#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#include "../include/help.h"
#include "../include/socket.h"


void post_text(char* str1, const char* data)
{
    char postlength[128];

    sprintf(postlength, "%ld\r\n", strlen(data));
    
    strcat(str1, "Content-Type: text/plain\r\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, postlength);
    strcat(str1, "\r\n");
    strcat(str1, data);		
}



int main(int argc, const char *argv[])
{
    
    if (argc < 2)
    {
        help_menu(argv[0]);
        exit(1);
    }

    char buffer[15000];
    char *query = calloc(200 , sizeof(char));
    char *format = "POST %s HTTP/1.0\r\n";
    int web_soket;

    char option[3];
    strcpy(option, argv[1]);
    

    if (strcmp(argv[1],"-t") == 0)
    {
        web_soket = get_socket(argv[2]);
        sprintf(query,format,argv[3]);
        post_text(query, argv[4]);
        
    }
    else if (strcmp(argv[1],"-i") == 0)
    {
        web_soket = get_socket(argv[2]);
        sprintf(query,format,argv[3]);
       
    }
    else if (strcmp(argv[1],"-h") == 0)
    {
        help_menu(argv[0]);
        exit(1);
    }
    else{
        
    }
    /// Soket Açma.

    strcat(query,"\r\n\r\n");
    write(web_soket,query,strlen(query));
    printf("REAd");
    read(web_soket,buffer,1200);
    printf("%s",buffer);
}