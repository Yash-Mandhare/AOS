// Write a C program which creates a child process to run linux/ unix command or any user defined
// program. The parent process set the signal handler for death of child signal and Alarm signal. If
// a child process does not complete its execution in 5 second then parent process kills child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid; // Global variable to hold child PID

// Signal handler for child termination
void handle_sigchld(int sig) {
	int errno;
    int saved_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0); // Clean up terminated child
    errno = saved_errno; // Restore saved errno
}

// Signal handler for alarm
void handle_alarm(int sig) {
    printf("Child process is taking too long. Terminating it...\n");
    kill(child_pid, SIGKILL); // Kill the child process
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Set up signal handlers
    signal(SIGCHLD, handle_sigchld);
    signal(SIGALRM, handle_alarm);

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // In child process
        execvp(argv[1], &argv[1]); // Execute the command
        perror("execvp failed"); // If execvp returns, there was an error
        exit(1);
    } else {
        // In parent process
        alarm(5); // Set an alarm for 5 seconds

        // Wait for the child to finish
        int status;
        waitpid(child_pid, &status, 0);
        alarm(0); // Cancel the alarm if child finishes in time

        if (WIFEXITED(status)) {
            printf("Child terminated with exit status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally\n");
        }
    }

    return 0;
}


// [smile@localhost slip os 6sem]$ ./a.out sleep 10
// Child process is taking too long. Terminating it...
// Child terminated abnormally
