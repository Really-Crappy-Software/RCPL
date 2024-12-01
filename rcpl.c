#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
// By RCS
int main(int argc, char* argv[]) {
time_t thyme;
time(&thyme);
  char* timec = ctime(&thyme);
  timec[strcspn(timec, "\n")] = 0;
  strcat(timec, ".log");
  FILE *log = fopen(timec, "w");
      srand(time(NULL));
   signed long num = rand() % 999999999999999 + 100000000000000;
   char man[100];
   sprintf(man, "%d", num);
   printf("the shutdown code is: %s\n", man);
   fprintf(log, "the shutdown code is: %s\n", man);
  char buffer[100];
  char input[10];
  int port = atoi(argv[1]);
  int incomingsocks;
  int backlog = 3;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("FATAL:Socket creation failed\n");
    fprintf(log, "FATAL:Socket creation failed\n");
    return -1;
  }
struct sockaddr_in socks;
socks.sin_family = AF_INET; // IPv4 address family
socks.sin_port = htons(port); // port number
socks.sin_addr.s_addr = inet_addr("127.0.0.1"); // IPv4 address
struct sockaddr *addr = (struct sockaddr *)&socks;
if (bind(sockfd, addr, sizeof(socks)) < 0) {
    printf("FATAL: Socket could not be binded\n");
    fprintf(log, "FATAL: Socket could not be binded\n");
    return -1;
  } else {
    printf("NOTICE: Socket binded successfully \n");
    fprintf(log, "NOTICE: Socket binded successfully \n");
    if (listen(sockfd, backlog) < 0) {
      printf("FATAL: Cannot Listen\n");
      fprintf(log, "FATAL: Cannot Listen\n");
      return -1;
    } else {
      printf("NOTICE: listening to port %d\n", ntohs(socks.sin_port));
      fprintf(log, "NOTICE: listening to port %d\n", ntohs(socks.sin_port));
    }
    socklen_t sockbuf;
sockbuf= sizeof(socks);
    while (1) {
      incomingsocks = accept(sockfd, addr, &sockbuf);
      if (incomingsocks < 0) {
        printf("FATAL: Won't accept connections\n");
        fprintf(log, "FATAL: Won't accept connections\n");
        return -1;
      } else {
        printf("NOTICE: Someone has connected\n");
        fprintf(log, "NOTICE: Someone has connected\n");
      }
      int flags = MSG_WAITALL;
      ssize_t receiveres = recv(incomingsocks, buffer, sizeof(buffer), flags);
      buffer[strcspn(buffer, "\n")] = 0;
      if (receiveres < 0) {
        printf("NOTICE: No data sent from connected person\n");
        fprintf(log, "NOTICE: No data sent from connected person\n");
      }
      if (buffer == NULL) {
      printf("WARNING: A message has been received, but it wasn't written to the buffer");
      fprintf(log, "WARNING: A message has been received, but it wasn't written to the buffer");
      } else {
        printf("Message received printing on next line: \n");
        buffer[receiveres] = '\0';
                  printf("%s\n", buffer);
      fprintf(log, "%s", buffer);
      if (strcmp(buffer, man) == 0) {
        return 0;
      }
      }
    }
    }
}
