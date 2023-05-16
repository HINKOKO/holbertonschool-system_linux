#include "hreadelf.h"

/**
 * reverser - switch the endiannesses little to big vice versa
 * @bytes: pointer to chars array to be swapped
 * @size: size of chars array
 */

void reverser(unsigned char *bytes, size_t size)
{
	size_t start, end;
	size_t tmp;

	for (start = 0, end = size - 1; start < size; start++, end--)
	{
		tmp = bytes[start];
		bytes[start] = bytes[end];
		bytes[end] = tmp;
	}
}

/**
 * get_section_start - goal is to grab a pointer on first section
 * @bytes: char array
 * @class: 32 or 64 bit int flag decision
 * @endian: little or big endian int flag decision
 * Return: pointer to begin of first section
 */

void *get_section_start(unsigned char *bytes, int class, int endian)
{
	void *header = class == ELFCLASS32 ? (void *)&((Elf32_Ehdr *)bytes)->e_shoff
									   : (void *)&((Elf64_Ehdr *)bytes)->e_shoff;

	if (endian == ELFDATA2MSB)
		reverser(header, class == ELFCLASS32 ? 4 : 8);
	/* 4 bytes gives 32 bits , 8 bytes gives 64 bits */
	return (header);
}

/**
 * get_number_sections - retrieve the number "e_shnum" of sections
 * @bytes: char array
 * @class: 32 or 64 bit int flag decision
 * @endian: little or big endian int flag decision
 * Return: Number of sections
 */

uint16_t get_number_sections(unsigned char *bytes, int class, int endian)
{
	uint16_t num = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_shnum
									   : ((Elf64_Ehdr *)bytes)->e_shnum;

	if (endian == ELFDATA2MSB)
		reverser((unsigned char *)&num, 2);
	return (num);
}
