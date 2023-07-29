#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination buffer to copy the string.
 * @src: The source string to be copied.
 *
 * Return: Pointer to the destination buffer.
 *
 * This function copies the string pointed to by src to the buffer pointed
 * to by dest. It returns a pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 *
 * This function duplicates the given string str by dynamically allocating
 * memory for it and copying the contents. It returns a pointer to the
 * duplicated string. If memory allocation fails, it returns NULL.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 *
 * This function prints the given input string to the standard output.
 * It iterates through the string and calls _putchar to print each character.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 *
 * This function writes the character c to the standard output. It uses
 * a static buffer buf and WRITE_BUF_SIZE to optimize the output by flushing
 * the buffer only when necessary (using BUF_FLUSH). It returns 1 on success.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
