#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - executes the given command
 * @command: the command to execute
 */
void execute_command(char *command)
{
    char *arguments[MAX_COMMAND_LENGTH / 2 + 1];
    char *token;
    int i = 0;

    // Tokenize the command string
    token = strtok(command, " ");
    while (token != NULL && i < MAX_COMMAND_LENGTH / 2) {
        arguments[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    arguments[i] = NULL;

    // Check if the command exists in the PATH
    if (access(arguments[0], X_OK) == 0) {
        // Fork a child process
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            execve(arguments[0], arguments, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else { // Parent process
            wait(NULL);
        }
    } else {
        printf("Command not found: %s\n", arguments[0]);
    }
}

/**
 * main - entry point
 * Return: 0 on success, otherwise 1
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove the trailing newline

        if (strcmp(command, "exit") == 0) {
            break;
        }

        execute_command(command);
    }

    return 0;
}
