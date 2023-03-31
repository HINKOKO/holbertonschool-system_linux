#include "_getline.h"

/**
 * init_buffer - init a new buffer for storing chunks read
 * Return: struct defined in header
*/

t_buffer *init_buffer(void)
{
	static t_buffer buffer = { {0}, 0, buffer.buffer };

	return (&buffer);
}

/**
 * read_line - read lines from file descritor/handle newlines
 * @fd: file descriptor to read from
 * Return: pointer to characters line
*/

char *read_line(int fd)
{
	t_buffer *buffer = init_buffer();
	char *line = NULL;
	char *tmp = NULL;
	int bytes_used = 0;
	int end_of_line = 0;

	while (!end_of_line)
	{
		if (buffer->bytes_read <= 0)
		{
			buffer->bytes_read = read(fd, buffer->buffer, READ_SIZE);
			buffer->p = buffer->buffer;
			if (buffer->bytes_read <= 0 || buffer->bytes_read == -1)
				return (NULL);
		}
		/* look for end of line in buffer */
		while (bytes_used <= buffer->bytes_read && !end_of_line)
		{
			if (buffer->p[bytes_used] == '\n' || buffer->p[bytes_used] == '\0')
				end_of_line = 1;
			else
				bytes_used++;
		}
		/* then allocate memory for line and copy buffer content */
		tmp = realloc(line, bytes_used + 1);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		line = tmp;
		strncpy(line, buffer->p, bytes_used);
		line[bytes_used] = '\0';
		/* Update buffer */
		buffer->p += bytes_used + 1;
		buffer->bytes_read -= bytes_used + 1;
		bytes_used = 0;
	}
	return (line);
}

/**
 * _getline - 'main' function
 * @fd: file descriptor
 * Return: pointer to line of chars
*/

char *_getline(const int fd)
{
	return (read_line(fd));
}
