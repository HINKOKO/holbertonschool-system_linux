#include "hreadelf.h"

/**
 * get_section_header_start - get the start (offset)
 * of section header in ELF File
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: (void pointer you should handle the type correctly
 * where it goes dude !)
 */

void *get_section_header_start(unsigned char *bytes, int class, int endian)
{
	void *hstart = class == ELFCLASS32 ? (void *)&((Elf32_Ehdr *)bytes)->e_shoff
									   : (void *)((Elf64_Ehdr *)bytes)->e_shoff;
	if (endian == ELFDATA2MSB)
		swapper(hstart, class == ELFCLASS32 ? 4 : 8);
	return (hstart);
}

/**
 * get_number_sections - get section header count
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: uint16_t shnum
 */

Elf64_Off get_number_sections(unsigned char *bytes, int class, int endian)
{
	Elf64_Off shnum = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shnum
										  : ((Elf64_Ehdr *)bytes)->e_shnum;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&shnum, 2);
	return (shnum);
}

/**
 * get_size_hsection - get section header table entry size
 * e_shentsize ==> This member holds a sections header's size in bytes.  A
 * section header is one entry in the section header table;
 * all entries are the same size.
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: the uint16_t section header size
 */

Elf64_Half get_size_hsection(unsigned char *bytes, int class, int endian)
{
	Elf64_Half shead_size = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shentsize
												: ((Elf64_Ehdr *)bytes)->e_shentsize;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&shead_size, 2);
	return (shead_size);
}

/**
 * get_string_tabidx - pick the section header table
 * string index, ==> the entry associated with the section name string table.
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: uint16_t string tab index
 */

uint16_t get_string_tabidx(unsigned char *bytes, int class, int endian)
{
	uint16_t stridx = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shstrndx
										  : ((Elf64_Ehdr *)bytes)->e_shstrndx;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&stridx, 2);
	return (stridx);
}
