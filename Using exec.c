#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Before exec\n");

    char *args[] = {"ls", "-l", NULL};  // Arguments for exec
    execvp("ls", args);  // Replace process with "ls -l"

    perror("exec failed"); // This will execute only if exec fails
    exit(1);
}
