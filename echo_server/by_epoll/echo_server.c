#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct sockaddr SA;

struct connection_s {
    int fd;
    struct connection_s *next;
};
typedef struct connection_s connection_t;

static int g_epfd;


static connection_t *new_connection(int listenfd)
{
    int connfd;
    connection_t

    connfd = accept(listenfd, NULL, NULL);
    if (connfd < 0) {
        fprintf("accept failed, %s\n", strerror(errno));
        return NULL;
    }

    
}

int main(int argc, char *argv[])
{
    int listenfd;
    int port = 60000;
    int events, i;
    struct sockaddr_in srvaddr;
    struct epoll_event ee, event_list[32];

    g_epfd = epoll_create(20);
    assert(g_epfd >= 0);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    srvaddr.sin_family = AF_INET;
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvaddr.sin_port = htons(port);
    if (bind(listenfd, (const SA *)&srvaddr, sizeof(srvaddr)) < 0) {
        fprintf(stderr, "bind address(port:%d) failed, reason: %s\n", port, strerror(errno));
        exit(1);
    }

    if (listen(listenfd, 256) < 0) {
        fprintf(stderr, "listen failed, %s\n", strerror(errno));
        exit(1);
    }

    ee.data.ptr = NULL;
    ee.events = EPOLLIN;
    if (epoll_ctl(g_epfd, EPOLL_CTL_ADD, listenfd, &ee) < 0) {
        fprintf(stderr, "epoll_ctl failed(listen socket), %s\n", strerror(errno));
        exit(1);
    }

    for (;;) {
        events = epoll_wait(g_epfd, event_list, sizeof(event_list)/sizeof(event_list[0]), -1);

        if (events < 0) {
            fprintf(stderr, "epoll_wait failed, %s\n", strerror(errno));
            exit(1);
        }

        for (i = 0; i < events; i++) {
            if (!ee.data.ptr) {
                if (event_list[i].events & EPOLLIN) {
                    
                } else {
                    assert(false);
                }
                continue;
            }
        }
    }
    
    exit(0);
}
