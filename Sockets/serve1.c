#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "sockettome.h"

/* This program serves a socket on the given port, and
   accepts a connection.  It sends the username of whoever is running the 
   program along the connection, and then it reads a line of text, one
   character at a time.  It prints the line and exits.  You can connect
   to this program with telnet. */

int main(int argc, char **argv)
{
  char *un, c, s[1000];
  int port, sock, fd;

  /* Parse the command line and error check. */

  if (argc != 2) {
    fprintf(stderr, "usage: serve1 port\n");
    exit(1);
  }

  port = atoi(argv[1]);
  if (port < 8000) {
    fprintf(stderr, "usage: serve1 port\n");
    fprintf(stderr, "       port must be > 8000\n");
    exit(1);
  }

  /* Serve the socket and accept the connection. */

  sock = serve_socket(port);
  fd = accept_connection(sock);

  /* Send the username along the socket. */

  un = getenv("USER");
  printf("Connection established.  Sending `Server: %s'\n", un);
  sprintf(s, "Server: %s\n", un);
  write(fd, s, strlen(s));

  /* Read a line of text, one character at a time. */
  printf("Receiving:\n\n");
  do {
    if (read(fd, &c, 1) != 1) {
      printf("Socket Closed Prematurely\n");
      exit(0);
    } else putchar(c);
  } while (c != '\n');

  exit(0);
}

