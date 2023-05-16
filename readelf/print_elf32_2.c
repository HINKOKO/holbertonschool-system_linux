#include "hreadelf.h"

/**
 * print_entrypt_32 - print the entry point address
 * @entry_pt: entry point of ELF file
 */

void print_entrypt_32(Elf32_Addr entry_pt)
{
	printf("%21s%-16c0x%lx\n", "Entry point address", ':', (uint64_t)entry_pt);
}

/**
 * print_start_sections_32 - print the start of prog
 * and section headers
 * @starters: used to declare a variable for
 * program and sections header table file offset
 */

void print_start_sections_32(Elf32_Ehdr starters)
{
	Elf32_Off prog_headers = starters.e_phoff;
	Elf32_Off section_headers = starters.e_shoff;

	printf("%26s%-11c%li%s\n", "Start of program headers", ':',
		   (uint64_t)prog_headers, " (bytes into file)");
	printf("%26s%-11c%li%s\n", "Start of section headers", ':',
		   (unsigned long int)section_headers, " (bytes into file)");
}

/**
 * print_flags_32 - displays processor specific flags
 * @elf_flag: flag of processor!
 */

void print_flags_32(Elf32_Word elf_flag)
{
	printf("%7s%-30c0x%lx\n", "Flags", ':', (uint64_t)elf_flag);
}

/**
 * print_header_infos_32 - display the infos about program
 * and section headers
 * @header_infos: used to store variables accordingly
 */

void print_header_infos_32(Elf32_Ehdr header_infos)
{
	Elf32_Half size_header = header_infos.e_ehsize;
	Elf32_Half size_prog = header_infos.e_phentsize;
	Elf32_Half num_header = header_infos.e_phnum;
	Elf32_Half size_section_header = header_infos.e_shentsize;
	Elf32_Half num_section_header = header_infos.e_shnum;
	Elf32_Half string_table_idx = header_infos.e_shstrndx;

	printf("%21s%-16c%li%s\n", "Size of this header", ':',
		   (unsigned long int)size_header, " (bytes)");
	printf("%25s%-12c%li%s\n", "Size of program headers", ':',
		   (unsigned long int)size_prog, " (bytes)");
	printf("%27s%-10c%i\n", "Number of program headers", ':', num_header);
	printf("%25s%-12c%li%s\n", "Size of section headers", ':',
		   (unsigned long int)size_section_header, " (bytes)");
	printf("%27s%-10c%i\n", "Number of section headers", ':',
		   num_section_header);
	printf("%35s%-2c%i\n", "Section header string table index", ':',
		   string_table_idx);
}
