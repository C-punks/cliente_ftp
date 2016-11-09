#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define BUF_SIZE 4096

void fatal(char* string);