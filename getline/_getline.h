#ifndef __CUSTOMGETLINE__
#define __CUSTOMGETLINE__

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define READ_SIZE 1024




/* function for our homemade getline */
char *_getline(const int fd);
int _strlen(const char *str);



#endif /* __CUSTOMGETLINE__ */
