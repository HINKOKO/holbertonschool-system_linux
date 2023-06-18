#include "hls.h"

/**
 * print_long - print in long format the files
 * with drwx- format and time and right
 * @entry: pointer to directory entry structure
 */

void print_long(struct dirent *entry)
{
	struct stat fileStat = {0};
	struct group *grp;
	struct passwd *user;
	char time[24];

	_strncpy(time, ctime(&fileStat.st_mtime), 24);
	lstat((*entry).d_name, &fileStat);

	printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

	user = getpwuid(fileStat.st_uid);
	grp = getgrgid(fileStat.st_gid);

	printf(" %lu %s %s %li %s %s\n", fileStat.st_nlink, (*user).pw_name,
		   (*grp).gr_name, (intmax_t)fileStat.st_size, time, (*entry).d_name);
}

/**
 * one_by_line - displays according to -1 option
 * @dir: pointer to dir entries
 * @options: options int array
 */

void one_by_line(char *dir, int *options)
{
	if (options[0] == 1)
		printf("%s\n", dir);
	else
		printf("%s ", dir);
}
