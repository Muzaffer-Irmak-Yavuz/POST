#include "../include/help.h"



void help_menu(const char *const name)
{
    printf("\nUsage %s [options] [ <host name> <path to post data> <data>]\n",name);
    printf("Options:\n\n");
    printf("%s      Display this information\n","-h");
    printf("%s      Send text\n","-t");
}
