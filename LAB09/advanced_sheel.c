#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 64
#define MAX_HISTORY 10
char *history[MAX_HISTORY];
int history_count = 0;

// Function to read user input
void read_command(char *input)
{
    printf("my_shell> ");
    fgets(input, MAX_COMMAND_LEN, stdin);
    input[strlen(input) - 1] = '\0'; // Remove trailing newline
}
// Function to save command to history
void save_history(char *input)
{
    if (history_count < MAX_HISTORY)
    {
        history[history_count++] = strdup(input);
    }
    else
    {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(input);
    }
}
// Function to print history
void print_history()
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d %s\n", i + 1, history[i]);
    }
}
// Function to parse input into commands and arguments
void parse_command(char *input, char **args)
{
    for (int i = 0; i < MAX_ARGS; i++)
    {
        args[i] = strsep(&input, " ");
        if (args[i] == NULL)
            break;
    }
}
// Function to handle I/O redirection
    void
    handle_redirection(char **args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        if (strcmp(args[i], ">") == 0)
        {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO); // Redirect stdout to file
            close(fd);
            args[i] = NULL; // Remove the redirection symbols from arguments
        }
        else if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i + 1], O_RDONLY);
            dup2(fd, STDIN_FILENO); // Redirect stdin from file
            close(fd);
            args[i] = NULL;
        }
        i++;
    }
}
// Function to handle piping
void handle_piping(char **args)
{
    int pipefd[2];
    pid_t pid;
    char *command1[MAX_ARGS], *command2[MAX_ARGS];
    // Split input into two commands at the pipe "|"
    int i = 0, j = 0;
    while (args[i] != NULL && strcmp(args[i], "|") != 0)
    {
        command1[i] = args[i];
        i++;
    }
    command1[i] = NULL;
    i++; // Skip the "|"
    while (args[i] != NULL)
    {
        command2[j++] = args[i++];
    }
    command2[j] = NULL;
    if (pipe(pipefd) == -1)
    {
        perror("Pipe failed");
        return;
    }
    if ((pid = fork()) == -1)
    {
        perror("Fork failed");
        return;
    }
    if(pid == 0)
    {                                   // Child process
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(command1[0], command1);
        perror("Execution failed");
        exit(1);
    }
    else
    {                                  // Parent process
        wait(NULL);                    // Wait for the child process
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(command2[0], command2);
        perror("Execution failed");
        exit(1);
    }
}
// Function to execute commands
void execute_command(char **args)
{
    if (args[0] == NULL)
        return; // Empty command
    // Built-in commands
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL || chdir(args[1]) != 0)
        {
            perror("cd failed");
        }
        return;
    }
    else if (strcmp(args[0], "history") == 0)
    {
        print_history();
        return;
    }
    pid_t pid = fork();
    int i = 0;
    if (pid < 0)
    {
        perror("Fork failed");
        return;
    }
    if (pid == 0)
    { // Child process
        
        while (args[i] != NULL)
        {
            if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0)
            {
                handle_redirection(args);
            }
            else if (strcmp(args[i], "|") == 0)
            {
                handle_piping(args);
                return;
            }
            i++;
        }
        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    }
    else
    { // Parent process
        if (args[i - 1] == NULL || strcmp(args[i - 1], "&") != 0)
        {
            wait(NULL); // Wait for the child to complete
        }
    }
}
int main()
{
    char input[MAX_COMMAND_LEN];
    char *args[MAX_ARGS];
    while (1)
    {
        read_command(input);
        save_history(input); // Save the command to history
        parse_command(input, args);
        execute_command(args);
    }
    return 0;
}