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
	char *start, *header, *key, *val, *outer, *inner;

	/* parse into lines */
	/* here start gives us the begining of Request-Line*/
	/* we got method-token, Request-URI-TOken, protocol-version*/
	start = strtok_r(raw_request, CRLF, &outer);
	/* always a CRLF after the verb/target/http version */
	header = strtok_r(NULL, CRLF, &outer);

	/* loop through header */
	while (header != NULL)
	{
		key = strtok_r(header, ":", &inner);
		val = back_sp(strtok_r(NULL, CRLF, &inner));
		printf("Header: \"%s\" -> \"%s\"\n", key, val);
		header = strtok_r(NULL, CRLF, &outer);
	}
	return (send_response(client_sd, RESPONSE_200));
	(void)start;
}

/**
 * back_sp - remove trailing whitespace in front of field value
 * @token: the field value to work on
 * Return: fixed token
 */

char *back_sp(char *token)
{
	char *end;
	/* remove leading space */
	while (isspace((unsigned char)*token))
		token++;

	end = token + strlen(token) - 1;
	while (end > token && isspace((unsigned char)*end))
		end--;

	*(end + 1) = 0;

	return (token);
}
