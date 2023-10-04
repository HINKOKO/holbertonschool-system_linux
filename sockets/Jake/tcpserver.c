#include "tcp.h"

#define MAX_PENDING 10

/**
 * main - entry point
 * 
*/

int main(int argc, char **argv)
{
	int listen_fd, conn_fd, n;
	struct sockaddr_in servaddr;
	uint8_t buff[MAXLINE+1];
	uint8_t recvline[MAXLINE + 1];

	(void)argc;
	(void)argv;

	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error_n_die("Failed to create socket");
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	/* Bind step */
	if ((bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		error_n_die("Error when binding");
	
	if (listen(listen_fd, MAX_PENDING) == -1)
		error_n_die("Error at listening step");
	
	for (;;) {
		struct sockaddr_in addr;
		socklen_t addr_len;
		char client_address[MAXLINE + 1];

		printf("Waiting for a connection on port: %d\n", PORT);
		fflush(stdout);
		/* accept() if filling for us the two last argument ! Yiihay */
		conn_fd = accept(listen_fd, (struct sockaddr *)&addr, &addr_len); 
		/* accept() 'blocks' until an incoming connection arrives */
		/*when the address comes back , it's gonna be in network format, so convert it */

		inet_ntop(AF_INET, &addr, client_address, MAXLINE); /* inet_ntop ===> Network to Presentation format basically*/
		printf("Client connection: %s\n", client_address);

		memset(recvline, 0, MAXLINE);
		/* zero'ed out the receiving buffer */
		/* and read the client's message */
		while ((n = read(conn_fd, recvline, MAXLINE - 1)) > 0)
		{
			fprintf(stdout, "\n%s\n\n%s\n", bin_to_hex(recvline, n), recvline);
			/* detect the end of message */
			if (recvline[n - 1] == '\n')
				break;
			
			memset(recvline, 0, MAXLINE);
		}
		if (n < 0)
			error_n_die("read operation error");
		/* send a message */
		snprintf((char *)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHelloKiki");
		write(conn_fd, (char *)buff, strlen((char *)buff));
		close(conn_fd);
	}
	exit(EXIT_SUCCESS);
}
