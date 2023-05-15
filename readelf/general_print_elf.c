#include "hreadelf.h"

/**
 * print_elf64 - print the ELF file with 64bits logic
 * @elf64: Elf64_Ehdr struct bytes containing informations
 * about the ELF file we are rendering
*/

void print_elf64(Elf64_Ehdr elf64)
{
	print_OS_ABI(elf64.e_ident);
	print_type(elf64.e_type);
	print_architecture(elf64.e_machine);
	print_file_version(elf64.e_version);
	print_entrypt(elf64.e_entry);
	print_start_sections(elf64);
	print_flags(elf64.e_flags);
	print_header_infos(elf64);




}


