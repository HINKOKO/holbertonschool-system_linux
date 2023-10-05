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

#define PORT 12345
#define MAX_PENDING 10
#define MAXLINE 4096

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
 * accept_msg - accept a message from connected client
 * @sockfd: the socket fd we want to accept message from
 * Return: 0 for success, 1 otherwise
 */

int accept_msg(int sockfd)
{
	int client_fd;
	struct sockaddr_in client;
	char buff[MAXLINE + 1];
	ssize_t received = 0;
	socklen_t cl_size = sizeof(client);

	client_fd = accept(sockfd, (struct sockaddr *)&client, &cl_size);
	if (client_fd < 0)
		error_n_die("Error: client rejected");
	inet_ntop(PF_INET, &client.sin_addr, buff, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buff);

	/* call to recv() returns the number of 'bytes read' */
	received = recv(client_fd, buff, MAXLINE, 0);
	if (received < 0)
		error_n_die("Nothing received or lost along the path");

	buff[received] = 0;
	printf("Message received: \"%s\n\"", buff);
	close(client_fd);
	return (EXIT_SUCCESS);
}

/**
 * main - entry point, just trigger to server() function
 * Return: 0 success, 1 for failure
 * Your program must:
 * - Accept an entering connection
 * - Print the IP address of the connected client
 * - Wait for an incoming message from the connected client
 * - Print the received message
 * - Close the connection with the client
 * - Exit
 */

int main(void)
{
	struct sockaddr_in servaddr;
	int sockfd;
	unsigned short port = 12345;

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error_n_die("Failed to create socket!");
	servaddr.sin_family = PF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
		error_n_die("Error: Binding stage failure");
	if (listen(sockfd, MAX_PENDING) == -1)
		error_n_die("Error: listen on port socket failure");
	printf("Server listening on port %d\n", ntohs(servaddr.sin_port));
	accept_msg(sockfd);
	close(sockfd);
	return (EXIT_SUCCESS);
}
