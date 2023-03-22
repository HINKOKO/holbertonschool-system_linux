#include "hls.h"

/**
* _strcmp - self strcmp to avoid not allowed function
* @s1: string 1 to be compared
* @s2: string 2 to be compared
* Return: 0 success, 1 failure
*/

int _strcmp(char const *s1, char *s2)
{
	int j = 0, i = 0;

	while (s1[i] != '\0')
		i++;

	while (s1[j] == s2[j] && j < i)
		j++;

	return (s1[j] - s2[j]);
}
