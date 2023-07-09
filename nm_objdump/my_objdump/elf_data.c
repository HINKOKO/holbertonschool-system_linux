#include "objdump.h"

/**
 * init_elf_data - initialize elf_t data struct to fill it
 * @elf: pointer to elf_t structure we defined
 * @data: flexible data pointer
 * Return: haha or -1 if error
*/

int init_elf_data(elf_t *elf, void *data)
{
	elf->map = data;
	elf->ehdr = data;

	if (!check_elf(elf->ehdr->e_ident))
	{
		fprintf(stderr, "Not an ELF file - it has wrong magic bytes at the start");
		return (-1);
	}
	elf->shdr = (Elf64_Shdr *)(elf->map + elf->ehdr->e_shoff);
	if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	{
		/* allocate memory for new ELF header */
		elf->ehdr = malloc(sizeof(*(elf->ehdr)));
		if (!(elf->ehdr))
			return (perror("malloc"), -1);
		/* stick that header in memory space */
		fit_elf_header(elf, data);
		/* memory for section header */
		elf->shdr = malloc(sizeof(*(elf->shdr)) * elf->ehdr->e_shnum);
		if (!(elf->shdr))
			return (perror("malloc"), -1);
		/* stick in memory space */
		fit_shtab(elf, (Elf32_Shdr *)(elf->map + elf->ehdr->e_shoff),
			elf->ehdr->e_shnum);
	}
	/* get string tab header */
	if ((elf->shstrtab = get_shstrtab(elf->shdr,
									 elf->ehdr->e_shstrndx,
									 elf->map)) == NULL)
		return (-1);
	/* Get string table */
	if ((elf->strtab = get_strtab(elf)) == NULL)
		return (-1);
	return (0);
}

/**
 * get_strtab - locate and retrieve the string table data from ELF
 * @elf: pointer to elf_t structure
 * Return: pointer to string tab index .strtab or NULL if no found
*/

char *get_strtab(elf_t *elf)
{
	char *shstrtab;
	size_t i;

	shstrtab = elf->shstrtab;
	i = 0;
	while (i < elf->ehdr->e_shnum)
	{
		if (!strcmp(&shstrtab[elf->shdr[i].sh_name], ".strtab"))
			return (elf->map + elf->shdr[i].sh_offset);
		++i;
	}
	fprintf(stderr, "Sorry, no string table");
	return (NULL);
}

/**
 * get_shstrtab - get section header string table
 * based on string table index
 * @shdr_tab: pointer to section header table Elf64_Shdr
 * @strndx: index of section header string table
 * @addr: pointer to base address of mapped file
 * Return: NULL if failure, or if valid index,
 * return a pointer to the start of section header string table
*/

char *get_shstrtab(Elf64_Shdr *shdr_tab, Elf64_Half strndx, char *addr)
{
	if (strndx == SHN_UNDEF)
		return (fprintf(stderr, "Unable to get section header string table"), NULL);
	return (addr + shdr_tab[strndx].sh_offset);
}

/**
 * fit_elf_header - fills the ehdr field of struct elf_t
 * @elf: pointer to elf_t structure
 * @data: pointer to chars data Elf32_Ehdr
*/

void fit_elf_header(elf_t *elf, Elf32_Ehdr *data)
{
	/* copy paste the data from ELF file to struct */
	memcpy(elf->ehdr->e_ident, data->e_ident, elf->ehdr->e_ident[EI_NIDENT]);
	elf->ehdr->e_type = data->e_type;
	elf->ehdr->e_machine = data->e_machine;
	elf->ehdr->e_version = data->e_version;
	elf->ehdr->e_entry = data->e_entry;
	elf->ehdr->e_phoff = data->e_phoff;
	elf->ehdr->e_shoff = data->e_shoff;
	elf->ehdr->e_flags = data->e_flags;
	elf->ehdr->e_ehsize = data->e_ehsize;
	elf->ehdr->e_phentsize = data->e_phentsize;
	elf->ehdr->e_phnum = data->e_phnum;
	elf->ehdr->e_shentsize = data->e_shentsize;
	elf->ehdr->e_shnum = data->e_shnum;
	elf->ehdr->e_shstrndx = data->e_shstrndx;
}

/**
 * fit_shtab - fills the shdr field of struct elf_t
 * @elf: pointer to elf_t structure
 * @data: pointer to chars data Elf32_Shdr
 * @len: len of Shdr
*/

void fit_shtab(elf_t *elf, Elf32_Shdr *data, size_t len)
{
	size_t i = 0;

	while (i < len)
	{
		elf->shdr[i].sh_name = data[i].sh_name;
		elf->shdr[i].sh_type = data[i].sh_type;
		elf->shdr[i].sh_flags = data[i].sh_flags;
		elf->shdr[i].sh_offset = data[i].sh_offset;
		elf->shdr[i].sh_size = data[i].sh_size;
		elf->shdr[i].sh_link = data[i].sh_link;
		elf->shdr[i].sh_info = data[i].sh_info;
		elf->shdr[i].sh_addralign = data[i].sh_addralign;
		elf->shdr[i].sh_entsize = data[i].sh_entsize;
		++i;
	}
}
