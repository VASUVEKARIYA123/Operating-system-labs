#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_HISTORY_SIZE 50

// Function to parse the input command
void parse_command(char *input, char **args) {
    char *token;
    int i = 0;

    // Tokenize the input command by spaces
    token = strtok(input, " \t\n");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;
}

// Function to execute external commands
void execute_command(char **args) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking error
        perror("shell");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE / 2];
    char *history[MAX_HISTORY_SIZE];
    int history_index = 0;

    while (1) {
        // Display prompt and read user input
        printf("MyShell> ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strlen(input) - 1] = '\0';

        // Check for built-in commands
        if (strcmp(input, "exit") == 0) {
            exit(0);
        } else if (strcmp(input, "history") == 0) {
            for (int i = 0; i < history_index; i++) {
                printf("%s\n", history[i]);
            }
            continue;
        }

        // Store the command in history
        history[history_index] = strdup(input);
        history_index = (history_index + 1) % MAX_HISTORY_SIZE;

        // Parse and execute the command
        parse_command(input, args);
        execute_command(args);
    }

    return 0;
}