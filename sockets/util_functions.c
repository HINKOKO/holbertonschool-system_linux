#include "rest_api.h"

#include <ctype.h>

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
