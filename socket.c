#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);
  char buffer[100];
    printf("Input the message you want to send\n");
    fgets(buffer, 100, stdin);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Not Working\n");
    return -1;
  }
struct sockaddr_in feetpics;
  feetpics.sin_family = AF_INET;
feetpics.sin_port = htons(port);
feetpics.sin_addr.s_addr = inet_addr("127.0.0.1");
struct sockaddr *addr = (struct sockaddr *)&feetpics;
socklen_t sockbuf;
sockbuf = sizeof(feetpics);
if (connect(sockfd, addr, sockbuf) < 0 ) {
    printf("couldn't establish a connection with 127.0.0.1\n");
    return -1;
  } else {
      struct sockaddr_in jaycar;
      struct sockaddr *radioshack = (struct sockaddr *)&jaycar;
      socklen_t jaycarbuf = sizeof(jaycar);
    getpeername(sockfd, radioshack, &jaycarbuf);
    printf("connected to %s:%d\n", inet_ntoa(jaycar.sin_addr), ntohs(jaycar.sin_port));
    size_t ben = strlen(buffer);
    int flags = MSG_CONFIRM;
    ssize_t result = send(sockfd, buffer, 100, flags);
    if (result < 0) {
      printf("Message not sent\n");
      return -1;
    } else {
      printf("Message sent\n");
    }
  }
}

