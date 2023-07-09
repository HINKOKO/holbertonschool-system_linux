#include "objdump.h"

/**
 * map_file - map file into memory
 * convenient to access its content as a huge array in mem
 * @map: double pointer to file's content, that we can move conveniently
 * @filename: path to filename to map
 * Return: size of mapped region
*/

int map_file(void **map, const char *filename)
{
	int fd;
	struct stat sb;
	void *addr;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), -1);
	if (fstat(fd, &sb) == -1)
		return (perror(filename), -1);
	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
		return (perror("mmap"), -1);
	*map = addr;
	return (sb.st_size);
}
