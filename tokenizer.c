#include "shell.h"

/**
 * strtow - Splits a string into words using the given delimiter.
 * @str: The input string to be split.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings (words), or NULL on failure.
 *
 * This function splits the input string str into individual words based on
 * the delimiter d. It returns a dynamically allocated array of strings,
 * each representing a word from the input string. The delimiter can consist
 * of multiple characters. Repeated delimiters are ignored. If the input string
 * is empty or contains only delimiters, it returns NULL. Memory for the array
 * of strings and each word is allocated dynamically, and it is the caller's
 * responsibility to free the memory when it's no longer needed.
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	/* Count the number of words in the input string */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the input string into individual words */
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiters */
		while (is_delim(str[i], d))
			i++;

		/* Calculate the length of the current word */
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		/* Allocate memory for the current word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Free memory in case of failure */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy the current word into the array */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL; /* Null-terminate the array of strings */
	return (s);
}

/**
 * strtow2 - Splits a string into words using a single delimiter character.
 * @str: The input string to be split.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings (words), or NULL on failure.
 *
 * This function is similar to strtow but uses a single delimiter character
 * instead of a delimiter string. It splits the input string str into individual
 * words based on the delimiter d. Repeated delimiters are ignored. If the input
 * string is empty or contains only delimiters, it returns NULL. Memory for the
 * array of strings and each word is allocated dynamically, and it is the caller's
 * responsibility to free the memory when it's no longer needed.
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	/* Count the number of words in the input string */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	/* Split the input string into individual words */
	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip leading delimiters */
		while (str[i] == d && str[i] != d)
			i++;

		/* Calculate the length of the current word */
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		/* Allocate memory for the current word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			/* Free memory in case of failure */
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy the current word into the array */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL; /* Null-terminate the array of strings */
	return (s);
}
