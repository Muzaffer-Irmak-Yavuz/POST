#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>



int main()
{
    /// Soket Açma.
    int web_soket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    ///web sunucu bilgilerinin tutulduğu değişken
    struct sockaddr_in web_sunucu;
    ///host yapısı
    struct hostent *host;
    ///sunucu adresinden IP adresine ulaşma


    ///host içeriği alınamazsa hata
    if(host==NULL)
        return 3;
    ///Bağlantı aşaması

    memset(&web_sunucu, 0, sizeof(web_sunucu));
    ///web sunucusunun bağlantı ailesi
    web_sunucu.sin_family = AF_INET;
    ///web sunucusunun bağlantı adresi
    
    inet_pton(AF_INET, "216.239.38.21", &web_sunucu.sin_addr);
    ///web sunucusunun bağlantı portu
    web_sunucu.sin_port = htons((unsigned short) 80);
    ///bağlantı açma fonksiyonu
    if (connect(web_soket, (struct sockaddr *) &web_sunucu, sizeof(web_sunucu)) < 0)
    {
        printf("Client: connect() - Failed to connect.\n");
    }
    else{
        char buffer[1200];
        char *query = "POST http://ptsv2.com/t/kshse-1644423543/post HTTP/1.0\r\nContent-Length: 0\r\n\r\n";
        write(web_soket,query,strlen(query));
        read(web_soket,buffer,1200);
        printf("%s",buffer);
    }
}