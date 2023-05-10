#include "hreadelf.h"

/**
 * print_elf64 - print the ELF file with 64bits logic
 * @elf64: Elf64_Ehdr struct bytes containing informations
 * about the ELF file we are rendering
*/

void print_elf64(Elf64_Ehdr elf64)
{
	print_OS_ABI(elf64.e_ident);
	print_file_type(elf64.e_type);
	print_architecture(elf64.e_machine);
	print_file_version(elf64.e_version);
	print_entry_point(elf64.e_entry);
	print_htable_offset(elf64.e_phoff);
	print_stable_offset(elf64.e_shoff);
	print_flags_preproc(elf64.e_flags);
	print_header_size(elf64.e_ehsize);
	print_htable_size(elf64.e_phentsize);
	print_htable_num(elf64.e_phnum);
	print_stable_size(elf64.e_shentize);
	print_stable_num(elf64.e_shnum);
	print_string_idx(elf64.e_shstrndx);
}


