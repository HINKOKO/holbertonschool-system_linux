#include "hls.h"

#define MAX_FILES 16
/**
 * 
 * 
 * 
*/

int main(int argc, char *argv[])
{
	int options[1] = {0};
	char *files[MAX_FILES] = {NULL};
	int num_files = 0;

	*files = handle_flags(argc, argv, options);
	show_dir(files, num_files, options);

	
}
