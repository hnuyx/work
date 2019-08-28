#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>


#define BUFLEN 255


int main (int argc, char **argv)
{
    struct sockaddr_in peeraddr,ia;
    int sockfd;
    unsigned char loop;
    char recmsg[BUFLEN + 1];
    unsigned int socklen, n;
    struct ip_mreq mreq;
    
    /* 创建 socket 用于UDP通讯 */
    sockfd = socket (AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf ("socket creating err in udptalk\n");
        exit (1);
    }
    /* 设置要加入组播的地址 */
    bzero(&mreq, sizeof (struct ip_mreq));
    
    inet_pton(AF_INET,"239.3.0.1",&ia.sin_addr);
    ia.sin_port = htons(8000);
    /* 设置组地址 */
    bcopy (&ia.sin_addr.s_addr, &mreq.imr_multiaddr.s_addr, sizeof (struct in_addr));
    /* 设置发送组播消息的源主机的地址信息 */
    mreq.imr_interface.s_addr =  htonl (INADDR_ANY);
    
    
    /* 把本机加入组播地址，即本机网卡作为组播成员，只有加入组才能收到组播消息 */
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP , &mreq, sizeof (struct ip_mreq)) == -1)
    {
        perror ("setsockopt");
        exit (-1);
    }
#if 0
    loop = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop,sizeof (loop)) == -1)
    {
        printf("IP_MULTICAST_LOOP set fail!\n");
    }
#endif
    
    socklen = sizeof (struct sockaddr_in);
    memset (&peeraddr, 0, socklen);
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port = htons (7839);
    inet_pton(AF_INET, "239.3.0.1", &peeraddr.sin_addr);
    
#if 0
    /* 绑定自己的端口和IP信息到socket上 */
    if (bind(sockfd, (struct sockaddr *) &peeraddr,sizeof (struct sockaddr_in)) == -1)
    {
        printf ("Bind error\n");
        exit (0);
    }
#endif
    
    /* 循环接收网络上来的组播消息 */
    for (;;)
    {
        bzero (recmsg, BUFLEN + 1);
        n = recvfrom (sockfd, recmsg, BUFLEN, 0, (struct sockaddr *) &ia, &socklen);
        if (n < 0)
        {
            printf ("recvfrom err in udptalk!\n");
            exit (4);
        }
        else{
        /* 成功接收到数据报 */
            recmsg[n] = 0;
            printf ("recv:[%s]\n", recmsg);
        }
        
        printf("Please input:\n");
        bzero (recmsg, BUFLEN + 1);
        if (fgets (recmsg, BUFLEN, stdin) == (char *) EOF)
            exit (0);
        //只向对方回复数据，不向组内其他成员发送数据
        //if (sendto(sockfd, recmsg, strlen (recmsg), 0, (struct sockaddr *) &ia, sizeof ( ia)) < 0)
        //向组内所有成员发送数据，除了自己
        if (sendto(sockfd, recmsg, strlen (recmsg), 0, (struct sockaddr *) &peeraddr, sizeof ( peeraddr)) < 0)
        {
            printf ("sendto error!\n");
            exit (3);
        }
        printf ("send ok\n");
    }
}

