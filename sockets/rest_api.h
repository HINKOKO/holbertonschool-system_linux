#ifndef __SOCKETS_API__
#define __SOCKETS_API__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080
#define MAX_PENDING 10
#define MAXLINE 4096

/* Macros for dealing with HTTP format */
#define CRLF "\r\n"
#define RESPONSE_200_CORE "HTTP/1.1 200 OK"
#define RESPONSE_200 (RESPONSE_200_CORE CRLF CRLF)
#define RESPONSE_201 "HTTP/1.1 201 Created"
/*classic not found*/
#define RESPONSE_404 "HTTP/1.1 404 Not Found\r\n\r\n"
/* Content-Length is a required header */
#define RESPONSE_411 "HTTP/1.1 411 Length Required\r\n\r\n"
/* Missing either title or description body parameters */
#define RESPONSE_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"
#define TITLE "title"
#define DESC "description"
#define CONTENT_TYPE "Content-Type"
#define JSON "application/json"
#define CONTENT_LENGTH "Content-Length"

#define ID "id"
#define TITLE "title"
#define DESC "description"

#define handle_error(msg)   \
	do                      \
	{                       \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

/**
 * todo - todo's represented as node of a Linked list
 * @id: identify todo's by a unique id
 * @title: title of the todo
 * @desc: description of the todo
 * @next: pointer to next todo
 */

typedef struct todo
{
	int id;
	char *title;
	char *desc;
	struct todo *next;
} todo_t;

/**
 * struct todo_info - overview of todo node
 *
 */

typedef struct todo_info
{
	todo_t *head;
	todo_t *tail;
} list_t;

int start_server(void);
int accept_msg(int sockfd);
int send_response(int client_sd, char *response);
int parse_response(char *raw_request, int client_fd);
char *back_sp(char *token);
/* starting to do the todos */
int post_todo(int client_sd, char *body, short content_length);
int client_response(int client_sd, short len, todo_t *todo);

/* Functions for REST_API */
int start_n_listen(void);
int receiver(int sockfd, char *buffer);

todo_t *posting_todo(char *buff, list_t *list);
void post_response(int client_sd, list_t *list);
void parse_req(char *buff, int client_sd, list_t *list);
int parse_error(char *buff, int client_sd);

#endif /* __SOCKETS_API__ */
