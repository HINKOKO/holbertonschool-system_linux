#ifndef __TCP_LIFE__
#define __TCP_LIFE__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

#define PORT 18000
#define SA const struct sockadrr
#define MAXLINE 4096

void error_n_die(const char *fmt, ...);
char *bin_to_hex(const unsigned char *input, size_t len);


#endif /* __TCP_LIFE__ */
