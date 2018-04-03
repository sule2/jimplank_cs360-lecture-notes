#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  alarm(2);
  execl("sh1", "sh1", NULL);
  perror("execl");
  return 0;
}
