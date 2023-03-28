#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor, unique id to represent file
 * or I/O stream to read from (or write to)
 * Return: null-terminated string // newline character not included
*/

char *_getline(const int fd)
{
	char *buff = malloc(READ_SIZE + 1);
	int bytes_read = 0;

	while (1) 
	{
		int bytes = read(fd, buff + bytes_read, READ_SIZE);
		if (bytes == -1 || bytes == 0)
		{
			break;
		}

		bytes_read += bytes;

		if (buff[bytes_read - 1] == '\n')
		{
			break;
		}

		buff = realloc(buff, bytes_read + READ_SIZE + 1);
	}

	buff[bytes_read] = '\0';
	return (buff);
}
