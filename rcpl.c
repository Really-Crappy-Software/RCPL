#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// By RCS
int main(int argc, char* argv[]) {
  char buffer[100];
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
    printf("FATAL: Socket could not be created\n");
    return -1;
  } else {
    printf("NOTICE: Socket binded successfully \n");
    if (listen(sockfd, backlog) < 0) {
      printf("FATAL: Cannot Listen\n");
      return -1;
    } else {
      printf("NOTICE: listening to port %d\n", ntohs(socks.sin_port));
    }
    socklen_t sockbuf;
sockbuf= sizeof(socks);
    while (1) {
      incomingsocks = accept(sockfd, addr, &sockbuf);
      if (incomingsocks < 0) {
        printf("FATAL: Won't accept connections\n");
        return -1;
      } else {
        printf("NOTICE: Someone has connected\n");
      }
      int flags = MSG_WAITALL;
      ssize_t receiveres = recv(incomingsocks, buffer, sizeof(buffer), flags);
      if (receiveres < 0) {
        printf("NOTICE: No data sent from connected person\n");
      }
      if (buffer == NULL) {
      printf("WARNING: A message has been received, but it wasn't written to the buffer");
      } else {
        printf("Message received printing on next line: \n");
        buffer[receiveres] = '\0';
      printf("%s", buffer);
      }

    }
    }
}
