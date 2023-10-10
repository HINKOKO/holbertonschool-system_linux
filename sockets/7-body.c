#include "rest_api.h"

/* for isspace*/
#include <ctype.h>

char *back_sp(char *token);

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
	char *tok, *val, *saveptr;
	int i;

	strtok_r(raw_request, " ", &saveptr);
	tok = strtok_r(NULL, " ", &saveptr);
	printf("Path: %s\n", tok);

	for (i = 0; i < 7; i++)
		tok = strtok_r(NULL, "\n", &saveptr);
	while (1)
	{
		tok = strtok_r(NULL, "=", &saveptr);
		val = strtok_r(NULL, "&\"", &saveptr);
		if (!val)
			break;
		printf("Body param: \"%s\" -> \"%s\"\n", tok, val);
	}

	return (send_response(client_sd, RESPONSE_200));
}
