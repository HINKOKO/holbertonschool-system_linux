#include "hreadelf.h"

/**
 * print_magic - display magic bytes
 * @bytes: chars array
 */

void print_magic(unsigned char *bytes)
{
	size_t i;
	unsigned char *magics = ((Elf64_Ehdr *)bytes)->e_ident;

	printf("  Magic    ");
	for (i = 0; i < 16; i++)
		printf("%02x ", magics[i]);
	printf("\n");
}

/**
 * print_class - display the class of ELF
 * @bytes: chars array
 */

void print_class(unsigned char *bytes)
{
	unsigned char klass = ((Elf64_Ehdr *)bytes)->e_ident[EI_CLASS];

	printf("  Class:                             ");
	switch (klass)
	{
	case (ELFCLASS32):
		puts("ELF32");
		break;
	case (ELFCLASS64):
		puts("ELF64");
		break;
	case (ELFCLASSNONE):
		puts("Invalid class");
		break;
	}
}

/**
 * print_data - display the data field of ELF
 * @bytes: chars array
 */

void print_data(unsigned char *bytes)
{
	unsigned char data = ((Elf64_Ehdr *)bytes)->e_ident[EI_CLASS];

	printf("  Data:                              ");
	switch (data)
	{
	case (ELFDATA2LSB):
		puts("2's complement, little endian");
		break;
	case (ELFDATA2MSB):
		puts("2's complement, big endian");
		break;
	case (ELFDATANONE):
	default:
		puts("Unknown endianness");
		break;
	}
}

/**
 * print_elf_header - main function to loop through
 * all printers functions
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_elf_header(unsigned char *bytes, int class, int endian)
{
	printf("ELF Header:\n");
	print_magic(bytes);
	print_class(bytes);
	print_data(bytes);
	print_version(bytes);
	print_osabi(bytes);
	print_abi_version(bytes);
	print_type(bytes, endian);
	print_machine(bytes, endian);
	print_file_version(bytes, endian);
	print_entrypt(bytes, class, endian);
	print_start_header(bytes, class, endian);
	print_start_section(bytes, class, endian);
	print_flags(bytes, class, endian);
	print_size_header(bytes, class, endian);
	print_size_prog(bytes, class, endian);
	print_num_prog(bytes, class, endian);
	print_section_size(bytes, class, endian);
	print_num_hsection(bytes, class, endian);
	print_string_table(bytes, class, endian);
}

/**
 * main - entry point of make 0
 * @argc: count of arguments
 * @argv: array of arguments
 * Return: 0 success, 1 otherwise
 */

int main(int argc, char **argv)
{
	unsigned char bytes[64];

	if (argc != 2)
		return (EXIT_SUCCESS);
	if (access(argv[1], F_OK) == -1)
	{
		fprintf(stderr, "readelf: Error: '%s' No such file\n", argv[1]);
		return (EXIT_FAILURE);
	}
	if (access(argv[1], O_RDONLY) == -1)
	{
		fprintf(stderr, "readelf: Error: %s: Failed to read file's magic\n",
				argv[1]);
		return (EXIT_FAILURE);
	}
	if (read_elf_header_bytes(bytes, argv[1]))
	{
		perror("readelf: Error: ");
		return (EXIT_FAILURE);
	}
	if (check_elf_magic(bytes))
		return (EXIT_FAILURE);
	print_elf_header(bytes,
					 bytes[4] == ELFCLASS32 ? ELFCLASS32 : ELFCLASS64,
					 bytes[5] == ELFDATA2LSB ? ELFDATA2LSB : ELFDATA2MSB);
	return (0);
}
