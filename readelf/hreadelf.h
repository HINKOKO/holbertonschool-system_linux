#ifndef __HELF__
#define __HELF__

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <elf.h>

/* MAIN PRINT OF HEADER */
void print_elf_header(unsigned char *bytes, int class, int endian);
/* printer functions for header */
void print_magic(unsigned char *bytes);
void print_class(unsigned char *bytes);
void print_data(unsigned char *bytes);
void print_version(unsigned char *bytes);
void print_osabi_2(unsigned char osabi);
void print_osabi(unsigned char *bytes);
void print_abi_version(unsigned char *bytes);
void print_type(unsigned char *bytes, int endianess);
void print_machine(unsigned char *bytes, int endianess);
void print_machine_2(uint16_t machine);
void print_file_version(unsigned char *bytes, int endian);
void print_entrypt(unsigned char *bytes, int class, int endian);
void print_start_header(unsigned char *bytes, int class, int endian);
void print_start_section(unsigned char *bytes, int class, int endian);
void print_flags(unsigned char *bytes, int class, int endian);
void print_size_header(unsigned char *bytes, int class, int endian);
void print_size_prog(unsigned char *bytes, int class, int endian);
void print_num_prog(unsigned char *bytes, int class, int endian);
void print_section_size(unsigned char *bytes, int class, int endian);
void print_num_hsection(unsigned char *bytes, int class, int endian);
void print_string_table(unsigned char *bytes, int class, int endian);

/* TOOL BOX */

int read_elf_header_bytes(unsigned char *bytes, const char *filename);
int check_elf_magic(unsigned char *bytes);
void swapper(unsigned char *bytes, size_t size);

#endif /* __HELF__ */
