#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  char *s = "Hi!\n";
  int i;
  int fd;

  i = write(3, s, strlen(s));
  printf("%d\n", i);
  if (i < 0) perror("write");
  return 0;
}
