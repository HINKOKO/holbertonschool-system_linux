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
 * struct osabi_s - struct to handle the OS/ABI
 * versionning stored in e_ident[EI_NIDENT]
 * @str: the string to print regarding os/abi
 * macro_code: macros associated with it in elf.h
*/

typedef struct osabi_s
{
	char *str;
	int macro_code;
} osabi_t;

/* Printer functions */
int print_helf(FILE *fd, char *args);
void print_magic(unsigned char *bytes);
int print_class(unsigned char *bytes, char *args);
int print_endian(unsigned char *bytes, char *args);
int print_version(unsigned char *bytes, char *args);



/* utility functions to perform checks and conversion */
FILE *pick_fd(char *filename);
int check_args(int argc, char **argv);
void swap_endian(void *ptr, size_t size);
void convert_elf32(Elf32_Ehdr elf32, int endian);
void convert_elf64(Elf32_Ehdr elf32, int endian);

#endif /* __HELF__ */

