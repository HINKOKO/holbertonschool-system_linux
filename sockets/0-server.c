#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

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
 *
 * When a socket is created with socket(2), it exists in a name
 * space (address family) but has no address assigned to it.
 * We are KIND BOYS, so we assign a port/address to it with 'bind()'
 * 'bind()' => assigns the address specified by addr to the socket referred to
 * by the file descriptor sockfd.
 * It is normally necessary to assign a local address
 * using bind() before a SOCK_STREAM socket may receive connections.
 *
 * Then => listen() marks the socket referred to by sockfd as a passive
 * socket, that is, as a socket that will be used to accept incoming
 * connection requests using accept(2). (Not implemented here)
 *
 * Return: 0 for success, otherwise errno set and returns -1
 */

int server(void)
{
	int sockfd;
	uint16_t port = 12345;
	struct sockaddr_in addr;

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

	while (1)
		;

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
