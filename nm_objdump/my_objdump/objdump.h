#ifndef __H_OBJDUMP__
#define __H_OBJDUMP__

#include <elf.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
/* isprint function to check byte ASCII printable ? */
#include <ctype.h>

/* a.out default behavior */
#define DEFAULT "a.out"

/* Byte per line */
#define BPL 16

/**
 * struct selfself_crazy_stuff - homemade struct to
 * ELF'ilize the life of argv[1] when batman is gone!
 * @map: address, pointer to mapped file in memory
 * @ehdr: Elf64_Ehdr chars array
 * @shdr: Elf64_Shdr chars array
 * @shstrtab: pointer to section header string table
 * @strtab: pointer to string table interesting to us
*/
typedef struct selfself_crazy_stuff
{
	char *map;
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdr;
	char *shstrtab;
	char *strtab;
} elf_t;

/* ELF VALIDITY check */
int check_elf(unsigned char *elf);

/* Memory mapping to access data conveniently */
int map_file(void **map, const char *filename);


/* Objdump 'core' */
int objdumper(const char *filename);
void display_sections(elf_t *elf);
void dump_section(char *section, Elf64_Shdr *shdr, size_t bpl);
char dump_byte_content(char byte);

/* Elf data manipulation and struct fill */
int init_elf_data(elf_t *elf, void *data);
char *get_strtab(elf_t *elf);
char *get_shstrtab(Elf64_Shdr *shdr_tab, Elf64_Half strndx, char *addr);
void fit_elf_header(elf_t *elf, Elf32_Ehdr *data);
void fit_shtab(elf_t *elf, Elf32_Shdr *data, size_t len);











#endif /* __H_OBJDUMP__ */
