#include "hreadelf.h"
/**
 * print_entrypt - print the entry point address
 * 
 * 
*/

void print_entrypt(Elf64_Addr entry_pt)
{
	printf("%21s%-28c0x%lx\n", "Entry point address", ':', entry_pt);
}
