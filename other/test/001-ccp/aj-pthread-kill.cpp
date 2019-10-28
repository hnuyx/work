
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        pthread_t tid = atol(argv[1]);
        pthread_kill(tid, 14);
    }

    return 0;
}
