#include "hreadelf.h"

/**
 * print_section_name - prints the section name
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 * @strtable: string table
 */

void print_section_name(unsigned char *bytes, int class, int endian,
						unsigned char *strtable)
{
	uint32_t name = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_name
										: ((Elf64_Shdr *)bytes)->sh_name;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&name, class == ELFCLASS32 ? 4 : 8);
	printf("%-17s", strtable + name);
}

/**
 * print_section_name - prints the section name
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 * @strtable: string table
 */

void print_section_type(unsigned char *bytes, int class, int endian)
{
	uint32_t type = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_type
										: ((Elf64_Shdr *)bytes)->sh_type;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&type, class == ELFCLASS32 ? 4 : 4);
	printf("%-15s", get_section_type(type));
}
