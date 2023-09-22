#include "main.h"

/**
 * print_string - Print string
 * @format: The string to print
 *
 * Return: The length of the output
 */
int print_string(const char *format)
{
	int len = 0;

	if (format == NULL)
		return (write(1, "", 1));

	while (format[len])
		len++;

	return (write(1, format, len));
}

/**
 * removeSpaces - removes spaces from a stirng
 * @strng: the string to remove in
 *
 * Return: new string
*/
char *removeSpaces(char *strng)
{
	int i;
	char *buf;

	buf = malloc(sizeof(char) * strlen(strng));
	if (buf == NULL)
		return (NULL);

	for (i = 0; strng[i] != ' ' && strng[i] != '\0'; i++)
		buf[i] = strng[i];
	buf[i] = '\0';

	return (buf);
}
