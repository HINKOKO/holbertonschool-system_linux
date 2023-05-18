#include "hreadelf.h"

/**
 *
 *
 *
 */

void print_version(unsigned char *bytes)
{
	unsigned char version = ((Elf64_Ehdr *)bytes)->e_ident[EI_VERSION];

	printf("  Version:				%d", version);
	switch (version)
	{
	case (EV_CURRENT):
		puts(" (current)");
		break;
	case (EV_NONE):
	default:
		puts("");
		break;
	}
}

/**
 * print_osabi_2 - Print osabi
 * @osabi: osabi
 */
void print_osabi_2(unsigned char osabi)
{
	switch (osabi)
	{
	case ELFOSABI_OPENBSD:
		puts("OpenBSD");
		break;
	case ELFOSABI_ARM:
		puts("ARM");
		break;
	case ELFOSABI_STANDALONE:
		puts("Stand-alone (embedded)");
		break;
	default:
		printf("<unknown: %x>\n", osabi);
		break;
	}
}

/**
 * print_osabi - Print osabi
 * @bytes: character array
 */
void print_osabi(unsigned char *bytes)
{
	unsigned char osabi = ((Elf64_Ehdr *)bytes)->e_ident[EI_OSABI];

	printf("  OS/ABI:				");
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
	case ELFOSABI_IRIX:
		puts("UNIX - IRIX");
		break;
	default:
		print_osabi_2(osabi);
		break;
	}
}

/**
 *
 *
 */

void print_abi_version(unsigned char *bytes)
{
	unsigned char abi = ((Elf64_Ehdr *)bytes)->e_ident[EI_ABIVERSION];

	printf("  ABI Version:				%d\n", abi);
}

/**
 * print_type - Print elf type
 * @bytes: character array
 * @endianess: LSB or MSB
 */
void print_type(unsigned char *bytes, int endianess)
{
	uint16_t type = ((Elf64_Ehdr *)bytes)->e_type;

	if (endianess == ELFDATA2MSB)
		swapper((unsigned char *)&type, 2);
	printf("  Type:					");
	switch (type)
	{
	case ET_NONE:
		puts("NONE (None)");
		break;
	case ET_REL:
		puts("REL (Relocatable file)");
		break;
	case ET_EXEC:
		puts("EXEC (Executable file)");
		break;
	case ET_DYN:
		puts("DYN (Shared object file)");
		break;
	case ET_CORE:
		puts("CORE (Core file)");
		break;
	default:
		puts("Unknown type");
		break;
	}
}
