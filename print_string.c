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
 * free_s - Frees
 * @buf: buffer
 * @buff: buffer
 * @bufff: buffer
 * @buffff: buffer
 * 
 * Return: nothing
*/
void free_s(char *buf, char *buff, char *bufff, char *buffff)
{
    free_all(buf, buff);
	free_all(bufff, buffff);
}
