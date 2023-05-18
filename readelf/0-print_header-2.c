#include "hreadelf.h"

/**
 * print_machine_2 - Print machine architecture
 * @machine: machine architecture
 */

void print_machine_2(uint16_t machine)
{
	switch (machine)
	{
	case EM_ARM:
		puts("ARM");
		break;
	case EM_VAX:
		puts("Stand-alone (embedded)");
		break;
	case EM_X86_64:
		puts("Advanced Micro Devices X86-64");
		break;
	default:
		printf("%d\n", machine);
		break;
	}
}

/**
 * print_machine - Print machine architecture
 * @bytes: character array
 * @endianess: LSB or MSB
 */
void print_machine(unsigned char *bytes, int endianess)
{
	uint16_t machine = ((Elf64_Ehdr *)bytes)->e_machine;

	if (endianess == ELFDATA2MSB)
		swapper((unsigned char *)&machine, 2);
	printf("  Machine:				");
	switch (machine)
	{
	case EM_NONE:
		puts("Unknown machine");
		break;
	case EM_SPARC:
		puts("Sparc");
		break;
	case EM_386:
		puts("Intel 80386");
		break;
	case EM_860:
		puts("Intel 80860");
		break;
	default:
		print_machine_2(machine);
	}
}

/**
 *
 *
 *
 */

void print_file_version(unsigned char *bytes, int endian)
{
	uint16_t f_version = ((Elf64_Ehdr *)bytes)->e_version;

	if (endian == ELFDATA2MSB)
		swapper((unsigned char *)&f_version, 2);

	printf("  Version				");
	switch (f_version)
	{
	case EV_NONE:
	case EV_CURRENT:
		puts("0x1");
		break;
	default:
		printf("%#x\n", f_version);
	}
}

/**
 *
 *
 */

void print_entrypt(unsigned char *bytes, int class, int endian)
{
	Elf64_Addr *entry64;
	Elf32_Addr *entry32;

	printf("  Entry point address:			");
	if (class == ELFCLASS32)
	{
		entry32 = &((Elf32_Ehdr *)bytes)->e_entry;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)entry32, 4);
		printf("0x%x\n", *entry32);
	}
	else
	{
		entry64 = &((Elf64_Ehdr *)bytes)->e_entry;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)entry64, 8);
		printf("0x%lx\n", *entry64);
	}
}

/**
 *
 *
 *
 */

void print_start_header(unsigned char *bytes, int class, int endian)
{
	Elf64_Off *h64;
	Elf32_Off *h32;

	printf("  Start of program headers:		");
	if (class == ELFCLASS32)
	{
		h32 = &((Elf32_Ehdr *)bytes)->e_phoff;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)h32, 4);
		printf("%u", *h32);
	}
	else
	{
		h64 = &((Elf64_Ehdr *)bytes)->e_phoff;
		if (endian == ELFDATA2MSB)
			swapper((unsigned char *)h64, 8);
		printf("%lu", *h64);
	}
	puts(" (bytes into file)");
}
