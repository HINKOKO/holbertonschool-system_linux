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

/**
 * error_n_die - error management function
 * call to handle and display error message
 * @fmt: format string specifier
 */

void error_n_die(const char *fmt, ...)
{
	int err_save;
	va_list list;

	err_save = errno;
	va_start(list, fmt);
	vfprintf(stdout, fmt, list);
	fprintf(stdout, "\n");
	fflush(stdout);

	if (err_save != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", err_save, strerror(err_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(list);
	exit(EXIT_FAILURE);
}

/**
 * main - entry point, just trigger to server() function
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 success, 1 for failure
 */

int main(int argc, char **argv)
{
	struct sockaddr_in servaddr;
	int sockfd;
	struct hostent *hostinfo;

	if (argc < 3)
		error_n_die("Usage: %s <host> <port>", argv[0]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error_n_die("Error creating socket");

	hostinfo = gethostbyname(argv[1]);
	if (!hostinfo)
		error_n_die("Unknown host at this stage of knowledge in the Universe");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[0]),
			  &servaddr.sin_addr);

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		error_n_die("Failed to connect the client via socket");

	fprintf(stdout, "Connected to: %s:%s\n", argv[1], argv[2]);
	close(sockfd);
	return (EXIT_SUCCESS);
}
