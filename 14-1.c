#include <signal.h>

int main(void) {
    //
    // Set the process response to SIGINT, SIGQUIT signals to ignore
    //
    (void) signal(SIGINT, SIG_IGN);
    (void) signal(SIGQUIT, SIG_IGN);
    
    //
    // From this point, the process will ignore the occurrence of SIGINT, SIGQUIT signals.
    //
    while (1);
    return 0;
}
