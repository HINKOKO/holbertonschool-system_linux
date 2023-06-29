#include "hnm.h"

/**
 * get_info - pick symbol type
 * @hdr: struct holding ELF infos
 * @idx: symtab index
 */

char *get_info(hdrs *hdr, int idx)
{
	char c;

	if (ELF64S_ST_BIND == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELFS_ST_BIND == STB_WEAK && ELFS_ST_TYPE == STT_OBJECT)
		c = GET_SYM(st_shndx, idx) == SHN_UNDEF ? 'v' : 'V';
	else if (ELFS_ST_BIND == STB_WEAK)
		c = GET_SYM(st_shndx, idx) == SHN_UNDEF ? 'w' : 'W';
	else if (GET_SYM(st_shndx, idx) == SHN_UNDEF)
		c = 'U';
	else if (GET_SYM(st_shndx, idx) == SHN_ABS)
		c = 'A';
	else if (GET_SYM(st_shndx, idx) == SHN_COMMON)
		c = 'C';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, idx)) ==)

	/* to be continued */
}

/**
 * sym - print symbols of ELF binary
 *
 */

int sym(hdrs *hdr)
{
	int i;
	size_t j, sym_size;
	char *strtab;

	for (i = 0; i < GET_EHDR(e_shnum); ++i)
		if (GET_SHDR(sh_type, i) == SHT_SYMTAB)
			break;
	if (i == GET_EHDR(e_shnum))
		return (0);
	hdr->Sym32 = (Elf32_Sym *)&hdr->addr[GET_SHDR[sh_offset, i]];
	hdr->Sym64 = (Elf64_Sym *)&hdr->addr[GET_SHDR[sh_offset, i]];
	strtab = &hdr->addr[GET_SHDR(sh_offset, i + 1)];
	/* divide total size by size of an entr -> gives us the number of entries */
	/* then we can iterate over in our for loop with j */
	sym_size = GET_SHDR(sh_size, i) / GET_SHDR(sh_entsize, i);
	for (j = 1; j < sym_size; ++j)
	{
		if (IS_MSB)
		{
			conv_msb((char *)SET_SYM(st_value, j), SYM_SIZE(st_value, i));
		}
	}
}
/**
 * conv_msb - convert to big endian with XOR tmp tec
 * @ptr: pointer to octet
 * @size: size of ptr points to
 */

void conv_msb(char *ptr, size_t size)
{
	size_t start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		ptr[start] ^= ptr[end];
		ptr[end] ^= ptr[start];
		ptr[start] ^= ptr[end];
	}
}
/**
 * init_shdr
 *
 *
 */

void *init_shdr(hdrs *hdr) {}

/**
 * init_ehdr - initialize header info stuff
 * @hdr: pointer to struct hdrs
 *
 */

void *init_ehdr(hdrs *hdr)
{
	hdr->Ehdr32 = (Elf32_Ehdr *)hdr->addr;
	hdr->Ehdr64 = (Elf64_Ehdr *)hdr->addr;

	if (IS_MSB)
	{
		conv_msb((char *)SET_EHDR(e_shoff), EHDR_SIZE(e_shoff));
		conv_msb((char *)SET_EHDR(e_shentsize), EHDR_SIZE(e_shentsize));
		conv_msb((char *)SET_EHDR(e_shnum), SET_EHDR(e_shnum));
	}
}
