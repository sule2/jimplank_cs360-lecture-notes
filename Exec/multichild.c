/* multichild.c
   Jim Plank
   CS360 -- Exec/Wait lecture

   This program forks off 4 children processes and waits for them
   all to complete.  The children sleep for a random period of time,
   and then exit.  This shows that wait() will return the first child
   that exits, not the first child that has been forked.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main()
{
  int i, j, status;
  int sleeptime;

  srandom(time(0));

  for (j = 0; j < 4; j++) {
    sleeptime = random()%10;
    i = fork();
    if (i == 0) {
      sleep(sleeptime);
      printf("Child %d (%d) exiting\n", j, getpid());
      exit(0);
    } else {
      printf("Fork %d returned %d\n", j, i);
    }
  }

  for (j = 0; j < 4; j++) {
    i = wait(&status);
    printf("Wait returned %d\n", i);
  }
  return 0;
}

