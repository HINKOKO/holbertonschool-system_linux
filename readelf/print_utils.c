#include "hreadelf.h"

/**
 * print_magic - print the magic number
 * It's a kind of magic !
 * @bytes: bytes array
*/

void print_magic(unsigned char *bytes)
{
	size_t i;

	printf(" Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", bytes[i]);
	printf("\n");
}

/**
 * printclass - check what class is and prints accordingly
 * @bytes: bytes array
 * @args: args inputed (to match from main)
 * Return: 0 on success, 1 error, 32 for 32 bits detected
*/

int print_class(unsigned char *bytes, char *args)
{
	if (bytes[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "Error, %s\n", args);
		return (1);
	}
	if (bytes[EI_CLASS] == ELFCLASS32)
	{
		printf("%6s%-28c%s\n", "Class", ':', "ELF32");
		return (32);
	}
	else
		printf("%6s%-28c%s\n", "Class", ':', "ELF64");
	return (0);
}

int print_endian(unsigned char *bytes, char *args)
{
	if (bytes[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "Invalid encoding %d\n", *args);
		return (1);
	}
	if (bytes[EI_DATA] == ELFDATA2LSB)
	{
		printf("%6s%-28c%s\n", "Data", ':', "2's complement, little endian");
		return (LSB);
	}
	else
		printf("%6s%-28c%s\n", "Data", ':', "2's complement, big endian");
	return (MSB);
}

int print_version(unsigned char *bytes, char *args)
{
	if (bytes[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "Invalid Versioning in file: %d\n", *args);
		return (1);
	}
	printf("%6s%-28c%d\n", "Version", ':', EV_CURRENT);
	return (0);
}
