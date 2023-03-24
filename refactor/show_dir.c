#include "hls.h"

/**
 * 
 * 
 * 
*/

void show_dir(char *files[], int num_files, int *options)
{
	int mult = 0, i = 0;

	if (num_files == 0) {
		display_current(".", options);
		return;
	}

	if (num_files > 1)
		mult = 1;

	for (i = 0; i < num_files; i++)
		show_options(files[i], options, mult);
}

/**
 * 
 * 
 * 
*/

void show_options(char *files[], int count, int *options)
{
	int i;
	int mult = 0;

	if (count > 1) mult = 1;

	for (i = 0; i < count; i++)
	{
		DIR *dir;
		struct dirent *read;
		dir = opendir(files[i]);

		if (mult == 1 && errno == 0)
			printf("%s :\n", files[i]);
		if (dir != NULL)
		{
			read = readdir(dir);
			while (read != NULL)
			{
				if (options[0] == 1) print_1(read->d_name, options);
				else print_classic(read);
				read = readdir(dir);
			}
			if (i < count - 1 || errno != 0)
				printf("\n");
			closedir(dir);
		}
		if (errno != 0) manage_errors(files[i]);
	}
}



