#include "hreadelf.h"

/**
 * swapper - swap the bytes for LSB/MSB conversion
 * @bytes: bytes array to swap
 * @size: size of bytes array
 */

void swapper(unsigned char *bytes, size_t size)
{
	size_t start, end;
	int tmp;

	for (start = 0, end = size - 1; start < end; start++, --end)
	{
		tmp = bytes[start];
		bytes[start] = bytes[end];
		bytes[end] = tmp;
	}
}

/**
 * read_elf_header_bytes - read the bytes from header ELF
 * to check if valid
 * @bytes: bytes array
 * @filename: the ELF filename to read from
 * Return: 1 for error, 0 for success
 */

int read_elf_header_bytes(unsigned char *bytes, const char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "rb");
	if (!fp || fread(bytes, 64, 1, fp) == 0)
		return (1);
	fclose(fp);
	return (0);
}

/**
 * check_elf_magic - check if magic bytes are magics
 * @bytes: bytes array
 * Return: 0 for success, magic is magic, 1 failure
 */

int check_elf_magic(unsigned char *bytes)
{
	Elf64_Ehdr *head64;

	head64 = (Elf64_Ehdr *)bytes;
	if (memcmp(head64->e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "readelf: Error: Not an ELF, wrong magic\n");
		return (1);
	}
	return (0);
}
