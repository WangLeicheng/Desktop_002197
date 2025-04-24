#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

int main() {
    int socket_pair[2];
    pid_t pid;
    char buf[128];

    // Create a socket pair
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) == -1) {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(socket_pair[0]); // Close parent's end

        const char *msg = "Hello from child!";
        write(socket_pair[1], msg, strlen(msg) + 1);

        read(socket_pair[1], buf, sizeof(buf));
        printf("Child received: %s\n", buf);

        close(socket_pair[1]);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(socket_pair[1]); // Close child's end

        const char *msg = "Hello from parent!";
        write(socket_pair[0], msg, strlen(msg) + 1);

        read(socket_pair[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);

        close(socket_pair[0]);
        wait(NULL); // Wait for child to exit
    }

    return 0;
}
