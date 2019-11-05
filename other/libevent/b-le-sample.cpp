
/*
 * sample for learning
 * */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define  LE_ADDRESS_SIZE 32
#define  LE_BUFFER_SIZE  1024

typedef struct event_base EventBase;
typedef struct event Event;

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
    }
    else if (flag & BEV_EVENT_TIMEOUT)
    {
    }

    bufferevent_free(bev);
}

// event callback
void acceptcb(struct evconnlistener *listener, evutil_socket_t fd,
              struct sockaddr *addr, int socklen, void *arg)
{
    EventBase *base = (EventBase *)arg;
    struct sockaddr_in *sin = (struct sockaddr_in *)addr;

    //printf("connection from %s:%d\n", buf, ntohs(sin->sin_port));
    printf("connection from %s:%d\n", inet_ntoa(sin->sin_addr), ntohs(sin->sin_port));

    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, readcb, NULL, eventcb, NULL);
    bufferevent_enable(bev, EV_READ);
}

int run_server()
{
    int ret = 0;
    struct sockaddr_in sin;

    // new an event base
    EventBase *base = event_base_new();
    assert(base);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(5566);

    // evconnlistener
    struct evconnlistener *listener =
        evconnlistener_new_bind(base, acceptcb, base,
                                LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_EXEC,
                                -1,  (struct sockaddr *)&sin, sizeof(sin));
    assert(listener);
    assert(evconnlistener_get_fd(listener) != EVUTIL_INVALID_SOCKET);


    // start event loop
    // return 0 if successful, -1 if an error occurred, or 1 if we exited because no events were pending or active.
    ret = event_base_dispatch(base);
    assert(ret >= 0);

    // free the event base
    event_base_free(base);

    return 0;
}

int main()
{
    setbuf(stdout, NULL);
    run_server();
    return 0;
}
