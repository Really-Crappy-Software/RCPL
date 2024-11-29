#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  int port = atoi(argv[1]);
  int incomingsocks;
  int backlog = 3;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Failed\n");
    return -1;
  }
struct sockaddr_in socks;
socks.sin_family = AF_INET; // IPv4 address family
socks.sin_port = htons(port); // port number
socks.sin_addr.s_addr = inet_addr("127.0.0.1"); // IPv4 address
struct sockaddr *addr = (struct sockaddr *)&socks;
if (bind(sockfd, addr, sizeof(socks)) < 0) {
    printf("your code sucks\n");
    return -1;
  } else {
    printf("You did it...\n");
    if (listen(sockfd, backlog) < 0) {
      printf("It's deaf\n");
      return -1;
    } else {
      printf("listening to port %d\n", ntohs(socks.sin_port));
    }
    socklen_t sockbuf;
sockbuf= sizeof(socks);
    while (1) {
      incomingsocks = accept(sockfd, addr, &sockbuf);
      if (incomingsocks < 0) {
        printf("Its intolerant\n");
        return -1;
      } else {
        printf("Someone has tried to connect\n");
      }
    }
    }
}
