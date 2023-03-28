#include "_getline.h"

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor, unique id to represent file
 * or I/O stream to read from (or write to)
 * Return: null-terminated string // newline character not included
*/

char *_getline(const int fd)
{
	static char buffer[READ_SIZE];
	static char *p = buffer;
	static int bytes_read;
	char *line, *tmp = NULL;
	int bytes_used, end_of_line = 0;

	while (!end_of_line)
	{
		if (bytes_read == 0)
		{
			bytes_read = read(fd, buffer, READ_SIZE);
			p = buffer;
			if (bytes_read == 0)
				return (NULL);
		}
		/* search for end of line in buffer */
		while (bytes_used < bytes_read && !end_of_line)
		{
			if (p[bytes_used] == '\n')
				end_of_line = 1;
			else
				bytes_used++;
		}
		/* allocate memory for line and copy buffer content */
		*tmp = realloc(line, bytes_used + 1);

		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		line = tmp;
		strncpy(line + strlen(line), p, bytes_used);
		line[bytes_used + strlen(line)] = '\0';

		/* Update buffer pointer and bytes being read */
		p += bytes_used + 1;
		bytes_read -= bytes_used + 1;
		bytes_used = 0;
	}
	return (line);
}
