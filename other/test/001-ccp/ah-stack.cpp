#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
 
int main()
{
    struct rlimit lmt;
    getrlimit(RLIMIT_STACK,&lmt);
    printf("rlim_cur=%u,rlim_max=%u\n",lmt.rlim_cur,lmt.rlim_max);

    lmt.rlim_cur *= 2;
    setrlimit(RLIMIT_STACK,&lmt);

    getrlimit(RLIMIT_STACK,&lmt);
    printf("rlim_cur=%u,rlim_max=%u\n",lmt.rlim_cur,lmt.rlim_max);

    return 0;
}
