#include "hreadelf.h"

/**
 * print_elf_sections_loop - main function to loop through
 * all printers functions
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 * @num_sections: number of sections
 * @hsize: size of header sections
 * @str_table: the string table
 */

void print_elf_sections_loop(unsigned char *bytes, int class, int endian,
							 int num_sections, int hsize, unsigned char *str_table)
{
	int i;

	print_section_hname(class);

	for (i = 0; i < num_sections; ++i, bytes += hsize)
	{
		printf("  [%2d] ", i);
		print_section_name(bytes, class, endian, str_table);
		print_section_type(bytes, class, endian);
		print_section_addr(bytes, class, endian);
		print_section_off(bytes, class, endian);
		print_section_size(bytes, class, endian);
		print_section_entry_size(bytes, class, endian);
		print_section_flags(bytes, class, endian);
		print_section_link(bytes, class, endian);
		print_section_info(bytes, class, endian);
		print_section_addralign(bytes, class, endian);
	}

	print_key_match_flags(class);
}

/**
 * print_elf_section_header - mimics the readelf -W -S
 * infos about section headers
 * @bytes: chars array
 * @filename: the ELF file to print from
 * @class: 32/64 bits int flag
 * @endian: LSB/MSB int flag
 */

void print_elf_section_header(unsigned char *bytes, char *filename,
							  int class, int endian)
{
	Elf64_Off offset = 0;
	uint16_t n_sections = 0, str_idx = 0, size_hsection = 0;
	size_t string_offset = 0, sec_size = 0;
	unsigned char *data = NULL, *str_table = NULL;

	/* catch a pointer on the first header of sections */
	void *header_start = get_section_header_start(bytes, class, endian);
	/* cast and dereference to access its value */
	offset = class == ELFCLASS32 ? *(Elf32_Off *)header_start
								 : *(Elf64_Off *)header_start;
	n_sections = get_number_sections(bytes, class, endian);
	size_hsection = get_size_hsection(bytes, class, endian);
	printf("There are %d section headers, starting at offset %#lx:\n",
		   n_sections, offset);
	/* read chunks of bytes of ELF sections according to num mutiply by size */
	if (read_bytes(&data, filename, offset, n_sections * size_hsection))
	{
		exit(EXIT_FAILURE);
	}

	str_idx = get_string_tabidx(bytes, class, endian);
	string_offset = get_section_offset(data + (str_idx * size_hsection),
									   class, endian);
	sec_size = get_section_size(data + (str_idx * size_hsection), class, endian);

	if (read_bytes(&str_table, filename, string_offset, sec_size))
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	print_elf_sections_loop(data, class, endian,
							n_sections, size_hsection, str_table);
	free(data);
	free(str_table);
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
	print_elf_section_header(bytes, argv[1],
							 bytes[4] == ELFCLASS32 ? ELFCLASS32 : ELFCLASS64,
							 bytes[5] == ELFDATA2MSB ? ELFDATA2MSB : ELFDATA2LSB);
	return (0);
}
