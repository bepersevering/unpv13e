#include "unp.h"
#include <time.h>

int main(int argc, char **argv) {
  int listenfd, connfd;
  socklen_t len;
  struct sockaddr_in servaddr, cliaddr;
  char buff[MAXLINE];
  time_t ticks;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  // daytime server
  servaddr.sin_port = htons(13);

  Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
  Listen(listenfd, LISTENQ);

  for (;;) {
    len = sizeof(cliaddr);
    connfd = Accept(listenfd, (SA *)&cliaddr, &len);
    printf("connection from %s, port %d\n",
           Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));

    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24\r\n", ctime(&ticks));
    Write(connfd, buff, sizeof(buff));
    Close(connfd);
  }
}
