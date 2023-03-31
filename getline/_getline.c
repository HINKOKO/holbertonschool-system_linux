#include "_getline.h"

/**
 * _getline - reads entire lines from fd
 * @fd: file descriptor to read from
 * Return: pointer to strings chars
*/

char *_getline(const int fd)
{
	static line_t *lines;
	line_t *new_chunk;
	char *draft;
	int bytes_read;

	if (fd == -1)
	{
		for (new_chunk = lines; new_chunk != NULL; new_chunk = new_chunk->next)
		{
			free(new_chunk->buff);
			free(new_chunk);
		}
		return (NULL);
	}
	for (new_chunk = lines; new_chunk != NULL; new_chunk = new_chunk->next)
	{
		if (new_chunk->fd == fd)
		{
			if (new_chunk->bytes <= 0)
				new_chunk->bytes = read(fd, new_chunk->buff, READ_SIZE);
			return (cook_line(new_chunk));
		}
	}
	draft = malloc(sizeof(char) * READ_SIZE);
	bytes_read = read(fd, draft, READ_SIZE);
	if (bytes_read <= 0)
	{
		free(draft);
		return (NULL);
	}
	new_chunk = malloc(sizeof(line_t));
	if (!new_chunk)
		return (NULL);
	new_chunk->fd = fd;
	new_chunk->bytes = bytes_read;
	new_chunk->buff = draft;
	new_chunk->next = lines;
	lines = new_chunk;
	return (cook_line(lines));
}
/**
 * cook_line - to handle newline // chars remaining in buffer
 * @lines: pointer to struct holding chunk of chars
 * Return: pointer to start of line of chars being handled
*/

char *cook_line(line_t *lines)
{
	int i, j, size = 0, bytes_copy = 0;
	char *line = NULL, *tmp;

	while (lines->bytes > 0)
	{
		if (size < bytes_copy + lines->bytes + 1)
		{
			size += lines->bytes + 1;
			tmp = malloc(sizeof(char) * size);
			if (!tmp)
			{
				free(line);
				return (NULL);
			}
			memcpy(tmp, line, bytes_copy);
			memset(tmp + bytes_copy, '\0', size - bytes_copy);
			free(line); /* free the empty line */
			line = tmp; /* set new address */
		}
		for (i = 0; i < READ_SIZE; i++)
			if (lines->buff[i] == '\n')
			{
				lines->buff[i++] = '\0';
				lines->bytes -= i;
				memcpy(line + bytes_copy, lines->buff, i);
				/* don't loose remaining chars ==> move them */
				for (j = 0; i < READ_SIZE; j++, i++)
					lines->buff[j] = lines->buff[i];
				/* continue loop */
				for (; j < READ_SIZE; j++)
					lines->buff[j] = '\0'; /* remaining buff properly set */
				return (line);
			}
		/* if no newlines found just copy what's being read */
		memcpy(line + bytes_copy, lines->buff, lines->bytes);
		bytes_copy += lines->bytes;
		lines->bytes = read(lines->fd, lines->buff, READ_SIZE);
		}
		return (line);
}
