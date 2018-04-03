#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  close(0);
  sleep(1);
  exit(0);
}
