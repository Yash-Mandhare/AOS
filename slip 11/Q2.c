// Write a C program that redirects standard output to a file output.txt. (use of dup and open system
// call).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_descriptor;
    
    // Open the file output.txt in write mode. Create it if it doesn't exist.
    file_descriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_descriptor < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor to standard output (stdout)
    if (dup2(file_descriptor, STDOUT_FILENO) < 0) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Close the original file descriptor as it's no longer needed
    close(file_descriptor);

    // Now all output to stdout will be redirected to output.txt
    printf("This will be written to output.txt\n");
    printf("Standard output redirection is successful!\n");

    return 0;
}
