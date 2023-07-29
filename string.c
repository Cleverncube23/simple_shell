#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string whose length to check.
 *
 * Return: The integer length of the string.
 *
 * This function calculates the length of the input string by counting
 * the number of characters until it reaches the null terminator '\0'.
 * If the input string is NULL, it returns 0.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 *
 * This function compares two strings character by character until it
 * finds a difference or reaches the end of both strings. If the characters
 * at the current position are different, it returns the difference of their
 * ASCII values. If both strings are equal, it returns 0. The comparison
 * continues until one of the strings reaches the null terminator.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if the needle starts with the haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack or NULL if not found.
 *
 * This function checks if the substring needle is found at the beginning
 * of the string haystack. It returns the address of the next character after
 * the match if found, or NULL if the substring is not present at the beginning
 * of the string.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 *
 * This function appends the characters from the source buffer (src) to the
 * end of the destination buffer (dest). It returns a pointer to the destination
 * buffer, which contains the concatenated string.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

