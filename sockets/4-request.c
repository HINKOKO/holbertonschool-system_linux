#include "rest_api.h"

/**
 * main - entry point
 * Return: 0 for sucess, 1 otherwise
 */

int main(void)
{
	return (start_n_listen());
}

/**
 * parse_response - parse the response header HTTP using
 * good old strtok() to split the header strings
 * @raw_request: the raw request we got back
 * @client_sd: the client socket descriptor
 * Return: 0 success, 1 otherwise
 */

int parse_response(char *raw_request, int client_sd)
{
	char *DELIMS = " \t\r\n";
	char *method, *path, *version;

	method = strtok(raw_request, DELIMS);
	path = strtok(NULL, DELIMS);
	version = strtok(NULL, DELIMS);

	printf("Method: %s\nPath: %s\nVersion: %s\n", method, path, version);
	return (send_response(client_sd, RESPONSE_200));
}
