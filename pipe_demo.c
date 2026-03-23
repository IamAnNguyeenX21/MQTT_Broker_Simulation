#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main ()
{
    int fd[2];
    if (pipe(fd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) 
    {
        // Child process
        // close(fd[0]); // Close the read end of the pipe
        // char message[] = "Hello from the child process!";
        // write(fd[1], message, strlen(message) + 1);
        // close(fd[1]); // Close the write end of the pipe
        // exit(EXIT_SUCCESS);
        close(fd[1]); 
        char buffer[BUFFER_SIZE];
        ssize_t bytesRead;
        while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE - 1)) > 0) 
        {
            buffer[bytesRead] = '\0';
            printf("Received message: %s\n", buffer);
        }
        close(fd[0]);
        printf("Child process exiting.\n");
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        // close(fd[1]); // Close the write end of the pipe
        // char buffer[BUFFER_SIZE];
        // read(fd[0], buffer, BUFFER_SIZE);
        // printf("Received message: %s\n", buffer);
        // close(fd[0]); // Close the read end of the pipe
        // wait(NULL); // Wait for the child process to finish
        close(fd[0]);
        char message[] = "Hello from the parent process!";
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
        wait(NULL);
        printf("Parent process exiting.\n");
    }
    return 0;
}