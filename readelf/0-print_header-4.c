#include "hreadelf.h"

/**
 *
 *
 */
void print_section_size(unsigned char *bytes, int class, int endian)
{
	uint16_t sec_size = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shentsize
											: ((Elf64_Ehdr *)bytes)->e_shentsize;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sec_size, 2);
	printf("  Size of section headers:		%d (bytes)\n", sec_size);
}

/**
 *
 *
 */

void print_num_hsection(unsigned char *bytes, int class, int endian)
{
	uint16_t sec_count = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shnum
											 : ((Elf64_Ehdr *)bytes)->e_shnum;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sec_count, 2);
	printf("  Number of section headers:		%d\n", sec_count);
}

/**
 *
 *
 */

void print_string_table(unsigned char *bytes, int class, int endian)
{
	uint16_t stridx = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shstrndx
										  : ((Elf64_Ehdr *)bytes)->e_shstrndx;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&stridx, 2);
	printf("  Section header string table index:    %d\n", stridx);
}
