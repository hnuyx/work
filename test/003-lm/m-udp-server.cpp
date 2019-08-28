
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in addr;
    struct sockaddr_in addr;
    int sockfd;
    char buf[128];
    socklen_t socklen = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed %d-%s\n", errno, strerror(errno));
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = inet_addr("239.3.0.1");
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //addr.sin_addr.s_addr = inet_addr("172.16.2.124");
    addr.sin_port = htons(8000);

#if 0
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("bind failed %d-%s\n", errno, strerror(errno));
        return -1;
    }
#endif

#if 0
    int loop = 1;
    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0)
    {
        printf("setsockopt IP_MULTICAST_LOOP failed %d-%s\n", errno, strerror(errno));
        return -1;
    }
#endif

#if 0
    struct in_addr local_addr;
    local_addr.s_addr = inet_addr("172.16.2.124");
    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &local_addr, sizeof(local_addr)) < 0)
    {
        printf("setsockopt IP_MULTICAST_IF failed %d-%s\n", errno, strerror(errno));
        return -1;
    }
#endif

#if 0
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("239.3.0.1");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    //mreq.imr_interface.s_addr = inet_addr("127.0.0.1");
    //mreq.imr_interface.s_addr = inet_addr("172.16.2.124");
    if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        printf("setsockopt IP_ADD_MEMBERSHIP failed %d-%s\n", errno, strerror(errno));
        return -1;
    }
#endif

    while(true)
    {
        snprintf(buf, 128, "hello world, udp multicast");
        size_t len = strlen(buf);
        if(sendto(sockfd, buf, len, 0, (struct sockaddr *) &addr, socklen) < 0)
        {
            printf("sendto failed %d-%s\n", errno, strerror(errno));
            return -1;
        }
        printf("send success: %s\n", buf);
        sleep(1);
    }

    return 0;
}
