/* prsize3.c
   Jim Plank
   Fall, 1996
   CS360
 */

#include <stdio.h>
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

  d = opendir(fn);
  if (d == NULL) {
    perror("prsize");
    exit(1);
  }
 
  total_size = 0;

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    exists = stat(de->d_name, &buf);
    if (exists < 0) {
      fprintf(stderr, "Couldn't stat %s\n", de->d_name);
    } else {
      total_size += buf.st_size;
    }
    /* Make the recursive call if the file is a directory */
    if (S_ISDIR(buf.st_mode)) {
      total_size += get_size(de->d_name);
    }
  }
  closedir(d);
  return total_size;
}

int main()
{
  printf("%d\n", get_size("."));
}
