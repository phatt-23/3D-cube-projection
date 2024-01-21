#include "keyboard.h"
#include <stdio.h>
#include <unistd.h>


int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Save old terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set the terminal to non-blocking mode
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set file descriptor to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Attempt to read a character
    ch = getchar();

    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Restore file descriptor status
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // If a character was read, put it back into the input stream
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


