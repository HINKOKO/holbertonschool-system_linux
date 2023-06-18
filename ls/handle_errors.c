#include "hls.h"

/**
 * handle_error - handle error case of program
 * @dir: pointer to dir
 */

void handle_error(char *dir)
{
	if (errno == ENOENT)
		fprintf(stderr, "hls: cannot access %s: ", dir);
	else if (errno == EACCES)
		fprintf(stderr, "hls: cannot open directory %s", dir);
	perror("");
}
