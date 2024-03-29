#include "rest_api.h"

/* for isspace*/
#include <ctype.h>

#define REQUIRED_METHOD "POST"
#define REQUIRED_PATH "/todos"
#define SP " \t"
#define POST_SPACE 17
#define COLOR "\033[4m"
#define RESET "\033[0m"

static int ids;
static todo_t *root;

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
	char *start, *method, *path, *header, *body, *key, *val;
	char *outer, *inner;
	short content_len = 0;

	body = strstr(raw_request, CRLF CRLF);
	if (strlen(body))
	{
		*body = 0;
		body += strlen(CRLF CRLF);
	}
	start = strtok_r(raw_request, CRLF, &outer);
	method = strtok(start, SP);
	path = strtok(NULL, SP);
	path = strtok(path, "?");

	if (strcasecmp(method, REQUIRED_METHOD) || strcasecmp(path, REQUIRED_PATH))
		return (send_response(client_sd, RESPONSE_404));

	printf("Path: %s\n", path);
	header = strtok_r(NULL, CRLF, &outer);
	while (header != NULL)
	{
		key = strtok_r(header, ":", &inner);
		val = back_sp(strtok_r(NULL, CRLF, &inner));
		if (!strcasecmp(key, CONTENT_LENGTH))
			content_len = atoi(val);
		header = strtok_r(NULL, CRLF, &outer);
	}
	if (!content_len)
		return (send_response(client_sd, RESPONSE_411));

	post_todo(client_sd, body, content_len);
	return (EXIT_SUCCESS);
}

/**
 * post_todo - after validity check in parse_response
 * effectively post the todo in our super volatile RAM Database
 *
 * @client_sd: client socket descriptor
 * @body: the raw request body to be parsed/cooked
 * @content_length: the content length
 *
 * Return: 0 success, otherwise appropriate message/error code
 */

int post_todo(int client_sd, char *body, short content_length)
{
	char *body_params, *param, *val, *outer, *inner;
	char *title = NULL, *desc = NULL;
	char buf1[1024] = {0}, buf2[1024] = {0};
	todo_t *todo, *tmp;

	body[content_length] = 0;
	body_params = strtok_r(body, "&", &outer);
	while (body_params)
	{
		param = strtok_r(body_params, "=", &inner);
		val = strtok_r(NULL, "=", &inner);
		if (!strcasecmp(param, TITLE))
			title = val;
		else if (!strcasecmp(param, DESC))
			desc = val;
		body_params = strtok_r(NULL, "&", &outer);
	}
	if (!title || !desc)
		return (send_response(client_sd, RESPONSE_422));
		
	todo = calloc(1, sizeof(*todo));
	todo->id = ids++;
	todo->desc = strdup(desc);
	todo->title = strdup(title);
	if (!root)
		root = todo;
	else
	{
		tmp = root;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = todo;
	}
	sprintf(buf2, "{\"" ID "\":%d,\"" TITLE "\":\"%s\",\""
		DESC "\":\"%s\"}", ids - 1, title, desc);
	sprintf(buf1, RESPONSE_201 CRLF CONTENT_LENGTH ": %ld" CRLF
		CONTENT_TYPE ": " JSON CRLF CRLF "%s", strlen(buf2), buf2);
	send_response(client_sd, buf1);
	return (0);
}
