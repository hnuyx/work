
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int opt;
    const char *optstring = "ab:c::d:";

    while((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch(opt)
        {
        case 'a':
            printf("opt a==%c\n", opt);
            break;
        case 'b':
            printf("opt b==%c, arg: %s\n", opt, optarg);
            break;
        case 'c':
            printf("opt c==%c, arg: %s\n", opt, optarg);
            break;
        case 'd':
            printf("opt d==%c, arg: %s\n", opt, optarg);
            break;
        default:
            printf("error opt %c");
            return -1;
        }
    }

    return 0;
}
