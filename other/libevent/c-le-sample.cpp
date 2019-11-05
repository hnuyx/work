
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <event2/event.h>
#include <event2/bufferevent.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define  LE_ADDRESS_SIZE 32
#define  LE_BUFFER_SIZE  1024

typedef struct event_base EventBase;
typedef struct event Event;

int usage(const char *exe)
{
    printf("usage: %s <ip> <port>\n", exe);
    return 0;
}

void readcb(struct bufferevent *bev, void *arg)
{
    char buf[LE_BUFFER_SIZE];

    size_t n = bufferevent_read(bev, buf, LE_BUFFER_SIZE - 1);
    buf[n] = '\0';

    printf("%s\n", buf);
}

void eventcb(struct bufferevent *bev, short flag, void *arg)
{
    if(flag & BEV_EVENT_EOF)
    {
        printf("remote peer closed\n");
    }
    else if(flag & BEV_EVENT_ERROR)
    {
        printf("error happened\n");
    }
    else if (flag & BEV_EVENT_TIMEOUT)
    {
        printf("time out\n");
    }
    else if (flag & BEV_EVENT_CONNECTED)
    {
        printf("connection finished\n");
        return ;
    }

    bufferevent_free(bev);
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        return usage(argv[0]);
    }

    int ret = 0;

    // new an event base
    EventBase *base = event_base_new();
    assert(base);

    // bufferevent
    // return a pointer to a newly allocated bufferevent struct, or NULL if an error occurred
    struct bufferevent * bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    assert(bev);

    // connect to server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    inet_aton(argv[1], &sin.sin_addr);
    sin.sin_port = htons(atoi(argv[2]));

    bufferevent_setcb(bev, readcb, NULL, eventcb, bev);
    bufferevent_enable(bev, EV_READ);
    // return 0 on success, -1 on failure.
    ret = bufferevent_socket_connect(bev, (const struct sockaddr*)&sin, sizeof(sin));
    assert(ret == 0);

    // start event loop
    // return 0 if successful, -1 if an error occurred, or 1 if we exited because no events were pending or active.
    ret = event_base_dispatch(base);
    assert(ret >= 0);

    // free the event base
    event_base_free(base);

    return 0;
}
