
/**
 * hl-udp-multicast.cpp
 * udp client/server for multicast
 * Henry 2019-10-09
 * */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#include "hl-udp-multicast.h"

HLUdpMultiCast::HLUdpMultiCast(HL_UDP_TYPE ut, const char *_ip, int _port)
{
    type = ut;
    snprintf(ip, HL_IP_MAX_SIZE, "%s", _ip);
    port = _port;
    sockfd = -1;
    is_init = false;
}

int HLUdpMultiCast::init()
{
    if(is_init) return 0;

    // init socket fd
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed %d-%s\n", errno, strerror(errno));
        return -1;
    }

    if (type  == UDP_CLIENT)
    {
        // init client addr
        memset(&addr, 0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);

        int reuse = 1;
        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        {
            printf("setsockopt SO_REUSEADDR failed %d-%s\n", errno, strerror(errno));
            close(sockfd); sockfd = -1;
            return -1;
        }

        // bind
        if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            printf("bind failed %d-%s\n", errno, strerror(errno));
            close(sockfd); sockfd = -1;
            return -1;
        }

        // set multicast info
        mreq.imr_multiaddr.s_addr = inet_addr(ip);
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) < 0)
        {
            printf("setsockopt IP_ADD_MEMBERSHIP failed %d-%s\n", errno, strerror(errno));
            close(sockfd); sockfd = -1;
            return -1;
        }
    }
    else
    {
        // init server addr
        memset(&addr, 0,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);
    }

    is_init = true;

    return 0;
}

HLUdpMultiCast::~HLUdpMultiCast()
{
    if(sockfd > 0)
    {
        setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&mreq, sizeof(mreq));
        close(sockfd);
    }
}

// send heart-beat
int HLUdpMultiCast::send_heartbeat()
{
    if(init() != 0) return -1;

    HLMsgHead msg;
    msg.head = htonl(HL_UDP_HEAD);
    msg.len  = htonl(sizeof(HLMsgHead));
    msg.id   = htonl(MSG_HEARTBEAT);
    msg.seq  = htonl(time(NULL));

    if(sendto(sockfd, &msg, sizeof(HLMsgHead), 0, (struct sockaddr*)&addr, sizeof(addr)) != sizeof(HLMsgHead))
    {
        printf("heart-beat sendto failed %d-%s\n", errno, strerror(errno));
        return -1;
    }

    return 0;
}

/* recv data
 * return msg id
 * */
int HLUdpMultiCast::recv_data()
{
    if(init() != 0) return -1;

    HLMsgHead msg;
    if(recv(sockfd, &msg, sizeof(HLMsgHead), 0) != sizeof(HLMsgHead))
    {
        printf("heart-beat recv failed %d-%s\n", errno, strerror(errno));
        return MSG_NONE;
    }

    msg.head = ntohl(msg.head);
    msg.len  = ntohl(msg.len);
    msg.id   = ntohl(msg.id);
    msg.seq  = ntohl(msg.seq);

    // wrong head and size
    if(msg.head != HL_UDP_HEAD ||
       msg.len != sizeof(HLMsgHead))
        return MSG_NONE;

    // correct msg id
    if(msg.id > MSG_NONE && msg.id < MSG_MAX)
        return msg.id;

    return MSG_NONE;
}

