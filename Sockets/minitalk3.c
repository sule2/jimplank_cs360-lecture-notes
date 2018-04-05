#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "sockettome.h"

int main(int argc, char **argv)
{
  char *hn;
  int port, socket;   /* Port number, and socket fd for server */
  int conn1, conn2;   /* FD's for the two connections */
  int pid1, pid2;     /* Process id's of the two children */
  int pid, dummy;;    /* Used by the parent when it calls wait() */
  int id;             /* ID of process -- Parent/C1/C2: 'P', '1' or '2' */
  int cs;             /* 'c' or 's' - client or server */

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

  /* Set up the connections */

  if (strcmp(argv[3], "s") == 0) {
    cs = 's';
    socket = serve_socket(port);
    conn1 = accept_connection(socket);
    conn2 = accept_connection(socket);
    close(socket);
  } else if (strcmp(argv[3], "c") == 0) {
    cs = 'c';
    conn1 = request_connection(hn, port);
    conn2 = request_connection(hn, port);
  } else {
    fprintf(stderr, "usage: minitalk hostname port s|c\n");
    fprintf(stderr, "       last argument must be `s' or `c'\n");
    exit(1);
  }

  /* Set up parent and two children.  In the parent,
     pid1 and pid2 are the process id's of the children */

  pid1 = fork();
  if (pid1 == 0) {
    id = '1';
  } else {
    pid2 = fork();
    if (pid2 == 0) {
      id = '2';
    } else {
      id = 'P';
    }
  }

  /* Connect C1 of the server to C2 of the client */

  if (id == '1' && cs == 's') dup2(conn1, 1);
  if (id == '2' && cs == 'c') dup2(conn1, 0);

  /* Connect C1 of the client to C2 of the server */

  if (id == '1' && cs == 'c') dup2(conn2, 1);
  if (id == '2' && cs == 's') dup2(conn2, 0);

  /* Everyone (parent included) closes the connections */

  close(conn1);
  close(conn2);

  /* Have the parent call wait, and then kill the other child */

  if (id == 'P') {
    pid = wait(&dummy);
    if (pid == pid1) {
      kill(pid2, SIGKILL);
    } else {
      kill(pid1, SIGKILL);
    }
    exit(0);
  }

  /* Otherwise, have the children execlp cat */

  execlp("cat", "cat", NULL);
  fprintf(stderr, "Exec failed.  Drag\n");
  return 0;
}
