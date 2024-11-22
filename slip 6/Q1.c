// Display all the files from current directory which are created in particular month

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Use execlp to execute the shell command with pipe
    execlp("sh", "sh", "-c", "ls -l --time-style=+%b | grep 'Nov'", (char *)NULL);

    // If execlp fails, print an error
    perror("execlp failed");
    return 1;
}



// [smile@localhost slip os 6sem]$ ./a.out 
// -rwxrwxr-x. 1 smile smile 8408 Nov a.out
// -rwxrw-rw-. 1 smile smile   12 Nov file1.txt
// -rw-rw-r--. 1 smile smile   93 Nov output.txt
// -rw-rw-r--. 1 smile smile  555 Nov q1.c
// drwxr-xr-x. 2 smile smile    6 Nov smile
