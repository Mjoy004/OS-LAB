#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct stat fileStat;
    int fd = open("test.txt", O_RDONLY); // Open file in read mode

    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    if (stat("test.txt", &fileStat) < 0) {
        perror("Error getting file stats");
        close(fd);
        return 1;
    }

    printf("File size: %ld bytes\n", fileStat.st_size);
    
    close(fd); // Close file descriptor
    return 0;
}
