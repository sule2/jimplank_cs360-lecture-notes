/* prsize5.c
   Jim Plank
   Fall, 1996
   CS360
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int get_size(char *fn)
{
  DIR *d;
  struct dirent *de;
  struct stat buf;
  int exists;
  int total_size;
  char *s;

  d = opendir(fn);
  if (d == NULL) {
    perror("prsize");
    exit(1);
  }
 
  s = (char *) malloc(sizeof(char)*(strlen(fn)+258));
  total_size = 0;

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    /* Look for fn/de->d_name */
    sprintf(s, "%s/%s", fn, de->d_name);
    exists = stat(s, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", s);
    } else {
      total_size += buf.st_size;
    }
    if (S_ISDIR(buf.st_mode) && strcmp(de->d_name, ".") != 0 && 
        strcmp(de->d_name, "..") != 0) {
      total_size += get_size(s);
    }
  }
  closedir(d);
  free(s);
  return total_size;
}

int main()
{
  printf("%d\n", get_size("."));
}
