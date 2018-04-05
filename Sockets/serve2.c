#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sockettome.h"

/* This program is the same as serve1.c, except it uses
   fdopen(), so that the standard IO library can help
   read from the client. */

int main(int argc, char **argv)
{
  char *un;
  int port, sock, fd;
  int i;
  char s[1000];
  FILE *fsock;

  if (argc != 2) {
    fprintf(stderr, "usage: serve2 port\n");
    exit(1);
  }

  port = atoi(argv[1]);
  if (port < 5000) {
    fprintf(stderr, "usage: serve2 port\n");
    fprintf(stderr, "       port must be > 5000\n");
    exit(1);
  }
  un = getenv("USER");

  sock = serve_socket(port);

  fd = accept_connection(sock);

  printf("Connection established.  Sending `Server: %s'\n", un);
  sprintf(s, "Server: %s\n", un);
  write(fd, s, strlen(s));

  printf("Receiving:\n\n");

  /* Here's the new code -- see how you can use fgets now, instead of read(). */
  fsock = fdopen(fd, "r");

  if (fgets(s, 1000, fsock) == NULL) {
    printf("Error -- socket closed\n");
  } else {
    printf("%s", s);
  }
  return 0;
}
