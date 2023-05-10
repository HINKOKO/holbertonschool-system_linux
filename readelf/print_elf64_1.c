#include "hreadelf.h"

/**
 * 
 * 
 * 
*/

void print_OS_ABI(unsigned char *bytes)
{
	osabi_t osabi_array[] = {
		{ELFOSABI_NONE, "Unix - System V"},
		{ELFOSABI_SYSV, "Unix - System V"},
		{ELFOSABI_HPUX, "HP-UX"},
		{ELFOSABI_NETBSD, "NetBSD"},
		{ELFOSABI_GNU, "GNU ELF"},
		{ELFOSABI_LINUX, "Unix - Linux"},
		{ELFOSABI_SOLARIS, "Sun Solaris"},
		{ELFOSABI_STANDALONE, "Standalone (embedded)"},
	}
}
