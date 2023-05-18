#include "hreadelf.h"

/**
 * print_section_entry_size - print the section entry size
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_entry_size(unsigned char *bytes, int class, int endian)
{
	uint64_t entsize = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_entsize
										   : ((Elf64_Shdr *)bytes)->sh_entsize;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&entsize, class == ELFCLASS32 ? 4 : 8);
	printf("%02lx", entsize);
}

/**
 * print_section_flags - print the flags bits set in the entry
 * sh_flags
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_flags(unsigned char *bytes, int class, int endian)
{
	char buf[16] = {0}, *start = buf;
	uint64_t flags = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_flags
										 : ((Elf64_Shdr *)bytes)->sh_flags;

	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&flags, class == ELFCLASS32 ? 4 : 8);

	if (flags & SHF_WRITE)
		*start++ = 'W';
	if (flags & SHF_ALLOC)
		*start++ = 'A';
	if (flags & SHF_EXECINSTR)
		*start++ = 'X';
	printf(" %3s", buf);
}

/**
 * print_section_link - print the section header table link
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_link(unsigned char *bytes, int class, int endian)
{
	uint32_t link = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_link
										: ((Elf64_Shdr *)bytes)->sh_link;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&link, class == ELFCLASS32 ? 4 : 4);
	printf("%2u", link);
}

/**
 * print_section_info - print the extra info
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_info(unsigned char *bytes, int class, int endian)
{
	uint32_t info = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_info
										: ((Elf64_Shdr *)bytes)->sh_info;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&info, class == ELFCLASS32 ? 4 : 4);
	printf("%3u", info);
}

/**
 * print_section_addralign - print the align address constraint
 * ==> if a section contains doubleword, system must ensure
 * doubleword align for the entire section
 * value 0 or 1 means no alignement constraint
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_section_addralign(unsigned char *bytes, int class, int endian)
{
	uint64_t addralign = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_addralign
											 : ((Elf64_Shdr *)bytes)->sh_addralign;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&addralign, class == ELFCLASS32 ? 4 : 8);
	printf("%2lu\n", addralign);
}
