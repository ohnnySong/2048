#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>

// Function to wait for 0.5 seconds or until input is available
int wait_for_input() {
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    // Wait for 0.5 seconds
    tv.tv_sec = 0;
    tv.tv_usec = 500000;

    ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

    if (ret < 0) {
        perror("select");
        return -1;
    } else if (ret == 0) {
       
        return -1;
    } else {
        // Input available
        return 0;
    }
}
/*
int wait_for_input() {
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    // Wait for 0.5 seconds
    tv.tv_sec = 0;
    tv.tv_usec = 500000;

    ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

    if (ret < 0) {
        perror("select");
        return -1;
    } else if (ret == 0) {
        printf("Input slower!\n");
        return -1;
    } else {
        // Input available
        return 0;
    }
}
*/