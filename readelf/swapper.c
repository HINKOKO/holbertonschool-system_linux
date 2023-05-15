#include "hreadelf.h"

/**
 * swap_endian - switch the endiannesses little to big
 * @ptr: pointer to block of memory to be swapped
 * @size: size of block memory
*/

void swap_endian(void *ptr, size_t size)
{
	/* uint8_t portable and predictible */
	uint8_t *bytes = (uint8_t *) ptr;
	uint8_t tmp;
	size_t i;

	for (i = 0; i < size / 2; i++)
	{
		tmp = bytes[i];
		bytes[i] = bytes[size - i - 1];
		bytes[size - i - 1] = tmp;
	}
}

/**
 * convert_elf32 - convert endianness 32//64 bits
 * @elf32: Elf32_Ehdr struct to convert
 * @endian: "flag" int to know which endian's is involved
*/

void convert_elf32(Elf32_Ehdr elf32, int endian)
{
	if (endian == LSB)
	{
		swap_endian(&elf32.e_type, sizeof(elf32.e_type));
		swap_endian(&elf32.e_machine, sizeof(elf32.e_machine));
		swap_endian(&elf32.e_version, sizeof(elf32.e_version));
		swap_endian(&elf32.e_entry, sizeof(elf32.e_entry));
		swap_endian(&elf32.e_phoff, sizeof(elf32.e_phoff));
		swap_endian(&elf32.e_shoff, sizeof(elf32.e_shoff));
		swap_endian(&elf32.e_flags, sizeof(elf32.e_flags));
		swap_endian(&elf32.e_ehsize, sizeof(elf32.e_ehsize));
		swap_endian(&elf32.e_phentsize, sizeof(elf32.e_phentsize));
		swap_endian(&elf32.e_phnum, sizeof(elf32.e_phnum));
		swap_endian(&elf32.e_shentsize, sizeof(elf32.e_shentsize));
		swap_endian(&elf32.e_shnum, sizeof(elf32.e_shnum));
		swap_endian(&elf32.e_shstrndx, sizeof(elf32.e_shstrndx));
	}
}

/**
 * convert_elf64 - convert endianness 32//64 bits
 * @elf64: Elf64_Ehdr struct to convert
 * @endian: "flag" int to know which endian's is involved
*/

void convert_elf64(Elf64_Ehdr elf64, int endian)
{
	if (endian == LSB)
	{
		swap_endian(&elf64.e_type, sizeof(elf64.e_type));
		swap_endian(&elf64.e_machine, sizeof(elf64.e_machine));
		swap_endian(&elf64.e_version, sizeof(elf64.e_version));
		swap_endian(&elf64.e_entry, sizeof(elf64.e_entry));
		swap_endian(&elf64.e_phoff, sizeof(elf64.e_phoff));
		swap_endian(&elf64.e_shoff, sizeof(elf64.e_shoff));
		swap_endian(&elf64.e_flags, sizeof(elf64.e_flags));
		swap_endian(&elf64.e_ehsize, sizeof(elf64.e_ehsize));
		swap_endian(&elf64.e_phentsize, sizeof(elf64.e_phentsize));
		swap_endian(&elf64.e_phnum, sizeof(elf64.e_phnum));
		swap_endian(&elf64.e_shentsize, sizeof(elf64.e_shentsize));
		swap_endian(&elf64.e_shnum, sizeof(elf64.e_shnum));
		swap_endian(&elf64.e_shstrndx, sizeof(elf64.e_shstrndx));
	}
}
