
/**
 * hl-udp-multicast.h
 * udp client/server for multicast
 * Henry 2019-10-09
 * */

#ifndef __HL_UDP_MULTICAST_H__
#define __HL_UDP_MULTICAST_H__

#include <stdint.h>
#include <netinet/in.h>

#define HL_UDP_MULTI_CAST_IP   "239.0.0.1"
#define HL_UDP_MULTI_CAST_PORT  6666
#define HL_IP_MAX_SIZE          16
#define HL_UDP_HEAD             0x1A2B3C4D

enum HL_UDP_MSG_ID
{
    MSG_NONE = 0,

    MSG_HEARTBEAT,
    MSG_DATA,

    MSG_MAX
};

enum HL_UDP_TYPE
{
    UDP_CLIENT,
    UDP_SERVER,
};

#pragma pack(push, 4)
typedef struct _HL_MSG_HEAD
{
    uint32_t head;
    uint32_t len;
    uint32_t id;
    uint32_t seq;
} HLMsgHead;
#pragma pack(pop)


class HLUdpMultiCast
{
public:
    HLUdpMultiCast(HL_UDP_TYPE ut = UDP_CLIENT, const char *_ip = HL_UDP_MULTI_CAST_IP, int _port = HL_UDP_MULTI_CAST_PORT);
    ~HLUdpMultiCast();

    int init();

    // send heart-beat
    int send_heartbeat();
    /* recv data
     * return msg id
     * */
    int recv_data();

private:
    HL_UDP_TYPE type;
    char ip[HL_IP_MAX_SIZE];
    int port;

    bool is_init;

    struct sockaddr_in addr;
    struct ip_mreq mreq;

    int sockfd;
};

#endif
