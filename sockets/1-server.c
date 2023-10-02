#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PENDING 10
#define handle_error(msg)   \
	do {                       \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)


/**
 * server - opens a IPv4/TCP socket
 * listen to traffic on port 12345
 *
 * Return: 0 for success, otherwise errno set and returns -1
 */

int server(void)
{
	int sockfd, client_fd;
	uint16_t port = 12345;
	struct sockaddr_in addr, client;
	socklen_t client_size = sizeof(struct sockaddr_in);

	/* Create the socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		handle_error("socket");
	/* Give the socket a name , and bin to port number */
	addr.sin_family = AF_INET;
	/* htons function used to convert a 16-bit quantity */
	/* from host byte order to network byte order */
	/* => ensure the port number is in the correct byte order for network com */
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	/* address to accept any incoming messages */
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		handle_error("bind");

	/* Listening step */
	if (listen(sockfd, MAX_PENDING) == -1)
		handle_error("listen");

	printf("We opened a socket and we are now listening on port => %d\n",
		ntohs(addr.sin_port));

	client_fd = accept(sockfd, (struct sockaddr *)&client, &client_size);
	if (client_fd == -1)
		handle_error("accept");
	if (getpeername(sockfd, (struct sockaddr *)&addr, (socklen_t *)sizeof(addr)))
		printf("Client accepted on port: %s\n", inet_ntoa(client.sin_addr));

	if (close(sockfd) != 0 || close(client_fd) != 0)
		handle_error("close");

	return (EXIT_SUCCESS);
}

/**
 * main - entry point, just trigger to server() function
 * Return: 0 success, -1 otherwise
*/


int main(void)
{
	return (server());
}
