/* testaddr1.c
   Jim Plank
   CS360
   Memory Lecture 
   October, 1996 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern end;
extern etext;

int I;

int main(int argc, char **argv)
{

  int i;
  int *ii;

  printf("Page size: %d\n", getpagesize());

  printf("&etext = 0x%lx\n", (unsigned long int) &etext);
  printf("&end   = 0x%lx\n", (unsigned long int) &end);

  printf("\n");
  ii = (int *) malloc(sizeof(int));

  printf("main   = 0x%lx\n", (unsigned long int) main);
  printf("&I     = 0x%lx\n", (unsigned long int) &I);
  printf("&i     = 0x%lx\n", (unsigned long int) &i);
  printf("&argc  = 0x%lx\n", (unsigned long int) &argc);
  printf("&ii    = 0x%lx\n", (unsigned long int) &ii);
  printf("ii     = 0x%lx\n", (unsigned long int) ii);

}

