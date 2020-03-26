
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <event2/event.h>

#define  LE_BUFFER_SIZE  1024

typedef struct event_base EventBase;
typedef struct event Event;

int usage(const char *exe)
{
    printf("Usage: %s <file>\n", exe);
    return 0;
}

void readcb(evutil_socket_t fd, short flag, void *args)
{
    char buf[LE_BUFFER_SIZE];
    if(!(flag | EV_READ))
        return ;

    size_t n = read(fd, buf, LE_BUFFER_SIZE - 1);
    buf[n] = '\0';

    printf("%s\n", buf);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        return usage(argv[0]);
    }

    int ret = 0;

    // new an event base
    EventBase *base = event_base_new();
    assert(base);

    evutil_socket_t fd = (evutil_socket_t)open(argv[1], O_RDONLY | O_APPEND);
    Event *fe = event_new(base, fd, EV_READ | EV_PERSIST, readcb, NULL);
    assert(fe);
    ret = event_add(fe, NULL);
    assert(ret == 0);

    // start event loop
    // return 0 if successful, -1 if an error occurred, or 1 if we exited because no events were pending or active.
    ret = event_base_dispatch(base);
    assert(ret >= 0);

    // free the event base
    event_base_free(base);

    return 0;
}
