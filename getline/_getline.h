#ifndef __CUSTOMGETLINE__
#define __CUSTOMGETLINE__

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define READ_SIZE 10

/* little custom getline */
char *_getline(const int fd);


#endif /* __CUSTOMGETLINE__ */
