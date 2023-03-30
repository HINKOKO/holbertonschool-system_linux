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
 * struct line_s - struct for storing lines/bytes read
 * on a given file descriptor
 * @fd: file descriptor to open/read
 * @buffer: buffer for storing lines being read
 * @bytes: line read in bytes
 * @next: pointer to the next node/struct
*/


/* function for our homemade getline */
char *_getline(const int fd);
int _strlen(const char *str);



#endif /* __CUSTOMGETLINE__ */
