
#include <stdio.h>
#include <unistd.h>

#include "hl-udp-multicast.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: %s <server|client>\n", argv[0]);
        return -1;
    }

    if(argv[1][0] == 's')
    {
        HLUdpMultiCast hlumc(UDP_SERVER);
        while(true)
        {
            hlumc.send_heartbeat();
            sleep(1);
        }
    }
    else
    {
        HLUdpMultiCast hlumc(UDP_CLIENT);
        while(true)
        {
            printf("%d\n", hlumc.recv_data());
            sleep(1);
        }
    }
}
