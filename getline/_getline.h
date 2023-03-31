#ifndef __CUSTOMGETLINE__
#define __CUSTOMGETLINE__

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_SIZE 2568

/**
 * struct s_buffer - struct for reading
 * and storing chunks of char/bytes/lines coming from the fd
 * @buffer: the buffer to store our chunks
 * @p: pointer to buffer
 * @bytes_read: the chars/data we will read
*/

typedef struct s_buffer
{
	char buffer[READ_SIZE];
	int bytes_read;
	char *p;
} t_buffer;


/* function for our homemade getline */
char *_getline(const int fd);
char *read_line(int fd);
t_buffer *init_buffer(void);







#endif /* __CUSTOMGETLINE__ */
