#include "multithreading.h"

/* for strtoul() converts string to unsigned long int */
#include <stdlib.h>

/**
 * prime_factors - factorizes a number into a list of prime factors
 * @s: pointer to string representation of the number to factorize
 *
 * Return: pointer to factorized number list
 */

list_t *prime_factors(char const *s)
{
	unsigned long *factor = NULL, num = 0;
	unsigned long i = 2;
	list_t *list = malloc(sizeof(list_t));

	list_init(list);
	num = strtoul(s, '\0', 10);

	while (num % i == 0)
	{
		factor = malloc(sizeof(unsigned long));
		*factor = i;
		list_add(list, factor);
		num /= i;
	}
	/* then divide by consecutive prime nums */
	for (i = 3; i * i <= num; i += 2)
	{
		while (num % i == 0)
		{
			factor = malloc(sizeof(unsigned long));
			*factor = i;
			list_add(list, factor);
			num /= i;
		}
	}
	/* if a remainder indivisible, add it */
	if (num > 2)
	{
		factor = malloc(sizeof(unsigned long));
		*factor = num;
		list_add(list, factor);
	}
	return (list);
}
