
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <arpa/inet.h>

typedef uint32_t guint32;
typedef uint16_t guint16;
typedef int32_t  gint32;
typedef uint32_t guint32;
typedef uint8_t guint8;

#pragma pack(push, 4)

typedef struct pcap_hdr_s {
    guint32 magic_number;   /* magic number */
    guint16 version_major;  /* major version number */
    guint16 version_minor;  /* minor version number */
    gint32  thiszone;       /* GMT to local correction */
    guint32 sigfigs;        /* accuracy of timestamps */
    guint32 snaplen;        /* max length of captured packets, in octets */
    guint32 network;        /* data link type */
} pcap_hdr_t;

typedef struct pcaprec_hdr_s {
    guint32 ts_sec;         /* timestamp seconds */
    guint32 ts_usec;        /* timestamp microseconds */
    guint32 incl_len;       /* number of octets of packet saved in file */
    guint32 orig_len;       /* actual length of packet */
} pcaprec_hdr_t;

typedef struct ethernet_hdr_s {
    guint8 dst_mac[6];
    guint8 src_mac[6];
    guint16 protocol_id;
} ethernet_hdr_s;

typedef struct ip_hdr_s {
    guint8 version_ihl;
    guint8 tos;           /*type of service*/ 
    guint16 len;
    guint16 identification;
    guint16 flags;        /* flags + fragment*/
    guint8 ttl;           /* time to live */
    guint8 protocol;
    guint16 checksum;
    guint8 src[4];
    guint8 dst[4];
} ip_hdr_s;

#pragma pack(pop)

#define MAX_DATA_SIZE 4096

int main()
{
    FILE *fp = fopen("ip_packet", "r");
    assert(fp);

    pcap_hdr_t pcap_hdr;
    pcaprec_hdr_t pcaprec_hdr;
    char data[MAX_DATA_SIZE];

    // read header
    size_t n = fread(&pcap_hdr, 1, sizeof(pcap_hdr_t), fp);
    assert(n == sizeof(pcap_hdr_t));
    n = fread(&pcaprec_hdr, 1, sizeof(pcaprec_hdr_t), fp);
    assert(n == sizeof(pcaprec_hdr_t));
    assert(pcaprec_hdr.incl_len < MAX_DATA_SIZE);

    // read data
    n = fread(data, 1, pcaprec_hdr.incl_len, fp);
    assert(n == pcaprec_hdr.incl_len);

    char *p = data;
    // ehternet data
    ethernet_hdr_s *eth_hdr = (ethernet_hdr_s*)p;
    assert(ntohs(eth_hdr->protocol_id) == 0x0800);
    p += sizeof(ethernet_hdr_s);

    // ip header
    ip_hdr_s *ip_hdr = (ip_hdr_s *)p;
    printf("src addr: %d.%d.%d.%d\n",
          ip_hdr->src[0], ip_hdr->src[1], ip_hdr->src[2], ip_hdr->src[3]);
    printf("dst addr: %d.%d.%d.%d\n",
          ip_hdr->dst[0], ip_hdr->dst[1], ip_hdr->dst[2], ip_hdr->dst[3]);

    fclose(fp);

    return 0;
}
