#include "hreadelf.h"

/**
 * print_start_section - display section header
 * table file offset
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_start_section(unsigned char *bytes, int class, int endian)
{
	Elf64_Off *h64;
	Elf32_Off *h32;

	printf("  Start of section headers:          ");
	if (class == ELFCLASS32)
	{
		h32 = &((Elf32_Ehdr *)bytes)->e_shoff;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)h32, 4);
		printf("%u", *h32);
	}
	else
	{
		h64 = &((Elf64_Ehdr *)bytes)->e_shoff;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)h64, 8);
		printf("%lu", *h64);
	}
	puts(" (bytes into file)");
}

/**
 * print_flags - display processor specific flags
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_flags(unsigned char *bytes, int class, int endian)
{
	uint32_t flags = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_flags
										 : ((Elf64_Ehdr *)bytes)->e_flags;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&flags, 4);
	printf("  Flags:                             0x%x\n", flags);
}

/**
 * print_size_header - display prog header size
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_size_header(unsigned char *bytes, int class, int endian)
{
	uint16_t ehsize = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_ehsize
										  : ((Elf64_Ehdr *)bytes)->e_ehsize;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&ehsize, 2);
	printf("  Size of this header:               %d (bytes)\n", ehsize);
}

/**
 * print_size_prog - display prog header table entry size
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_size_prog(unsigned char *bytes, int class, int endian)
{
	uint16_t sizeprogh = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_phentsize
											 : ((Elf64_Ehdr *)bytes)->e_phentsize;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&sizeprogh, 2);
	printf("  Size of program headers:           %d (bytes)\n", sizeprogh);
}

/**
 * print_num_prog - display prog header table entry count
 * @bytes: chars array
 * @class: 32/64 bits flag int
 * @endian: LSB/MSB flag int
 */

void print_num_prog(unsigned char *bytes, int class, int endian)
{
	uint16_t numprogh = class == ELFCLASS32 ? ((Elf32_Ehdr *)bytes)->e_phnum
											: ((Elf64_Ehdr *)bytes)->e_phnum;
	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&numprogh, 2);
	printf("  Number of program headers:         %d\n", numprogh);
}
