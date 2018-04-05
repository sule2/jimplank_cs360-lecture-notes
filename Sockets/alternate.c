#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sockettome.h"

/* Here is code for a client and server to talk to each other
   by alternating. */

int main(int argc, char **argv)
{
  char *hn;
  int port, sock, fd;
  int i;
  char s[1000];
  FILE *fin, *fout;

  if (argc != 4) {
    fprintf(stderr, "usage: alternate hostname port s|c\n");
    exit(1);
  }

  hn = argv[1];
  port = atoi(argv[2]);
  if (port < 5000) {
    fprintf(stderr, "usage: alternate hostname port\n");
    fprintf(stderr, "       port must be > 5000\n");
    exit(1);
  }

  /* Set up the server port or the client connection. */

  if (argv[3][0] == 's') {
    sock = serve_socket(port);
    fd = accept_connection(sock);
  } else {
    fd = request_connection(hn, port);
  }

  printf("Connection established.  Client should start talking\n");

  fin = fdopen(fd, "r");
  fout = fdopen(fd, "w");

  /* Alternate client and server.  Use the variable i to make sure
     that the client goes first. */

  i = 0;
  while (1) {
    if (argv[3][0] == 'c' || i > 0) {
      if (fgets(s, 1000, stdin) == NULL) exit(0);
      fputs(s, fout);
      fflush(fout);
    }
    if (fgets(s, 1000, fin) == NULL) exit(0);
    fputs(s, stdout);
    fflush(stdout);
    i++;
  }
  return 0;
}
