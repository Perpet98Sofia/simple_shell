#include "main.h"

/**
 * free_all - Frees all resources
 * @strng: string to free
 * @strg: string to free
 *
 * Return: void
 */
void free_all(char *strng, char *strg)
{
	if (strng != NULL)
		free(strng);
	if (strg != NULL)
		free(strg);
}

/**
 * _strrchr - searches for the last occurrence of the character c
 * @str: Parameter as *char
 * @c: Parameter as char
 *
 * Return: pointer || NULL
 */
char *_strrchr(char *str, int c)
{
	int i;

	for (i = _strlen(str) - 1; i >= 0; i--)
	{
		if (str[i] == c)
			return (str + i);
	}

	return (NULL);
}

/**
 * _strlen - count the characters of a string
 * @s: the string
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	if (*s)
		return (1 + _strlen(s + 1));
	return (0);
}

/**
 * extract - Function to extract a string
 * @string: char *
 * @start_index: integer
 * @end_index: integer
 *
 * Return: char
 */
char *extract(char *string, int start_index, int end_index)
{
	char *substring = malloc(sizeof(char) * (end_index - start_index + 1));

	if (substring == NULL)
		return (NULL);

	_strncpy(substring, string + start_index, end_index - start_index + 1);
	substring[end_index - start_index + 1] = '\0';

	return (substring);
}

/**
 * _strncpy - copies a string
 * @dest: Destination
 * @src: Source
 * @n: n as Integer
 * Return: pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int c;

	for (c = 0; c < n && src[c] != '\0'; c++)
		dest[c] = src[c];

	for (; c < n; c++)
		dest[c] = '\0';

	return (dest);
}
