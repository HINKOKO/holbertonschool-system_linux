#ifndef __CUSTOMGETLINE__
#define __CUSTOMGETLINE__

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_SIZE 1024

/**
 * struct line_s - struct of linked list to store our chunks
 * of lines being read
 * @fd: file descriptor to read from
 * @bytes: bytes being read
 * @buff: pointer to buff eating chars
 * @next: pointer to next struct/node
*/

typedef struct line_s
{
	int fd;
	int bytes;
	char *buff;
	struct line_s *next;
} line_t;


/* function for our homemade getline */
char *_getline(const int fd);
char *cook_line(line_t *lines);


#endif /* __CUSTOMGETLINE__ */
