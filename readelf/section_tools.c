#include "hreadelf.h"

/**
 * read_bytes - read 64 bytes from ELF File
 * @bytes: chars array
 * @filename: ELF Filename to read from
 * @offset: offset in the ELF File to read at
 * @size: size of bytes to be read
 * Return: 0 success, 1 failure
 */

int read_bytes(unsigned char **bytes, const char *filename,
			   size_t offset, size_t size)
{
	FILE *fp = NULL;

	*bytes = malloc(sizeof(char) * size);
	if (!bytes)
		exit(EXIT_FAILURE);
	fp = fopen(filename, "rb");
	if (!fp || fseek(fp, offset, SEEK_SET) || fread(*bytes, size, 1, fp) == 0)
	{
		fprintf(stderr, "readelf: Error: problem when reading sections\n");
		return (1);
	}
	fclose(fp);
	return (0);
}

/**
 * get_section_offset - get section file offset
 * ==> This member's value holds the byte offset from the
 * beginning of the file to the first byte in the section.
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: the 64 or 32 bit section file offset
 */

Elf64_Off get_section_offset(unsigned char *bytes, int class, int endian)
{
	Elf64_Off sec_off = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_offset
											: ((Elf64_Shdr *)bytes)->sh_offset;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sec_off, class == ELFCLASS32 ? 4 : 8);
	return (sec_off);
}

/**
 * get_section_size - get the section size in bytes
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB decider
 * Return: the 64/32 section size based on bytes
 */

uint64_t get_section_size(unsigned char *bytes, int class, int endian)
{
	uint64_t sec_size = class == ELFCLASS32 ? ((Elf32_Shdr *)bytes)->sh_size
											: ((Elf64_Shdr *)bytes)->sh_size;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sec_size, class == ELFCLASS32 ? 4 : 8);
	return (sec_size);
}

/**
 * get_section_type - get section type, a PAIN
 * @type: type index
 * Return: section type name
 */

char *get_section_type(uint32_t type)
{
	switch (type)
	{
	case SHT_PROGBITS:
		return ("PROGBITS");
	case SHT_SYMTAB:
		return ("SYMTAB");
	case SHT_STRTAB:
		return ("STRTAB");
	case SHT_RELA:
		return ("RELA");
	case SHT_HASH:
		return ("HASH");
	case SHT_DYNAMIC:
		return ("DYNAMIC");
	case SHT_NOTE:
		return ("NOTE");
	case SHT_NOBITS:
		return ("NOBITS");
	case SHT_REL:
		return ("REL");
	case SHT_SHLIB:
		return ("SHLIB");
	case SHT_GNU_verneed:
		return ("VERNEED");
	case SHT_INIT_ARRAY:
		return ("INIT_ARRAY");
	case SHT_NULL:
	default:
		return ("NULL");
	}
}
