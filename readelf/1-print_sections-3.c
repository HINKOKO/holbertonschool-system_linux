#include "hreadelf.h"

/**
 * print_section_hname - print header field of section table
 * @class: 32/64 bit flag int
 */

void print_section_hname(int class)
{
	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            ");
	if (class == ELFCLASS32)
		printf("Addr     Off    Size   ES Flg Lk Inf Al\n");
	else
		printf("Address         Off     Size   ES Flg Lk Inf Al\n");
}

/**
 * print_key_match_flags - print explanation for flags
 * @class: 32/64 bits flag int
 */

void print_key_match_flags(int class)
{
	printf("Key to Flags:\n");

	printf("  W (write), A (alloc) X (execute), M (merge), S (strings)");

	if (class == ELFCLASS64)
		printf(", l (large)");
	printf("\n  I (info), L (link order), G (group), T (TLS), %s\n",
		   "E (exclude), x (unknown)");
	printf("  O (extra OS processing required) o (OS specific), %s\n",
		   " p (processor specific)");
}
