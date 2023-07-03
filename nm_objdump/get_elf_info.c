#include "hnm.h"

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
 * get_info - pick symbol type
 * @hdr: struct holding ELF infos
 * @i: symtab index
 * Return: the symbol abbreviation as a char
 */

char get_info(hdrs *hdr, int i)
{
	char c;

	if (ELFN_ST_BIND == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELFN_ST_BIND == STB_WEAK && ELFN_ST_TYPE == STT_OBJECT)
		c = GET_SYM(st_shndx, i) == SHN_UNDEF ? 'v' : 'V';
	else if (ELFN_ST_BIND == STB_WEAK)
		c = GET_SYM(st_shndx, i) == SHN_UNDEF ? 'w' : 'W';
	else if (GET_SYM(st_shndx, i) == SHN_UNDEF)
		c = 'U';
	else if (GET_SYM(st_shndx, i) == SHN_ABS)
		c = 'A';
	else if (GET_SYM(st_shndx, i) == SHN_COMMON)
		c = 'C';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_NOBITS &&
			 GET_SHDR(sh_flags, GET_SYM(st_shndx, i)) == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_PROGBITS &&
			 GET_SHDR(sh_flags, GET_SYM(st_shndx, i)) == SHF_ALLOC)
		c = 'R';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_PROGBITS &&
			 GET_SHDR(sh_flags, GET_SYM(st_shndx, i)) == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_PROGBITS &&
			 GET_SHDR(sh_flags, GET_SYM(st_shndx, i)) == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (GET_SHDR(sh_type, GET_SYM(st_shndx, i)) == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'D';
	if (ELFN_ST_BIND == STB_LOCAL)
		c += 32;
	return (c);
}

/**
 * sym - print symbols of ELF binary
 * @hdr: struct for ELF infos
 * Return: 1
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
	hdr->Sym32 = (Elf32_Sym *)&hdr->map[GET_SHDR(sh_offset, i)];
	hdr->Sym64 = (Elf64_Sym *)&hdr->map[GET_SHDR(sh_offset, i)];
	strtab = &hdr->map[GET_SHDR(sh_offset, i + 1)];
	/* divide total size by size of an entr -> gives us the number of entries */
	/* then we can iterate over in our for loop with j */
	sym_size = GET_SHDR(sh_size, i) / GET_SHDR(sh_entsize, i);
	for (j = 1; j < sym_size; ++j)
	{
		if (IS_MSB)
		{
			conv_msb((char *)SET_SYM(st_value, j), SYM_SIZE(st_value, i));
			conv_msb((char *)SET_SYM(st_info, j), SYM_SIZE(st_info, i));
			conv_msb((char *)SET_SYM(st_name, j), SYM_SIZE(st_name, i));
		}
		/* lower four-bytes of st_info => symbol's type */
		/* upper-four bytes of st_info => symbol's binding */
		/* check if symbol associated with a section ? */
		/* or symbol associated with a source file ? if yes continue => */
		if ((GET_SYM(st_info, j) & 15) == STT_SECTION ||
			(GET_SYM(st_info, j) & 15) == STT_FILE)
			continue;
		if ((!GET_SYM(st_size, j) && !GET_SYM(st_value, j))
			|| get_info(hdr, j) == 'U')
			printf("%*c %c %s\n", IS_32 ? 8 : 16, ' ',
				get_info(hdr, j), &strtab[GET_SYM(st_name, j)]);
		else
			printf("%0*lx %c %s\n", IS_32 ? 8 : 16, GET_SYM(st_value, j),
				get_info(hdr, j), &strtab[GET_SYM(st_name, j)]);
	}
	return (1);
}

/**
 * init_shdr - initialize ELFxx_Shdr struct
 * @hdr: pointer to struct for storing ELF info
 */

void init_shdr(hdrs *hdr)
{
	int i;

	hdr->Shdr32 = (Elf32_Shdr *)&hdr->map[GET_EHDR(e_shoff)];
	hdr->Shdr64 = (Elf64_Shdr *)&hdr->map[GET_EHDR(e_shoff)];
	if (IS_MSB)
	{
		for (i = 0; i < GET_EHDR(e_shnum); ++i)
		{
			conv_msb((char *)SET_SHDR(sh_type, i),
					 SHDR_SIZE(sh_type, i));
			conv_msb((char *)SET_SHDR(sh_offset, i),
					 SHDR_SIZE(sh_offset, i));
			conv_msb((char *)SET_SHDR(sh_size, i),
					 SHDR_SIZE(sh_size, i));
			conv_msb((char *)SET_SHDR(sh_entsize, i),
					 SHDR_SIZE(sh_entsize, i));
		}
	}
}

/**
 * init_ehdr - initialize header info stuff
 * @hdr: pointer to struct hdrs
 *
 */

void init_ehdr(hdrs *hdr)
{
	hdr->Ehdr32 = (Elf32_Ehdr *)hdr->map;
	hdr->Ehdr64 = (Elf64_Ehdr *)hdr->map;

	if (IS_MSB)
	{
		conv_msb((char *)SET_EHDR(e_shoff), EHDR_SIZE(e_shoff));
		conv_msb((char *)SET_EHDR(e_shentsize), EHDR_SIZE(e_shentsize));
		conv_msb((char *)SET_EHDR(e_shnum), EHDR_SIZE(e_shnum));
	}
}
