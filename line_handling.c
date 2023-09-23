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

	for (i = strlen(str) - 1; i >= 0; i--)
	{
		if (str[i] == c)
			return (str + i);
	}

	return (NULL);
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

	strncpy(substring, string + start_index, end_index - start_index + 1);
	substring[end_index - start_index + 1] = '\0';

	return (substring);
}
