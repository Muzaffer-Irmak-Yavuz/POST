#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int get_socket(const char *const host_name);

#endif