#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");  // Display the prompt
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  // Handle "end of file" condition (Ctrl+D)
        }
        command[strcspn(command, "\n")] = 0;  // Remove the newline character

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            execlp(command, command, (char *)NULL);  // Execute the command
            perror("exec failed");
            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);  // Wait for the child process to finish
        }
    }

    return 0;
}

