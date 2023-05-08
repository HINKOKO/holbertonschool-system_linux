#include "hreadelf.h"

/**
 * print_helf - displays the elf header of file
 * @fp: file descriptor
 * @args: array with args for options
 * Return: 1 for success (continue), 0 otherwise
*/

// int print_helf(FILE *fp, char *args)
// {
// 	Elf32_Ehdr elf32;
// 	Elf64_Ehdr elf64;



// }

/**
 * main - entry point
 * @argc: count of args
 * @argv: array of args
 * Return: 1 for success, 0 otherwise
*/

int main(int argc, char **argv)
{
	int i = 0;
	int fd = open(argv[1], O_RDONLY);
	Elf64_Ehdr header;

	(void)argc;

	read(fd, &header, sizeof(header));

	printf("ELF Header:\n");
	printf("  Magic  ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x ", header.e_ident[i]);
	}
	printf("\n");
	printf("  Class:			%s\n", header.e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");

	close(fd);
	return (0);

}
