/* ch1c.c
   James S. Plank */

/* This program prints out a counter that increments every 5 seconds.
   You stop it by typing <CNTL-C>, which sends the SIGINT signal to
   the program.  This signal terminates the program */

#include <stdio.h>
#include <unistd.h>

int main()
{
  int i;

  i = 0;
  while (1) {
    i++;
    printf("%d\n", i);
    fflush(stdout);
    sleep(1);
  }
  return 0;
}

