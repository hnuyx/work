
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int opt, lopt, loidx;
    const char *optstring = "ab:c::d:";
    const struct option long_options[] =
    {
        {"help", no_argument, &lopt, 1},
        {"version", no_argument, &lopt, 2},
        {"infile", required_argument, &lopt, 3},
        {"outfile", required_argument, &lopt, 4},
        {"logfile", optional_argument, &lopt, 5},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, optstring, long_options, &loidx)) != -1)
    {
        if(opt == 0)
            opt = lopt;
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
        case 1:
            printf("opt help==%d\n", opt);
            break;
        case 2:
            printf("opt version==%d\n", opt);
            break;
        case 3:
            printf("opt infile==%d arg: %s\n", opt, optarg);
            break;
        case 4:
            printf("opt outfile==%d arg: %s\n", opt, optarg);
            break;
        case 5:
            printf("opt logfile==%d arg: %s\n", opt, optarg);
            break;
        default:
            printf("error opt %c");
            return -1;
        }
    }

    return 0;
}
