#ifndef __HNM__
#define __HNM__

#include <elf.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

/* MACROS HELPERS */
#define IS_32 (hdr->Ehdr64->e_ident[EI_CLASS] == ELFCLASS32)
#define IS_MSB (hdr->Ehdr64->e_ident[EI_DATA] == ELFDATA2MSB)

#define SET_EHDR(x) (IS_32 ? (void *)&(hdr->Ehdr32->x) \
	: (void *)&(hdr->Ehdr64->x))
#define SET_SHDR(x, i) (IS_32 ? (void *)&(hdr->Shdr32[i].x) \
	: (void *)&(hdr->Shdr64[i].x))
#define SET_SYM(x, i) (IS_32 ? (void *)&(hdr->Sym32[i].x) \
	: (void *)&(hdr->Sym64[i].x))

#define GET_EHDR(x) (IS_32 ? hdr->Ehdr32->x : hdr->Ehdr64->x)
#define GET_SHDR(x, i) (IS_32 ? hdr->Shdr32[i].x : hdr->Shdr64[i].x)
#define GET_SYM(x, i) (IS_32 ? hdr->Sym32[i].x : hdr->Sym64[i].x)

#define EHDR_SIZE(x) (IS_32 ? sizeof(hdr->Ehdr32->x) : sizeof(hdr->Ehdr64->x))
#define SHDR_SIZE(x, i) (IS_32 ? sizeof(hdr->Shdr32[i].x) \
	: sizeof(hdr->Shdr64[i].x))
#define SYM_SIZE(x, i) (IS_32 ? sizeof(hdr->Sym32[i].x) \
	: sizeof(hdr->Sym64[i].x))

/* retrieve info in ElfXX_Sym => st_info */
#define ELFN_ST_BIND (IS_32 ? ELF32_ST_BIND(hdr->Sym32[i].st_info) \
	: ELF64_ST_BIND(hdr->Sym64[i].st_info))
#define ELFN_ST_TYPE (IS_32 ? ELF32_ST_TYPE(hdr->Sym32[i].st_info) \
	: ELF64_ST_TYPE(hdr->Sym64[i].st_info))

/**
 * struct hdrs - structure to store Elf32//Elf64 infos
 * @map: pointer to memory region mapped
 * @Ehdr64: 64-bit ELF header
 * @Ehdr32: 32-bit ELF header
 * @is_32: flag int status 32/64 bits
 * @is_msb: flag int status MSB/LSB
 * @Shdr64: 64-bit ELF section header
 * @Shdr32: 32-bit ELF section header
 * @Sym64: 64-bit ELF symbol table
 * @Sym32: 32-bit ELF symbol table
*/

typedef struct hdrs
{
	char *map;
	Elf64_Ehdr *Ehdr64;
	Elf32_Ehdr *Ehdr32;
	int is_32;
	int is_msb;
	Elf64_Shdr *Shdr64;
	Elf32_Shdr *Shdr32;
	Elf64_Sym *Sym64;
	Elf32_Sym *Sym32;
} hdrs;

/* GET_INFO */
char get_info(hdrs *hdr, int i);
int sym(hdrs *hdr);
void init_shdr(hdrs *hdr);
void init_ehdr(hdrs *hdr);


/* CONVERT */
void conv_msb(char *ptr, size_t size);



#endif /* __HNM__ */
