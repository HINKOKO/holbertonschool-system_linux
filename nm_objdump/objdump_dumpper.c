#include "objdump.h"

/**
 * objdumper - launch the process of objdumping core
 * @filename: the filename to objdump's
 * Return: haha !
*/

int objdumper(const char *filename)
{
	void *data;
	int map_size;
	elf_t elf;

	if ((map_size = map_file(&data, filename)) == -1)
		return (-1);
	if (init_elf_data(&elf, data) == -1)
		return (-1);
	display_sections(&elf);
	if (elf.ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	{
		free(elf.ehdr);
		free(elf.shdr);
	}
	munmap(data, map_size);
	return (0);
}

/**
 * display_sections - display the content of sections found in .strtab
 * @elf: pointer to elf_t struct
*/

void display_sections(elf_t *elf)
{
	void *section;
	size_t i;

	i = 0;
	while (i < elf->ehdr->e_shnum)
	{
		section = (elf->map + elf->shdr[i].sh_offset);
		if (section == elf->shstrtab)
			break;
		if (elf->shdr[i].sh_type != SHT_NOBITS
		&& elf->shdr[i].sh_type != SHT_SYMTAB
		&& elf->shstrtab[elf->shdr[i].sh_name])
		{
			printf("Content of section %s:\n", &(elf->shstrtab[elf->shdr[i].sh_name]));
			dump_section(section, &(elf->shdr)[i], BPL);
		}
		++i;
	}
}

/**
 * dump_section - dump's the content of section with 16 byte per line
 * @section: pointer to current section
 * @shdr: Elf64_Shdr byte array infos
 * @bpl: byte per line size_t
*/

void dump_section(char *section, Elf64_Shdr *shdr, size_t bpl)
{
	/* declare a buf 16 bytes + '\0' */
	char buf[BPL + 1];
	/* offset within the section */
	size_t sec_off;
	size_t i, j;

	sec_off = 0;
	/* outer loop until offset reach section size */
	while (sec_off < shdr->sh_size)
	{
		i = 0;
		/* Address of current byte being dumped */
		printf(" %04x", (unsigned int)(shdr->sh_addr + sec_off));
		/* inner loop prints bytes in section */
		/* print until bpl reached or end of section */
		while (i < bpl && sec_off + i < shdr->sh_size)
		{
			j = 0;
			printf(" ");
			/* loop to group 4 hex_bytes and ramdeck section size, and store in buf */
			while (j < 4 && sec_off + i + j < shdr->sh_size)
			{
				buf[i + j] = dump_byte_content(section[sec_off + i + j]);
				++j;
			}
			/* increment i to keep track of number of bytes written */
			i += j;
		}
		/* properly terminate as a string */
		buf[BPL] = '\0';
		printf(" %s\n", buf);
		/* move on the offset */
		sec_off += i;
	}
}

/**
 * dump_byte_content - dump the naked content of byte
 * @byte: the byte to reveal
 * Return: bytes content
*/

char dump_byte_content(char byte)
{
	if (byte > 0)
		printf("%02x", byte);
	else
		printf("00");
	/* isprint() => check if byte value is ASCII printable */
	return (isprint(byte) ? byte : '.');
}


