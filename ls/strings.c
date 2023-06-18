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

/**
 * _strlen - mimics the strlen function
 * @s: the string to lengify man
 * Return: an int, the len of string
 */

int _strlen(const char *s)
{
	int i = 0;

	while (s[i++] != '\0')
	{
	}
	return (i - 1);
}

/**
 * _strncpy - copies src to dest up to n bytes
 * @dest: pointer to dest
 * @src: ptr to source
 * @n: n bytes
 * Return: dest
 */

char *_strncpy(char *dest, char const *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; ++i)
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
