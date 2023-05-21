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

/* MAIN PRINT OF SECTION */
void print_elf_section_header(unsigned char *bytes, char *filename,
							  int class, int endian);
/* printer functions for sections */
void print_elf_sections_loop(unsigned char *bytes, int class, int endian,
							 int num_sections, int hsize, unsigned char *str_table);
void print_section_name(unsigned char *bytes, int class, int endian,
						unsigned char *strtable);
void print_section_type(unsigned char *bytes, int class, int endian);
void print_section_addr(unsigned char *bytes, int class, int endian);
void print_section_off(unsigned char *bytes, int class, int endian);
void print_section_size(unsigned char *bytes, int class, int endian);
void print_section_entry_size(unsigned char *bytes, int class, int endian);
void print_section_flags(unsigned char *bytes, int class, int endian);
void print_section_link(unsigned char *bytes, int class, int endian);
void print_section_info(unsigned char *bytes, int class, int endian);
void print_section_addralign(unsigned char *bytes, int class, int endian);
void print_section_hname(int class);
void print_key_match_flags(int class);

/* getters functions for sections */
uint64_t get_section_size(unsigned char *bytes, int class, int endian);
Elf64_Off get_section_offset(unsigned char *bytes, int class, int endian);
uint16_t get_string_tabidx(unsigned char *bytes, int class, int endian);
uint16_t get_size_hsection(unsigned char *bytes, int class, int endian);
uint16_t get_number_sections(unsigned char *bytes, int class, int endian);
void *get_section_header_start(unsigned char *bytes, int class, int endian);
char *get_section_type(uint32_t type);
char *get_section_type2(uint32_t type);

/* TOOL BOX */

int read_elf_header_bytes(unsigned char *bytes, const char *filename);
int check_elf_magic(unsigned char *bytes);
void swapper(unsigned char *bytes, size_t size);
int read_bytes(unsigned char **bytes, const char *filename,
			   size_t offset, size_t size);

#endif /* __HELF__ */
