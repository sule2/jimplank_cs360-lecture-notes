#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


main()
{
  FILE *f;
  int i;
  char s[20];

  f = fdopen(3, "w");
  fprintf(f, "Ha ha\n");
  
}
