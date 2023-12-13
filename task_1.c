#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    char buffer[BUFFER_SIZE];
    char *args[100];
    int status;

    while (1) {
        printf("$ ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        char *token = strtok(buffer, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            printf("Command not found\n");
            exit(0);
        } else {
            wait(&status);
        }
    }

    return 0;
}
