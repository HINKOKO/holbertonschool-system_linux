#include "_getline.h"

char *_getline(const int fd)
{
	static char buffer[READ_SIZE];
	static char *p = buffer;
	static int bytes_read;
	char *line = NULL;
	char *tmp = NULL;
	int bytes_used = 0;
	int end_of_line = 0;
	int file_pos = 0;
	int line_start = 0;

	while (!end_of_line)
	{
		if (bytes_read == 0)
		{
			bytes_read = read(fd, buffer, READ_SIZE); 
			p = buffer;
			if (bytes_read == 0 || bytes_read == -1)
			{
				if (line)
				{
					free(line);
					line = NULL;
				}
				return (line);
			}
		}

		/* search for end of line in buffer */
		while (bytes_used < bytes_read && !end_of_line)
		{
			if (p[bytes_used] == '\n')
			{
				end_of_line = 1;
				line_start = file_pos + bytes_used + 1;
			}
			else
			{
				bytes_used++;
			}
		}

		/* allocate memory for line and copy buffer content */
		tmp = realloc(line, file_pos + bytes_used + 1);

		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		line = tmp;
		strncpy(line + file_pos, p, bytes_used);
		file_pos += bytes_used;
		line[file_pos] = '\0';

		/* Update buffer pointer and bytes being read */
		if (end_of_line)
		{
			p += bytes_used + 1;
			bytes_read -= bytes_used + 1;
			bytes_used = 0;
		}
		else
		{
			int line_length = file_pos - line_start; 
			lseek(fd, line_start, SEEK_SET);
			bytes_read = read(fd, buffer, READ_SIZE);
			p = buffer;
			bytes_used = 0;
			file_pos = line_start;
			if (bytes_read == 0 || bytes_read == -1)
			{
				end_of_line = 1;
			}
			else
			{
				/* Append the rest of the line to the buffer */
				while (bytes_used < line_length && bytes_used < bytes_read)
				{
					line[file_pos++] = buffer[bytes_used++];
				}
			}
		}
	}
	return (line);
}
