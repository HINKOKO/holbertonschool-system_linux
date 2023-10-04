#include "tcp.h"

/**
 * error_n_die - variadic func to handle error messages
 * @fmt: format string specifier
*/

void error_n_die(const char *fmt, ...)
{
	int errno_save; /* save the errno */
	va_list l;

	errno_save = errno;
	va_start(l, fmt);
	vfprintf(stdout, fmt, l);
	fprintf(stdout, "\n");
	fflush(stdout);

	if (errno_save)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(l);
	exit(EXIT_FAILURE);
}

/**
 * bin_to_hex - takes a string of bytes, converts them to
 * hexadecimal representation, help for debugging
 * @input: the string to convert
 * @len: len of string to be converted
 * Return: the converted string, or NULL on failure
*/

char *bin_to_hex(const unsigned char *input, size_t len)
{
	char *res;
	char *hexits = "0123456789ABCDEF";
	int res_len = 0;
	size_t i;

	if (!input || len <= 0)
		return (NULL);
	
	/* we need to hexits 'char' by /char + 'space' + NULL terminator */
	res_len = (len * 3) + 1;
	res = malloc(res_len);
	bzero(res, res_len);

	for (i = 0; i < len; i++)
	{
		res[i * 3] = hexits[input[i] >> 4];
		res[(i * 3) + 1] = hexits[input[i] & 0x0F];
		res[(i * 3) + 2] = ' '; /* for readability */
	}
	/* help us to see if there's unprintable character along the way */
	return (res);
}
