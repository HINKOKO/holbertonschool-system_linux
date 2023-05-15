#include "hreadelf.h"

/**
 * print_infos_32 - displays infos accroding to differents
 * arrays defined regarding to the fields inspected in header
 * @infos: struct of infos
 * @size: size of that struct
 * @matching: code to find in the struct when parsing
*/

void print_infos_32(infos_t *infos, size_t size, Elf32_Half matching)
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
		printf("%s\n", infos[0].str);
}

/**
 * print_file_version_32 - dsiplay the file version
 * @version: Elf64_Word e_version => object file version
*/

void print_file_version_32(Elf32_Word version)
{
	/* # for prefixinf the hex output */
	printf("%9s%-28c%#x\n", "Version", ':',
	version == EV_NONE ? EV_NONE : EV_CURRENT);
}
/**
 * print_architecture_32 - print the machine architecture
 * @machine: Architecure e_machine
*/

void print_architecture_32(Elf32_Half machine)
{
	infos_t archi[] = {
		{EM_NONE, "No Machine"},
		{EM_M32, "AT&T WE 32100"},
		{EM_SPARC, "Sparc"},
		{EM_386, "Intel 80386"},
		{EM_X86_64, "Advanced Micro Devices X86-64"},
	};
	printf("%9s%-28c", "Machine", ':');
	print_infos(archi, 5, machine);
}
/**
 * print_type_32 - displays the type of file the ELF is about
 * @type: Elf64_Half => Object file type e_type (elf.h)
*/

void print_type_32(Elf32_Half type)
{
	infos_t type_array[] = {
		{ET_NONE, "No file type"},
		{ET_REL, "REL (Relocatable file)"},
		{ET_EXEC, "EXEC (Executable file)"},
		{ET_DYN, "DYN (Shared object file)"},
		{ET_CORE, "CORE (Core file)"},
	};
	printf("%6s%-31c", "Type", ':');
	print_infos(type_array, 5, type);
}

/**
 * print_OS_ABI_32 - print the OS Version
 * @bytes: our bytes array
*/

void print_OS_ABI_32(unsigned char *bytes)
{
	unsigned char osabi = ((Elf32_Ehdr *)bytes)->e_ident[EI_OSABI];

	printf("%8s%-29c", "OS/ABI", ':');
	switch (osabi)
	{
		case ELFOSABI_SYSV: /* Also ELFOSABI_NONE */
			puts("UNIX - System V");
			break;
		case ELFOSABI_HPUX:
			puts("UNIX - HP-UX");
			break;
		case ELFOSABI_NETBSD:
			puts("UNIX - NetBSD");
			break;
		case ELFOSABI_LINUX:
			puts("UNIX - GNU");
			break;
		case ELFOSABI_SOLARIS:
			puts("UNIX - Solaris");
			break;
		default:
			printf("<unknown: %x>\n", osabi);
			break;
	}
	printf("%14s%24i\n", "ABI Version:", bytes[EI_ABIVERSION]);
}
