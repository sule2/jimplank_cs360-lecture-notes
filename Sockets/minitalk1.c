#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sockettome.h"

/* Set up two processes for each of the client and server.
   Use dup and exec to have them talk with each other using cat. */

int main(int argc, char **argv)
{
  char *hn;
  int port, sock, fd;

  if (argc != 4) {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    exit(1);
  }

  hn = argv[1];
  port = atoi(argv[2]);
  if (port < 5000) {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    fprintf(stderr, "       port must be > 5000\n");
    exit(1);
  }

  if (strcmp(argv[3], "s") == 0) {
    sock = serve_socket(port);
    fd = accept_connection(sock);
    close(sock);
  } else if (strcmp(argv[3], "c") == 0) {
    fd = request_connection(hn, port);
  } else {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    fprintf(stderr, "       last argument must be `s' or `c'\n");
    exit(1);
  }

  printf("Connection made -- input goes to remote site\n");
  printf("                   output comes from remote site\n");

  if (fork() == 0) {
    dup2(fd, 0);
  } else {
    dup2(fd, 1);
  }
  close(fd);
  execlp("cat", "cat", NULL);
  fprintf(stderr, "Exec failed.  Drag\n");
  exit(1);
}
