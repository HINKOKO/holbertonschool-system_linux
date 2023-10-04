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


#define PORT 80
#define MAX_CHUNK 4096 /* buffer len */
#define SA struct sockaddr


/**
 * error_n_die - variadic function for handling error
 * cases/messages accroding to situation
 * @fmt: pointer to arguments
 * 
*/


void error_n_die(const char *fmt, ...)
{
	int errno_save;
	va_list list;

	errno_save = errno;

	va_start(list, fmt);
	vfprintf(stdout, fmt, list);
	fprintf(stdout, "\n");
	fflush(stdout);

	if (errno_save != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(list);
	/* this is an error function , so exit with an error */
	exit(EXIT_FAILURE);
}

/**
 * main- entry point of program
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 success, 1 otherwise
*/

int main(int argc, char **argv)
{
	int sockfd, n;
	int sendbytes;
	struct sockaddr_in servaddr;
	char sendline[MAX_CHUNK];
	char recvline[MAX_CHUNK];

	if (argc < 2)
		error_n_die("Usage: %s <server address (IP)>", argv[0]);
	
	if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_n_die("Sorry, Failed to create a socket.");
	
	/* bzero => kind of a memset  */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = 	AF_INET;
	servaddr.sin_port = htons(PORT); /* htons is host to network short */
	/* Convert to network byte-order, ensures that computers with diff bytes order == Okay*/

	/* convert IPv4 (and 6 too) addresses from text to bin format */
	/* translate address */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		error_n_die("inet_pton error for %s", argv[1]);
	
	/* Let's go for connection to the server provided as argv[1] */

	if (connect(sockfd, (SA *)&servaddr, (socklen_t)(sizeof(servaddr))) < 0)
		error_n_die("Failed to connect to socket!");
	
	/* connection successful, prepare the message */
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
	sendbytes = strlen(sendline);

	/* write to the socket */
	if (write(sockfd, sendline, sendbytes) != sendbytes)
		error_n_die("error while writing through the socket");
	
	while ((n = read(sockfd, recvline, MAX_CHUNK - 1)) > 0)
	{
		printf("%s", recvline);
		memset(recvline, 0, MAX_CHUNK);
	}
	if (n < 0)
		error_n_die("Error while reading");
	
	exit(EXIT_SUCCESS);
}
