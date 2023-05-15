#include "hreadelf.h"

/**
 * print_infos - displays infos accroding to differents
 * arrays defined regarding to the fields inspected in header
 * @infos: struct of infos
 * @size: size of that struct
 * @matching: code to find in the struct when parsing
*/

void print_infos(infos_t *infos, size_t size, Elf64_Half matching)
{
	size_t i, found = 0;

	for (i = 0; i < size; i++)
	{
		if (infos[i].macro_code == matching)
		{
			printf("%s\n", infos[i].str);
			found = 1;
			break;
		}
	}
	if (found != 1)
		/* No match ELFOSABINONE ==> Unix - System V */
		printf("%s", infos[0].str);
}

/**
 * print_file_version - dsiplay the file version
 * @version: Elf64_Word e_version => object file version
*/

void print_file_version(Elf64_Word version)
{
	infos_t obj_version[] = {
		{EV_NONE, "Invalid ELF Version"},
		{EV_CURRENT, "0x1"},
		{EV_NUM, "0x2"},
	};
	printf("%6s%-28c%i", "Version", ':', EV_CURRENT);
	print_infos(obj_version, 3, version);
}
/**
 * print_architecture - print the machine architecture
 * @machine: Architecure e_machine
*/

void print_architecture(Elf64_Half machine)
{
	infos_t archi[] = {
		{EM_NONE, "No Machine"},
		{EM_M32, "AT&T WE 32100"},
		{EM_SPARC, "SUN SPARC"},
		{EM_386, "Intel 80386"},
		{EM_X86_64, "Advanced Micro Devices X86-64"},
	};
	printf("%6s%-28c", "Machine", ':');
	print_infos(archi, 5, machine);
}
/**
 * print_type - displays the type of file the ELF is about
 * @type: Elf64_Half => Object file type e_type (elf.h)
*/

void print_type(Elf64_Half type)
{
	infos_t type_array[] = {
		{ET_NONE, "No file type"},
		{ET_REL, "REL (Relocatable file)"},
		{ET_EXEC, "EXEC (Executable file)"},
		{ET_DYN, "DYN (Shared object file)"},
		{ET_CORE, "CORE (Core file)"},
	};
	printf("%6s%-28c", "Type", ':');
	print_infos(type_array, 5, type);
}

/**
 * print_OS_ABI - print the OS Version
 * @bytes: our bytes array
*/

void print_OS_ABI(unsigned char *bytes)
{
	infos_t osabi_array[] = {
		{ELFOSABI_NONE, "Unix - System V"},
		{ELFOSABI_SYSV, "Unix - System V"},
		{ELFOSABI_HPUX, "Unix - HP-UX"},
		{ELFOSABI_NETBSD, "Unix - NetBSD"},
		{ELFOSABI_LINUX, "Unix - Linux"},
		{ELFOSABI_SOLARIS, "Unix - Solaris"},
	};
	printf("%6s%-28c", "OS/ABI", ':');
	print_infos(osabi_array, 6, bytes[EI_OSABI]);
	printf("%6s%-28c%d\n", "ABI Version", ':', bytes[EI_ABIVERSION]);
}
