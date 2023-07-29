#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1) {
        printf("shell> ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char **args = (char **)malloc(2 * sizeof(char *));
            args[0] = command;
            args[1] = NULL;
            execvp(command, args);
            perror("execvp");
            free(args);
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }

    return 0;
}
