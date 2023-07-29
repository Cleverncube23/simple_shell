#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int _erratoi(const char *str, bool *error) {
    char *endptr;
    long int result = strtol(str, &endptr, 10);

    /* Check for conversion errors */
    if (*endptr != '\0') {
        *error = true;
        return 0;
    }

    *error = false;
    return (int)result;
}
