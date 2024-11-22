// Write a C program which creates a child process to run linux/ unix command or any user defined
// program. The parent process set the signal handler for death of child signal and Alarm signal. If
// a child process does not complete its execution in 5 second then parent process kills child process.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid;

void handle_sigchld(int sig) {
    wait(NULL); // Wait for any child process to terminate
}

void handle_sigalrm(int sig) {
    printf("\nChild process did not complete in 5 seconds. Killing child process...\n");
    kill(pid, SIGKILL); // Kill the child process
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    signal(SIGCHLD, handle_sigchld); // Handle child process termination
    signal(SIGALRM, handle_sigalrm); // Handle alarm signal

    pid = fork(); // Create a child process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child process is executing the command: %s\n", argv[1]);
        execvp(argv[1], &argv[1]); // Execute the command

        // If execvp returns, it means there was an error
        perror("exec failed");
        exit(1);
    } else {
        // Parent process
        alarm(5); // Set an alarm for 5 seconds
        pause();  // Wait for signals (SIGCHLD or SIGALRM)
    }

    return 0;
}



// [smile@localhost slip os 6sem]$ ./a.out sleep 10
// Child process (PID: 6374) is executing the command: sleep

// Child process did not complete in 5 seconds. Killing child process (PID: 6374)...
