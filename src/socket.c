#include "../include/socket.h"



int get_socket(const char *const host_name)
{
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
    host = gethostbyname(host_name);
    struct in_addr **addr_list;
    addr_list = (struct in_addr **) host->h_addr_list;
    
    
	
    if(inet_pton(AF_INET, inet_ntoa(*addr_list[0]), &serveraddr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    ///web sunucusunun bağlantı portu
    serveraddr.sin_port = htons((unsigned short) 80);

    if (connect(web_soket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Client: connect() - Failed to connect.\n");
        return -1;
    }

    return web_soket;
}