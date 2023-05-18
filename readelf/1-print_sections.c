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
 * print_section_type - prints the section name
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_type(unsigned char *bytes, int class, int endian)
{
	uint32_t type = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_type
										: ((Elf64_Shdr *)bytes)->sh_type;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&type, class == ELFCLASS32 ? 4 : 4);
	printf(" %-15s", get_section_type(type));
}

/**
 * print_section_addr - print the section addresses
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_addr(unsigned char *bytes, int class, int endian)
{
	Elf64_Addr addr = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_addr
										  : ((Elf64_Shdr *)bytes)->sh_addr;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&addr, class == ELFCLASS32 ? 4 : 8);
	printf(" %0*lx", class == ELFCLASS32 ? 8 : 16, addr);
}

/**
 * print_section_off - print the section offset
 * ==> value which holds the byte offset from beginning of file
 * to the first byte in section
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_off(unsigned char *bytes, int class, int endian)
{
	Elf64_Off offset = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_offset
										   : ((Elf64_Shdr *)bytes)->sh_offset;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&offset, class == ELFCLASS32 ? 4 : 8);
	printf(" %06lx", offset);
}

/**
 * print_section_size - print the section size
 * ==> value which holds the section size in bytes
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_size(unsigned char *bytes, int class, int endian)
{
	uint64_t sec_size = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_size
											: ((Elf64_Shdr *)bytes)->sh_size;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sec_size, class == ELFCLASS32 ? 4 : 8);
	printf(" %06lx", sec_size);
}
