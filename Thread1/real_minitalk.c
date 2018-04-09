#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockettome.h"

/* process_connection is the exact same as in th_telnet, except we don't
   print the string "Read." */

void *process_connection(void *c)
{
  FILE **connection;
  char buf[1000];

  connection = (FILE **) c;
  while (fgets(buf, 1000, connection[0]) != NULL) {
    fputs(buf, connection[1]);
    fflush(connection[1]);
  }
  exit(0);
}

int main(int argc, char **argv)
{
  int fd, s;
  FILE *fin, *fout;
  FILE *stdin_to_socket[2];
  FILE *socket_to_stdout[2];
  pthread_t tid;

  if (argc != 4 || atoi(argv[2]) <= 0) {
    fprintf(stderr, "usage: th_telnet host port c|s\n");
    exit(1);
  }

  /* Open a socket connection to a server, and convert the file 
     descriptor to two FILE *'s, one for reading and one for 
     writing. */

  if (strcmp(argv[3], "s") == 0) {
    s = serve_socket(atoi(argv[2]));
    fd = accept_connection(s);
  } else {
    fd = request_connection(argv[1], atoi(argv[2]));
  }
  fin = fdopen(fd, "r");
  fout = fdopen(fd, "w");
  
  /* Create arrays of FILE *'s for process_connection. */

  stdin_to_socket[0] = stdin;
  stdin_to_socket[1] = fout;

  socket_to_stdout[0] = fin;
  socket_to_stdout[1] = stdout;

  /* Fork off a thread to read from the socket and print to standard output.
     The main thread will read from standard input and print to the socket. */

  if (pthread_create(&tid, NULL, process_connection, socket_to_stdout) == 0) {
    perror("pthread_create");
    exit(1);
  }
  process_connection(stdin_to_socket);

  return 0;
}
