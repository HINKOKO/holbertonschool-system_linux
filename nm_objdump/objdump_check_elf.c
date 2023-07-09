#include "objdump.h"

/**
 * check_elf - check validity of pretending Elf file
 * @elf: pointer to array of chars argument
 * Return: 1 if all '&&' conditions are true,
 * Necessary to continue execution of code in 'elf_data'
 * 0 otherwise
*/

int check_elf(unsigned char *elf)
{
	return (elf[EI_MAG0] == 0x7f
			&& elf[EI_MAG1] == 'E'
			&& elf[EI_MAG2] == 'L'
			&& elf[EI_MAG3] == 'F');
}
