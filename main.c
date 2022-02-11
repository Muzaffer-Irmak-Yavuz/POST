#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>

void addpost(char* str1, const char* data)
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
    if ((argc != 4))
    {
        fprintf(stderr,"Usage %s <host name> <url> <text>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    /// Soket Açma.
    int web_soket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    ///web sunucu bilgilerinin tutulduğu değişken
    struct sockaddr_in serveraddr;
    ///host yapısı
    struct hostent *host;
    ///sunucu adresinden IP adresine ulaşma


    ///host içeriği alınamazsa hata
    
    ///Bağlantı aşaması

    memset(&serveraddr, 0, sizeof(serveraddr));
    ///web sunucusunun bağlantı ailesi
    serveraddr.sin_family = AF_INET;
    ///web sunucusunun bağlantı adresi
    
    //inet_pton(AF_INET, "216.239.38.21", &serveraddr.sin_addr);
    host = gethostbyname(argv[1]);
    struct in_addr **addr_list;
    addr_list = (struct in_addr **) host->h_addr_list;
    
    
	
    if(inet_pton(AF_INET, inet_ntoa(*addr_list[0]), &serveraddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    ///web sunucusunun bağlantı portu
    serveraddr.sin_port = htons((unsigned short) 80);
    ///bağlantı açma fonksiyonu
    if (connect(web_soket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Client: connect() - Failed to connect.\n");
    }
    else{
        char buffer[1200];
        char *query = calloc(200 , sizeof(char));
        char *format = "POST %s HTTP/1.0\r\n";
        sprintf(query,format,argv[2]);
        //strcpy(query,"POST http://ptsv2.com/t/kshse-1644423543/post HTTP/1.0\r\n");
        addpost(query, argv[3]);
        strcat(query,"\r\n\r\n");
        write(web_soket,query,strlen(query));
        read(web_soket,buffer,1200);
        printf("%s",buffer);
    }
}