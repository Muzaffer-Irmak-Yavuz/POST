#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#include "../include/help.h"
#include "../include/socket.h"


void post_text(char* query, const char* data)
{
    char postlength[128];

    sprintf(postlength, "%ld\r\n", strlen(data));
    
    strcat(query, "Content-Type: text/plain\r\n");
    strcat(query, "Content-Length: ");
    strcat(query, postlength);
    strcat(query, "\r\n");
    strcat(query, data);		
}

void post_data(char* query, const char* filename)
{
    if (query == NULL) {
        fprintf(stderr,"PARAM");
        exit(EXIT_FAILURE);
    }


    FILE *image_file = fopen(filename, "rb");
    if (image_file == NULL) {
        fprintf(stderr, "Cannot open\n");
        exit(EXIT_FAILURE);
    }

    fseek(image_file, 0, SEEK_END);
    size_t image_length = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    void *image_content = calloc(image_length + 2,sizeof(char));
    if (image_content == NULL) {
        fprintf(stderr, "Cannot allocate mem for image_content\n");
        exit(EXIT_FAILURE);
    }


    size_t read_length = fread(image_content, sizeof(char), image_length, image_file);
    if (read_length != image_length) {
        fprintf(stderr, "Cannot read\n");
        exit(EXIT_FAILURE);
    }

    if (memcpy(image_content + image_length, "\r\n", 2) == NULL) {
        fprintf(stderr, "MEMCPY\n");
        exit(EXIT_FAILURE);
    }

    fclose(image_file);    
    
    FILE *test = fopen("deneme.png","wb");
    fwrite(image_content, sizeof(char), image_length, test);
    fclose(test);

    strcat(query, "Content-Type: image/png\r\n");
    strcat(query, "Content-Length: ");
    
    char content_length[10];
    sprintf(content_length, "%ld\r\n", image_length-8000);
    strcat(query, content_length);

    int query_len = strlen(query);
    memcpy(query + query_len, image_content, image_length-8000);
    
    
    
}





int main(int argc, const char *argv[])
{
    
    if (argc < 2)
    {
        help_menu(argv[0]);
        exit(1);
    }

    char buffer[15000];
    char *query = calloc(10000 , sizeof(char));
    char *format = "POST %s HTTP/1.1\r\n";
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
        post_data(query,argv[4]);
       
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
    printf("Read");
    read(web_soket,buffer,1200);
    printf("%s",buffer);
}