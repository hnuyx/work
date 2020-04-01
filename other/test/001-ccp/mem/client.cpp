
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <sys/time.h>
 
#include<event.h>
#include<event2/bufferevent.h>
#include<event2/buffer.h>
#include<event2/util.h>

#include "MsgStruct.h"

#include <iostream>
using namespace std;

#define ADJUST_TIME(se,ue,us) \
    if (ue < us) { us += 1000000; se -= 1; }

struct timeval start, tend;
 
void printTable(m_security_data& m) {
    cout << format.BEGIN_TABLE;

    int onum = 0;
    cout << format.BEGIN_LINE << m.getMetaData() << format.END_LINE;
    bool output = false;
    string code(m.code, 8);
    cout << format.BEGIN_LINE << m.toString() << format.END_LINE;
    cout << format.END_TABLE;

}

void outputCSV(m_security_data* m) {
    format.BEGIN_LINE = "";
    format.END_LINE = "\n";
    format.BEGIN_TABLE = "";
    format.END_TABLE = "";
    format.SPLIT_CHAR = ",";
    printTable(*m);
}
 
 
void server_msg_cb(struct bufferevent* bev, void* arg);
void event_cb(struct bufferevent *bev, short event, void *arg);
 
int main(int argc, char** argv)
{
    if( argc < 3 )
    {
        printf("./%s <ip> <port>\n", argv[0]);
        return -1;
    }

    struct event_base *base = event_base_new();
    struct bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &server_addr.sin_addr);

    // connect to server
    bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr, sizeof(server_addr));
    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    gettimeofday(&start, NULL);
    //bufferevent_write(bev, ":\n", 2);
    bufferevent_write(bev, "asdf:SH600000\n", 14);

    event_base_dispatch(base);

    return 0;
}


int size = 0;
int reads = 0;
char *m = (char *) malloc(sizeof (m_security_data));
void server_msg_cb(struct bufferevent* bev, void* arg)
{
    //m_security_data *m = (m_security_data*) malloc(sizeof (m_security_data));

    if(size <= 0 || reads == size)
    {
        bufferevent_read(bev, &size, sizeof(int));
        reads = 0;
    }
    if (size == -1)
        return;
    size_t len = bufferevent_read(bev, m + reads, size - reads);
    reads += len;
    if(reads == size)
    {
        printf("size: %d\n", size);
        outputCSV((m_security_data*)m);
        //gettimeofday(&tend, NULL);
        //ADJUST_TIME(tend.tv_sec, tend.tv_usec, start.tv_usec);
        //printf("times cost %u.%u s\n", (tend.tv_sec - start.tv_sec), (tend.tv_usec - start.tv_usec));
        //gettimeofday(&start, NULL);
        //bufferevent_write(bev, ":\n", 2);
    }
}

void event_cb(struct bufferevent *bev, short event, void *arg)
{
    if (event & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (event & BEV_EVENT_ERROR)
        printf("some other error\n");
    else if( event & BEV_EVENT_CONNECTED)
    {
        printf("the client has connected to server\n");
        return ;
    }

    bufferevent_free(bev);
    struct event *ev = (struct event*)arg;
    event_free(ev);
}


