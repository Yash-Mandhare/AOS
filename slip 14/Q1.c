// Display all the files from current directory whose size is greater that n Bytes Where n is accept from user.


#include <unistd.h>
#include <stdio.h>

int main() {
    char size[32]; // Buffer for the size condition

    // Prompt user for the size condition
    printf("Enter the size condition (e.g., +500c for > 500 bytes): ");
    scanf("%31s", size);

    // Execute the find command with the given size
    execlp("find", "find", ".", "-size", size, "-ls", (char *)NULL);

    // If execlp returns, it indicates an error
    perror("execlp failed");
    return 1;
}


// [smile@localhost slip os 6sem]$ ./a.out 
// Enter the size limit (in bytes): 8
// Files larger than 8 bytes:
// q1.c: 1356 bytes
// output.txt: 78 bytes
// a.out: 8880 bytes
