#include "rest_api.h"

/* for isspace*/
#include <ctype.h>

#define POST_METHOD "POST"
#define GET_ALL "GET"
#define REQUIRED_PATH "/todos"
#define SP " \t"

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

	if (strcasecmp(path, REQUIRED_PATH) ||
			strcasecmp(method, POST_METHOD) && strcasecmp(method, GET_ALL))
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
	if (!strcasecmp(method, POST_METHOD))
	{
		if (!content_len)
			return (send_response(client_sd, RESPONSE_411));
		post_todo(client_sd, body, content_len);
	}
	else if (!strcasecmp(method, GET_ALL))
		get_em_all(client_sd);
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

/**
 * get_em_all - pick all the todos and delivers
 * @client_sd: client sock descriptor
 * Return: 0 success, 1 failure
*/

int get_em_all(int client_sd)
{
	todo_t *node;
	char buf1[BUFSIZ] = {0}, buf2[BUFSIZ] = {0};

	buf2[0] = '[';
	for (node = root; node; node = node->next)
	{
		sprintf(buf2, "{\"" ID "\":%d, \"" TITLE "\":\"%s\",\""
			DESC "\":\"%s\"}", node->id, node->title, node->desc);
	}
	/* add closing bracket */
	*(buf2 + strlen(buf2)) = "]";
	sprintf(buf1, "HTTP/1.1 200 OK" CRLF CONTENT_LENGTH ": %ld" CRLF
		CONTENT_TYPE ": " JSON CRLF CRLF "%s", strlen(buf2), buf2);
	return (send_response(client_sd, buf1));
}
