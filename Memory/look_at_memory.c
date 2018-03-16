#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef UI (unsigned long int) 
extern end;
extern etext;
extern edata;

int A = 4;
int X;
int B = 6;
int Y;

void proc_a()
{
}

int main(int argc, char **argv)
{
  int i, j;
  int *ii;
  char buf[200];

  printf("Page size: %d\n", getpagesize());
  printf("\n");

  printf("&etext: 0x%lx\n", (UI) &etext);
  printf("&edata: 0x%lx\n", (UI) &edata);
  printf("&end:   0x%lx\n", (UI) &end);
  printf("\n");

  printf("Code Addresses:\n");
  printf("main:   0x%lx\n", (UI) main);
  printf("proc_a: 0x%lx\n", (UI) proc_a);

  printf("Global Variable Addresses:\n");
  printf("&A: 0x%lx\n", (UI) &A);
  printf("&B: 0x%lx\n", (UI) &B);
  printf("&X: 0x%lx\n", (UI) &X);
  printf("&Y: 0x%lx\n", (UI) &Y);
  printf("\n");

  printf("Heap Addresses:\n");
  ii = (int *) malloc(sizeof(int));
  printf("ii: 0x%lx\n", (UI) ii);
  printf("\n");

  printf("Stack Addresses:\n");
  printf("&i:    0x%lx\n", (UI) &i);
  printf("&j:    0x%lx\n", (UI) &j);
  printf("&argc: 0x%lx\n", (UI) &argc);
  printf("\n");

  sprintf(buf, "cat /proc/%d/maps", getpid());
  system(buf);
  return 0;
}
