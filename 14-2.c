#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
    printf("Receive signal %d, CTRL-C pressed\n", nsig);
}

void my_handler_2(int nsig) {
    printf("Receive signal %d, CTRL-4 pressed\n", nsig);
}

int main(void) {
    //
    // Set the process response to SIGINT, SIGQUIT signals
    //
    (void) signal(SIGINT, my_handler);
    (void) signal(SIGQUIT, my_handler_2);
    
    //
    // From this point, the process will print SIGINT, SIGQUIT messages.
    //
    while (1);
    return 0;
}
