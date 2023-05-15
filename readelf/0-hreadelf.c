#include "hreadelf.h"

/**
 * pick_fd - returns the fd
 * @filename: filename to find the fd
 * Return: the file descriptor, NULL if invalid
*/

FILE *pick_fd(char *filename)
{
	FILE *fd;

	fd = fopen(filename, "r");
	if (!fd)
	{
		fprintf(stderr, "%s: Error: No such file or directory\n", filename);
		return (NULL);
	}
	return (fd);
}

/**
 * check_args - check that args are valids
 * @argc: argument count
 * @argv: array of argument
 * Return: status 1 for success to continue, 0 otherwise
*/

int check_args(int argc, char **argv)
{
	int status;
	struct stat sb;

	status = 1;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: 0-hreadelf <elf_filename>\n");
		return (0);
	}

	stat(argv[1], &sb);
	if (!S_ISREG(sb.st_mode))
	{
		fprintf(stderr, "Not a regular file here: %s", argv[1]);
		return (0);
	}
	return (status);
}

/**
 * print_helf - first entry for starting to print the ELF file
 * @fd: file descriptor
 * @args: array of arguments
 * Return: 0 success, 1 for errors
*/

int print_helf(FILE *fd, char *args)
{
	Elf64_Ehdr elf64;
	Elf32_Ehdr elf32;
	int is32, endian, exit_status;

	/* ELF Binary files, so fread() more appropriate than read() */
	/* fread() reads binary stream input/output ==> ELF */
	/* Check man fread they use it for an ELF !!! :) */
	fread(&elf64, sizeof(elf64), 1, fd);
	/* rewind(fd); */
	fseek(fd, 0L, SEEK_SET);
	fread(&elf32, sizeof(elf32), 1, fd);
	/* ELFMAG symbolink constant represent the four magic bytes */
	/* SELFMAG Preprocessor declared to be '4' */
	if (memcmp(elf64.e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "readelf: Error: Not an ELF file");
		fprintf(stderr, "- it has the wrong magic bytes at the start\n");
		return (0);
	}
	puts("ELF Header:");
	print_magic(elf64.e_ident);
	is32 = print_class(elf64.e_ident, args);
	if (is32 == 1)
		return (1);
	endian = print_endian(elf64.e_ident, args);
	if (endian == 1)
		return (1);
	exit_status = print_version(elf64.e_ident, args);
	if (exit_status == 1)
		return (1);
	if (is32 == 32)
	{
		convert_elf64(elf64, endian);
		print_elf64(elf64);
	}
	else
	{
		convert_elf64(elf64, endian);
		print_elf64(elf64);
	}
	return (0);
}


/**
 * main - entry point and manage all errors that can occurs
 * @argc: count of args
 * @argv: array of args
 * Return: 1 for success, 0 otherwise
*/

int main(int argc, char **argv)
{
	int exit_status;
	FILE *fp;

	if (check_args(argc, argv) == 0)
		return (1);
	fp = pick_fd(argv[1]);
	if (!fp)
		return (1);
	exit_status = print_helf(fp, *argv);
	return (exit_status);
}

