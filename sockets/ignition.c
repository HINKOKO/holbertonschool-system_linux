#include "rest_api.h"

/**
 * start_n_listen - opens an IPv4/TCP socket
 * and listen to traffic on port PORT (8080)
 * Return: 0 for success, 1 otherwise
 */

int start_n_listen(void)
{
	int sockfd;
	struct sockaddr_in server;

	/* disable buffering => todo_api_output is filled */
	setbuf(stdout, NULL);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		handle_error("Socket creation: failure");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
		handle_error("Bind operation: failure");
	if (listen(sockfd, MAX_PENDING) == -1)
		handle_error("Listen: failure");
	printf("Server listening on Port %d\n", ntohs(server.sin_port));
	while (1)
		accept_msg(sockfd);
	close(sockfd);
	/* close returns already 0 on success or -1 on failure */
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
	char buff[BUFSIZ + 1] = {0};
	ssize_t received = 0;
	socklen_t cl_size = sizeof(client);

	client_fd = accept(sockfd, (struct sockaddr *)&client, &cl_size);
	if (client_fd < 0)
		handle_error("Error: client rejected");

	inet_ntop(AF_INET, &client.sin_addr, buff, INET_ADDRSTRLEN);
	printf("Client connected: %s\n", buff);

	/* call to recv() return the number of 'bytes read' */
	buff[0] = 0;
	received = recv(client_fd, buff, BUFSIZ, 0);
	if (received > 0)
	{
		buff[received] = 0;
		printf("Raw request: \"%s\"\n", buff);
		parse_response(buff, client_fd);
	}

	close(client_fd);
	return (EXIT_SUCCESS);
}

/**
 * send_response - send response 200 OK to the client
 * @client_sd: client socket descriptor
 * @response: the string to send back
 * Return: 0 for success, 1 otherwise
 */

int send_response(int client_sd, char *response)
{
	send(client_sd, response, strlen(response), 0);
	return (EXIT_SUCCESS);
}
