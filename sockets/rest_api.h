#ifndef __SOCKETS_API__
#define __SOCKETS_API__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
#define MAX_PENDING 10
#define MAXLINE 4096

#define CRLF "\r\n"

#define RESPONSE_200_CORE "HTTP/1.1 200 OK"
#define RESPONSE_200 (RESPONSE_200_CORE CRLF CRLF)

#define handle_error(msg)   \
	do                      \
	{                       \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

int start_n_listen(void);
int accept_msg(int sockfd);
int parse_response(char *raw_request, int client_fd);

#endif /* __SOCKETS_API__ */
