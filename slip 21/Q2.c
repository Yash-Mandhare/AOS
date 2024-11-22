// Write a C program which receives file names as command line arguments and display those
// filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>  // Add this line to include string.h for strcat

int main(int argc, char *argv[]) {
    // Check if the number of arguments is less than 2 (meaning no files provided)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    // Prepare the command to execute
    char command[1024] = "ls -l";
    int i;
    // Add all the files provided in the command-line arguments to the ls command
    for (i = 1; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    // Add the sorting part of the command
    strcat(command, " | sort -k5,5n");

    // Execute the constructed command
    execlp("sh", "sh", "-c", command, (char *)NULL);

    // If execlp fails, print an error
    perror("execlp failed");
    return 1;
}



// [smile@localhost slip os 6sem]$ ./a.out file1.txt file2.txt
// Files sorted by size (ascending order):
// file1.txt: 0 bytes
// file2.txt: 0 bytes