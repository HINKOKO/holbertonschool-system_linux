#ifndef __HELF__
#define __HELF__

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <elf.h>

#define LSB 101
#define MSB 102

/**
 * struct infos_s - struct to handle the OS/ABI
 * versionning stored in e_ident[EI_NIDENT]
 * @macro_code: macros associated with it in elf.h
 * @str: the string to print regarding os/abi
 */

typedef struct infos_s
{
	int macro_code;
	char *str;
} infos_t;

/* Printer functions */
int print_helf(FILE *fd, char *args);
void print_magic(unsigned char *bytes);
int print_class(unsigned char *bytes, char *args);
int print_endian(unsigned char *bytes, char *args);
int print_version(unsigned char *bytes, char *args);

/* print 64 */
void print_elf64(Elf64_Ehdr elf64);

void print_OS_ABI(unsigned char *bytes);
void print_type(Elf64_Half type);
void print_architecture(Elf64_Half machine);
void print_file_version(Elf64_Word version);
void print_entrypt(Elf64_Addr entry_pt);
void print_start_sections(Elf64_Ehdr starters);
void print_flags(Elf64_Word elf_flag);
void print_header_infos(Elf64_Ehdr header_infos);

/* print 32 */
void print_elf32(Elf32_Ehdr elf32);

void print_OS_ABI_32(unsigned char *bytes);
void print_type_32(Elf32_Half type);
void print_architecture_32(Elf32_Half machine);
void print_file_version_32(Elf32_Word version);
void print_entrypt_32(Elf32_Addr entry_pt);
void print_start_sections_32(Elf32_Ehdr starters);
void print_flags_32(Elf32_Word elf_flag);
void print_header_infos_32(Elf32_Ehdr header_infos);

/* main printage taking care of the bunch of functions right above*/
void print_infos(infos_t *infos, size_t size, Elf64_Half matching);
void print_infos_32(infos_t *infos, size_t size, Elf32_Half matching);

/* utility functions to perform checks and conversion */
FILE *pick_fd(char *filename);
int check_args(int argc, char **argv);
void swap_endian(void *ptr, size_t size);
void convert_elf32(Elf32_Ehdr elf32, int endian);
void convert_elf64(Elf64_Ehdr elf64, int endian);

/***************** TASK 1 *****************/
/* utilities */
void reverser(unsigned char *bytes, size_t size);
void *get_section_start(unsigned char *bytes, int class, int endian);
uint16_t get_number_sections(unsigned char *bytes, int class, int endian);

#endif /* __HELF__ */
