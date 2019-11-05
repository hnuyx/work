
/*
 * sample for learning
 * */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <event2/event.h>
#include <event2/util.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define  LE_ADDRESS_SIZE 32

typedef struct event_base EventBase;
typedef struct event Event;

// event callback
void do_accept(evutil_socket_t listener, short flag, void  *arg)
{
    EventBase *base = (EventBase *)base;
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    char buf[LE_ADDRESS_SIZE];
    // On success, return a nonnegative integer that is a descriptor for the accepted socket.  On error, -1 is returned, and errno  is  set  appropriately.
    evutil_socket_t fd = accept(listener, (struct sockaddr *)&sin, &len);
    if(fd < 0)
    {
        perror("accept");
        return ;
    }
    //assert(fd > 0);

    // On success, returns a non-NULL pointer to dst.  NULL is returned if there was an error, with errno set to indicate the error.
    const char *ret = inet_ntop(AF_INET, &sin, buf, LE_ADDRESS_SIZE);
    assert(ret);

    printf("connection from %s:%d\n", buf, ntohs(sin.sin_port));
}

int run_server()
{
    int ret = 0;
    struct sockaddr_in sin;

    // new an event base
    EventBase *base = event_base_new();
    assert(base);

    // get listen socket file-descriptor
    // On success, a file descriptor for the new socket is returned.  On error, -1 is returned, and errno is set appropriately.
    evutil_socket_t listener = socket(AF_INET, SOCK_STREAM, 0);
    assert (listener > 0);

    // return 0 on success, -1 on failure
    ret = evutil_make_socket_nonblocking(listener);

    ret = 1;
    // On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
    ret = setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(ret));
    assert(ret == 0);

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(5566);
    // On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
    ret = bind(listener, (struct sockaddr *)&sin, sizeof(sin));
    assert(ret == 0);

    // new an event
    // return a newly allocated struct event that must later be freed with event_free() or NULL if an error occurred.
    // EV_TIMEOUT, EV_READ, EV_WRITE, EV_SIGNAL, EV_PERSIST, EV_ET
    Event *ev = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, base);
    assert(ev);

    // add event
    // return 0 if successful, or -1 if an error occurred
    ret = event_add(ev, NULL);


    // start event loop
    // return 0 if successful, -1 if an error occurred, or 1 if we exited because no events were pending or active.
    ret = event_base_dispatch(base);
    assert(ret >= 0);

    // free the event
    event_free(ev);

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
