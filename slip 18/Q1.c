// Read the current directory and display the name of the files, no of files in current directory

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    int i;
    for (i = 1; i < argc; i++)
    {
        if (access(argv[i], F_OK) == 0)
        {
            printf("%s: Found\n", argv[i]);
        }
        else
        {
            printf("%s: Not Found\n", argv[i]);
        }
    }

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out file1.txt 
// file1.txt: Found
