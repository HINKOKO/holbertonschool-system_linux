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
	char *path, *query, *key, *val, *query_tok, *inner_tok;

	strtok(raw_request, DELIMS);
	path = strtok(NULL, DELIMS);
	path = strtok_r(path, "?", &query_tok);
	printf("Path: %s\n", path);

	query = strtok_r(NULL, "&", &query_tok);
	while (query != NULL)
	{
		key = strtok_r(query, "=", &inner_tok);
		val = strtok_r(NULL, "=", &inner_tok);
		printf("Query: \"%s\" -> \"%s\"\n", key, val);
		query = strtok_r(NULL, "&", &query_tok);
	}
	return (send_response(client_sd, RESPONSE_200));
}
