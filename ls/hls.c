#include "hls.h"

/**
 * overload - modifies display if overload
 * @entry: pointer to directory entry
 * @options: option array
 */

void overload(struct dirent *entry, int *options)
{
	if (options[2] == 1)
		one_by_line(entry->d_name, options);
	else
	{
		if (options[3] == 1 && _strcmp(entry->d_name, ".") &&
			_strcmp(entry->d_name, ".."))
			one_by_line(entry->d_name, options);
		else if (entry->d_name[0] != '.')
			one_by_line(entry->d_name, options);
	}
}
/**
 * display_with_options - handle options and displays
 * as requested in input
 * @nodes: node of linked list options
 * @opt: options 'flag' array
 * @multi: flag int to on/off multi arg
 */

void display_with_options(opt_t *nodes, int *opt, int multi)
{
	struct dirent *entry;
	DIR *dir;

	dir = opendir(nodes->str);

	if (multi == 1 && errno == 0)
		printf("%s :\n", nodes->str);
	if (dir)
	{
		entry = readdir(dir);
		while (entry)
		{
			if (opt[1] == 1)
			{
				print_long(entry);
				opt[0] = 1;
			}
			else
				overload(entry, opt);
			entry = readdir(dir);
		}
		if (nodes->next || errno != 0)
			printf("\n");
	}
	if (errno)
		handle_error(nodes->str);
	if (opt[0] != 1 && errno == 0)
		printf("\n");
	closedir(dir);
}

/**
 * display_local - display current directory '.'
 * when 'ls' launched with no desired path
 * @head: linked list of args
 * @opt: option array
 */

void display_local(char *head, int *opt)
{
	struct dirent *entry;
	DIR *dir;

	dir = opendir(head);
	if (dir)
	{
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (opt[1] == 1)
			{
				print_long(entry);
				opt[0] = 1;
			}
			else
			{
				overload(entry, opt);
			}
			entry = readdir(dir);
		}
	}
	if (opt[0] != 1)
		printf("\n");
	closedir(dir);
}

/**
 * display_dir - check if options are passed and display
 * directory accrodingly
 * @nodes: node of the linked list of args
 * @options: options array
 */

void display_dir(opt_t *nodes, int *options)
{
	opt_t *head = nodes;
	int multi = 0;

	if (head == NULL)
	{
		display_local(".", options);
		return;
	}
	/* if arguments provided */
	if (head->next)
		multi = 1;
	while (head)
	{
		display_with_options(head, options, multi);
		head = head->next;
	}
}
