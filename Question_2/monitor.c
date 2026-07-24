#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    // fork to make a new process
    pid_t pid = fork();

    if (pid == 0) {
        // child process here. making it get stuck on purpose
        printf("Child Process (PID: %d) is running...\n", getpid());
        sleep(10); // simulates freezing
        exit(0);
    } else if (pid > 0) {
        // parent process monitoring the kid
        int status;
        printf("Parent monitoring child (PID: %d). Waiting 3 seconds...\n", pid);
        sleep(3); 

        // check if child is still running. WNOHANG makes sure we don't get stuck waiting
        pid_t result = waitpid(pid, &status, WNOHANG);
        if (result == 0) {
            printf("Child is unresponsive. Terminating...\n");
            kill(pid, SIGKILL); // send the kill signal

            // wait again to clean up the zombie process
            waitpid(pid, &status, 0); 
            printf("Child terminated and zombie prevented.\n");
        } else {
            printf("Child finished normally.\n");
        }
    } else {
        perror("fork failed");
    }
    return 0;
}
