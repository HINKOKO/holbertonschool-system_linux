#include "hreadelf.h"

/**
 * check_magic - function to check if magic bytes are magic
 * @bytes: chars array
 * Return: 0 success, 1 failure
 */

int check_magic(unsigned char *bytes)
{
	Elf64_Ehdr *elf64;

	elf64 = (Elf64_Ehdr *)bytes;
	if (memcmp(elf64->e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "Not an ELF file, wrong magic bytes\n");
		return (1);
	}
	return (0);
}

/**
 * read_header_bytes - reads 64 bytes from header
 * @bytes: charac array
 * @filename: the ELF file to read from
 * Return: 0 success, 1 failure
 */

int read_header_bytes(unsigned char *bytes, const char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "rb");
	if (!fp || fread(bytes, 64, 1, fp) == 0)
		return (1);
	fclose(fp);
	return (0);
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
 * print_section_header - take care of displaying the header and
 * call the other print functions on the way
 * @bytes: char array
 * @filename: the filename ELF to show sections off
 * @class: 32 or 64 bit int flag decision
 * @endian: little or big endian int flag decision
 * Return: 0 success, 1 failure, thank you
 */

int print_section_header(unsigned char *bytes, char *filename,
						 int class, int endian)
{
	Elf64_Off offset;
	uint16_t number_sections = 0;
	/* void to perform sanity arithmetics (hackademics.fr)*/
	/* goal=> catch a pointer on the first header of section */
	/* not known at first but casting then to hanlde it */
	(void)filename;

	void *header_start = get_section_start(bytes, class, endian);
	/* === *(jojo *) pointer == */
	/* jojo casted & dereferenced to access its value */
	offset = class == ELFCLASS32 ? *(Elf32_Off *)header_start
								 : *(Elf64_Off *)header_start;
	number_sections = get_number_sections(bytes, class, endian);

	printf("There are %d section headers, starting at offset %#lx:\n\n",
		   number_sections, offset);
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
	unsigned char bytes[64];

	if (check_args(argc, argv) == 0)
		return (1);
	if (read_header_bytes(bytes, argv[1]))
	{
		perror("readelf: Error: ");
		return (1);
	}
	if (check_magic(bytes))
		return (1);
	print_section_header(bytes, argv[1],
						 bytes[4] == ELFCLASS32 ? ELFCLASS32 : ELFCLASS64,
						 bytes[5] == ELFDATA2LSB ? ELFDATA2LSB : ELFDATA2MSB);
	return (0);
}
