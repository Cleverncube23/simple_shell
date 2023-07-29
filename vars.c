#include "shell.h"

/**
 * is_chain - Checks if the current character in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it is a chain delimiter, 0 otherwise.
 *
 * This function checks if the character at position buf[*p] and the next character
 * in the buffer form a chain delimiter (|| or && or ;). If a chain delimiter is found,
 * it replaces the delimiter with a null terminator and updates the cmd_buf_type field
 * in the info struct to indicate the type of chain delimiter. The pointer p is updated
 * to the next position in the buffer after the delimiter. If no chain delimiter is found,
 * the function returns 0.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
        size_t j = *p;

        if (buf[j] == '|' && buf[j + 1] == '|')
        {
                buf[j] = '\0';
                j++;
                info->cmd_buf_type = CMD_OR;
        }
        else if (buf[j] == '&' && buf[j + 1] == '&')
        {
                buf[j] = '\0';
                j++;
                info->cmd_buf_type = CMD_AND;
        }
        else if (buf[j] == ';') /* found end of this command */
        {
                buf[j] = '\0'; /* replace semicolon with null terminator */
                info->cmd_buf_type = CMD_CHAIN;
        }
        else
                return (0);
        *p = j;
        return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 *
 * This function checks the cmd_buf_type field in the info struct to determine whether
 * we should continue chaining commands based on the last exit status. If the last
 * command was a logical AND (&&) and the last status is non-zero (indicating failure),
 * it stops further command execution by replacing the characters from position i to len
 * in the buffer with null terminators. Similarly, if the last command was a logical OR (||)
 * and the last status is zero (indicating success), it stops further command execution
 * in the same way.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (info->cmd_buf_type == CMD_AND)
        {
                if (info->status)
                {
                        buf[i] = '\0';
                        j = len;
                }
        }
        if (info->cmd_buf_type == CMD_OR)
        {
                if (!info->status)
                {
                        buf[i] = '\0';
                        j = len;
                }
        }

        *p = j;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 * This function replaces the first occurrence of the command (stored in info->argv[0])
 * that matches an alias in the alias list with the alias value. It does this by searching
 * for the command in the alias list and extracting the value after the '=' character.
 * The memory for the replaced command (info->argv[0]) is freed, and a new copy of the
 * alias value is assigned to info->argv[0]. The function returns 1 if an alias is replaced
 * successfully, and 0 if no matching alias is found.
 */
int replace_alias(info_t *info)
{
        int i;
        list_t *node;
        char *p;

        for (i = 0; i < 10; i++)
        {
                node = node_starts_with(info->alias, info->argv[0], '=');
                if (!node)
                        return (0);
                free(info->argv[0]);
                p = _strchr(node->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
                if (!p)
                        return (0);
                info->argv[0] = p;
        }
        return (1);
}

/**
 * replace_vars - Replaces environment variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 * This function replaces the environment variables (strings starting with '$') in the
 * tokenized string (info->argv) with their corresponding values from the environment list.
 * If the variable is "$?", it is replaced with the exit status converted to a string.
 * If the variable is "$$", it is replaced with the process ID converted to a string.
 * For other variables, it searches for a matching variable in the environment list and
 * replaces it with its value. If no matching variable is found, it replaces the variable
 * with an empty string. The function returns 1 if any variable is replaced, otherwise 0.
 */
int replace_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                _strdup("")); /* Temporarily replace with an empty string */
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                _strdup("")); /* Temporarily replace with an empty string */
            continue;
        }
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], _strdup(""));

    }
    return (0);
}

/**
 * replace_string - Replaces a string with a new one.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 *
 * This function replaces the memory for the old string with the new string.
 * It frees the memory occupied by the old string and assigns the new string
 * to the same address. The function returns 1 to indicate that the replacement
 * was successful.
 */
int replace_string(char **old, char *new)
{
        free(*old);
        *old = new;
        return (1);
}
