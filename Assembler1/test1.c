#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char *s;
  long sz;

  if (argc != 2 || sscanf(argv[1], "%ld", &sz) == 0) {
    fprintf(stderr, "usage: test1 bytes\n");
    exit(1);
  }

  s = (char *) malloc(sz);

  if (s == NULL) { perror("malloc"); exit(1); }
  printf("malloc %ld worked\n", sz);
  return 0;
}
