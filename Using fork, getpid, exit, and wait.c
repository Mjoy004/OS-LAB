#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) { // Child process
        printf("Child process (PID: %d)\n", getpid());
        exit(0); // Child exits
    } 
    else { // Parent process
        printf("Parent process (PID: %d), waiting for child...\n", getpid());
        wait(NULL); // Wait for child to exit
        printf("Child process finished.\n");
    }
    return 0;
}
