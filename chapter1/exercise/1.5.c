#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int listenfd, connfd, i;
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9999);

    Bind(listenfd,(SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    for(;;)
    {
        connfd = Accept(listenfd,(SA*)NULL, NULL);
        ticks = time(NULL);
        snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
        for(i = 0; i < strlen(buf); ++i)
            Write(connfd,&buf[i],1);
        Close(connfd);
    }
}