// This is a simple C program that illustrates usage of process in linux OS. 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main () {

    printf("Hello, World!\n");
    pid_t pid = fork(); 
    if (pid < 0) { // error
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { // child process
        printf("This is the child process with PID: %d\n", getpid());
        execlp("/bin/ls", "ls", NULL); // execute ls command
    }
    else { // parent process
        wait(NULL); // wait for child process to finish
        printf("Child process finished. This is the parent process with PID: %d\n", getpid());
    }
    printf("Hello, World!\n");
    return 0;
}